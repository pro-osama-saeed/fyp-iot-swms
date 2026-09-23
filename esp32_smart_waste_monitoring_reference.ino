#include <WiFi.h>
#include <ThingSpeak.h>
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>
#include "secrets.h"

// -----------------------------------------------------------------------------
// Reference firmware reconstructed from the published system description.
// It is NOT the recovered original FYP firmware.
// -----------------------------------------------------------------------------

// Known from the publication:
constexpr uint8_t STATUS_LED_PIN = 2;
constexpr uint8_t LCD_I2C_ADDRESS = 0x27;

// Example/configurable pins - VERIFY AGAINST THE ACTUAL PROJECT HARDWARE.
constexpr uint8_t TRIG_PIN = 5;
constexpr uint8_t ECHO_PIN = 18;
constexpr uint8_t RAIN_PIN = 34;  // ADC-capable input on many ESP32 boards.

constexpr unsigned long REPORT_INTERVAL_MS = 15000UL;
constexpr unsigned long WIFI_RETRY_INTERVAL_MS = 5000UL;
constexpr unsigned long ULTRASONIC_SETTLE_MS = 500UL;

// Calibrate these two values against the real prototype.
// The accessible publication reports a 3 ft physical bin, while one test row
// states 3 m for the empty-bin measurement. Do not assume either is correct
// for your physical build without calibration.
constexpr float EMPTY_DISTANCE_CM = 91.44F;  // 3 ft, configurable
constexpr float FULL_DISTANCE_CM = 9.144F;   // 0.3 ft, configurable
constexpr int FULL_THRESHOLD_PERCENT = 90;

LiquidCrystal_PCF8574 lcd(LCD_I2C_ADDRESS);
WiFiClient client;

unsigned long lastReportMs = 0;
unsigned long lastWifiAttemptMs = 0;
float lastFillPercent = NAN;
bool lastRainState = false;

static float clampFloat(float value, float low, float high) {
  if (value < low) return low;
  if (value > high) return high;
  return value;
}

bool rainDetected() {
  // Threshold polarity varies by rain-sensor module.
  // VERIFY and calibrate this against the actual sensor board.
  const int raw = analogRead(RAIN_PIN);
  constexpr int RAIN_ADC_THRESHOLD = 1800;
  return raw < RAIN_ADC_THRESHOLD;
}

float readDistanceCm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  const unsigned long durationUs = pulseIn(ECHO_PIN, HIGH, 30000UL);
  if (durationUs == 0) {
    return NAN;
  }

  const float distanceCm = (durationUs * 0.0343F) / 2.0F;
  delay(ULTRASONIC_SETTLE_MS);
  return distanceCm;
}

float distanceToFillPercent(float distanceCm) {
  if (!isfinite(distanceCm)) {
    return NAN;
  }

  const float span = EMPTY_DISTANCE_CM - FULL_DISTANCE_CM;
  if (span <= 0.0F) {
    return NAN;
  }

  const float fill = ((EMPTY_DISTANCE_CM - distanceCm) / span) * 100.0F;
  return clampFloat(fill, 0.0F, 100.0F);
}

const char* statusFromFill(float fillPercent) {
  if (!isfinite(fillPercent)) return "Sensor Error";
  if (fillPercent >= FULL_THRESHOLD_PERCENT) return "Full";
  if (fillPercent >= 50.0F) return "Middle";
  return "Empty";
}

void lcdLine(uint8_t row, const String& value) {
  lcd.setCursor(0, row);
  lcd.print("                ");
  lcd.setCursor(0, row);
  lcd.print(value.substring(0, 16));
}

void showRain() {
  lcdLine(0, "Rain Detected");
  lcdLine(1, "Fill update paused");
}

void showFill(float fillPercent) {
  lcdLine(0, String(statusFromFill(fillPercent)));
  if (isfinite(fillPercent)) {
    lcdLine(1, String((int)round(fillPercent)) + "% fill");
  } else {
    lcdLine(1, "Sensor Error");
  }
}

void setStatusLed(bool connected) {
  digitalWrite(STATUS_LED_PIN, connected ? HIGH : LOW);
}

void connectWiFiIfNeeded() {
  if (WiFi.status() == WL_CONNECTED) {
    setStatusLed(true);
    return;
  }

  setStatusLed(false);

  const unsigned long now = millis();
  if (now - lastWifiAttemptMs < WIFI_RETRY_INTERVAL_MS) {
    return;
  }

  lastWifiAttemptMs = now;
  Serial.println("Wi-Fi reconnect attempt...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

void uploadToThingSpeak(bool rainState, float fillPercent) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Skipping ThingSpeak upload: Wi-Fi not connected.");
    return;
  }

  // Reference mapping only. Verify the original channel-field mapping.
  // Field 1 = fill percent; Field 2 = rain flag.
  if (isfinite(fillPercent)) {
    ThingSpeak.setField(1, fillPercent);
  }
  ThingSpeak.setField(2, rainState ? 1 : 0);

  const int httpCode = ThingSpeak.writeFields(THINGSPEAK_CHANNEL_ID,
                                               THINGSPEAK_WRITE_API_KEY);
  Serial.print("ThingSpeak response: ");
  Serial.println(httpCode);
}

void setup() {
  Serial.begin(115200);

  pinMode(STATUS_LED_PIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(RAIN_PIN, INPUT);

  digitalWrite(TRIG_PIN, LOW);
  setStatusLed(false);

  Wire.begin();
  lcd.begin(16, 2);
  lcd.setBacklight(255);
  lcd.clear();
  lcdLine(0, "Smart Waste Bin");
  lcdLine(1, "Starting...");

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  ThingSpeak.begin(client);
}

void loop() {
  connectWiFiIfNeeded();

  const unsigned long now = millis();
  if (now - lastReportMs < REPORT_INTERVAL_MS) {
    delay(10);
    return;
  }
  lastReportMs = now;

  lastRainState = rainDetected();

  if (lastRainState) {
    // Documented behavior: suppress fill-level updates while raining.
    showRain();
    uploadToThingSpeak(true, lastFillPercent);
    Serial.println("Rain detected: fill-level update paused.");
    return;
  }

  const float distanceCm = readDistanceCm();
  const float fillPercent = distanceToFillPercent(distanceCm);
  lastFillPercent = fillPercent;

  showFill(fillPercent);
  uploadToThingSpeak(false, fillPercent);

  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  Serial.print("Fill (%): ");
  Serial.println(fillPercent);
}
