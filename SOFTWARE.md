# Software and Firmware

## Documented software stack

| Layer | Tool/library |
|---|---|
| IDE | Arduino IDE 1.8.13 |
| Language | C++ / Arduino dialect |
| Wi-Fi | `WiFi.h` |
| ThingSpeak | `ThingSpeak.h` |
| I2C | `Wire.h` |
| LCD | `LiquidCrystal_PCF8574.h` |
| Serial debug | 115200 baud |

## Firmware responsibilities

The ESP32 firmware is described as handling:

1. Sensor data acquisition.
2. Fill-level calculation.
3. Rain-condition detection.
4. Local LCD status changes.
5. ThingSpeak data transmission.
6. Wi-Fi reconnection.
7. Status indication.

## Reported implementation fixes

The publication records two practical firmware fixes:

- A 500 ms delay after ultrasonic measurements helped resolve occasional stuck readings.
- Clearing the LCD's second line prevented old text from remaining visible after status changes.

## Security / credential handling for this repository

The repository does not store Wi-Fi passwords or ThingSpeak API keys. Put secrets in `src/secrets.h` and keep that file untracked.

## Original vs reference firmware

`src/esp32_smart_waste_monitoring_reference.ino` is intentionally labeled as a **reference/reconstructed implementation**. It follows the documented system behavior but is not presented as the original FYP source because the attached report and source files were not recoverable.
