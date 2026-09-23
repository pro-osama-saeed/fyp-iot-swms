# IoT-Based Smart Waste Management System

### Real-time waste-bin monitoring with rain-aware environmental compensation

[![ESP32](https://img.shields.io/badge/Controller-ESP32-informational)](https://www.espressif.com/en/products/socs/esp32)
[![IoT](https://img.shields.io/badge/Domain-IoT-success)](https://www.arduino.cc/)
[![Cloud](https://img.shields.io/badge/Cloud-ThingSpeak-orange)](https://thingspeak.com/)
[![Publication](https://img.shields.io/badge/Published-2026-blue)](https://doi.org/10.47264/idea.nasij/7.1.3)

An academic IoT prototype for monitoring waste-bin fill level and environmental conditions in near real time. The system combines an **ESP32**, **HC-SR04 ultrasonic sensor**, **rain sensor**, **16x2 I2C LCD**, and **ThingSpeak** so that bin status can be observed both locally and remotely.

> **Academic context:** Associate Degree in Computer Networking (ADP) Final Year Project.

> **Source note:** The PDF attached to this chat is truncated at exactly 2 MiB and does not contain a usable PDF trailer/xref table, so its original pages, figures, tables, and source code could not be faithfully extracted. This repository therefore separates **source-derived project facts** from **redrawn/reconstructed implementation material**. The accessible 2026 publication describing the same project is used as a supplemental source and is cited below. Replace the source placeholders with the original report/code when the complete report is available.

---

## Project at a glance

| Item | Details |
|---|---|
| Project | IoT-Based Smart Waste Management System |
| Academic context | ADP Computer Networking FYP |
| Core controller | ESP32 Wi-Fi microcontroller |
| Fill-level sensing | HC-SR04 ultrasonic sensor |
| Environmental sensing | Rain sensor |
| Local feedback | 16x2 I2C LCD, address `0x27` |
| Cloud monitoring | ThingSpeak |
| Reporting interval | 15 seconds |
| Alert/fill threshold | 90% capacity |
| Reported fill-level/rain monitoring accuracy | 99% correct readings across the reported tests |
| Reported dashboard latency | < 2 s average; 95% of cases within 2 s |
| Reported successful transmissions | 99% |
| Prototype power | 5 V, 10,000 mAh power bank |
| Reported continuous test | 12-hour run |
| Publication | NASIJ, Vol. 7(1), pp. 42-53, 2026 |
| DOI | 10.47264/idea.nasij/7.1.3 |

---

## What problem does it address?

Traditional fixed-schedule waste collection can result in bins being collected too early or overflowing before the next scheduled pickup. The project explores a low-cost IoT alternative in which a bin's fill level is sensed, processed locally, uploaded to a cloud dashboard, and shown on an on-site display.

A key project contribution is **rain-aware environmental compensation**: rainfall can interfere with ultrasonic measurements, so rain detection is used to suppress fill-level updates/alerts during the reported rain condition rather than treating every ultrasonic reading as normal waste-level data.

---

## System architecture

![System architecture](docs/figures/architecture.svg)

The architecture shown above is a **redrawn project diagram**, not an extracted copy of the unavailable original report figure.

Data path:

`HC-SR04 + Rain Sensor -> ESP32 -> Local LCD`

and

`ESP32 -> Wi-Fi -> ThingSpeak -> Remote Dashboard`

The publication also describes a status LED on GPIO 2, an I2C LCD at address `0x27`, serial debugging at 115200 baud, and automatic Wi-Fi reconnection logic.

---

## Main features

### 1. Real-time fill-level monitoring

The HC-SR04 is mounted inside the top of the bin and measures the distance to the waste surface. The reported testing scenarios map sensor distance to approximate bin states such as empty, middle/half-full, and full.

### 2. Rain-aware measurement handling

The rain sensor provides environmental context. During the reported rain condition, the system displays a rain status and pauses fill-level updates to reduce false readings.

### 3. Local + remote feedback

The 16x2 LCD provides immediate status information at the bin, while ThingSpeak provides remote data logging, visualization, historical inspection, and monitoring.

### 4. Near-real-time cloud reporting

The reported design sends data to ThingSpeak every **15 seconds**, with the published evaluation reporting an average dashboard appearance delay of less than **2 seconds** in the measured cases.

### 5. Automatic Wi-Fi recovery

The published implementation reports reconnection testing up to **30 m** from the router and retry logic at approximately **5-second** intervals after a connectivity problem.

---

## Hardware

| Component | Role |
|---|---|
| ESP32 Dev Board | Sensor processing, decision logic, Wi-Fi communication |
| HC-SR04 | Bin fill-level distance measurement |
| Rain sensor | Rain/environment detection and fill-reading suppression |
| 16x2 I2C LCD | On-site status display |
| 5 V / 10,000 mAh power bank | Prototype power source |
| Status LED | Connection/system status indication |
| 3 ft dustbin | Physical prototype/test vessel |

See [`docs/HARDWARE.md`](docs/HARDWARE.md) for the detailed component notes.

---

## Software stack

| Layer | Technology |
|---|---|
| Embedded development | Arduino IDE 1.8.13 |
| Firmware language | C++ (Arduino dialect) |
| Wi-Fi | `WiFi.h` |
| Cloud upload | `ThingSpeak.h` |
| I2C bus | `Wire.h` |
| LCD | `LiquidCrystal_PCF8574.h` |
| Cloud visualization | ThingSpeak dashboard |
| Serial debugging | 115200 baud |

See [`docs/SOFTWARE.md`](docs/SOFTWARE.md).

---

## Operating workflow

![System workflow](docs/figures/workflow.svg)

1. Initialize ESP32, LCD, sensors, and status outputs.
2. Connect to Wi-Fi.
3. Check the rain condition.
4. If rain is detected, show rain status and suppress fill-level updates.
5. Otherwise read the HC-SR04 distance.
6. Convert the calibrated distance into a fill-level/status value.
7. Update the LCD.
8. Upload the current status to ThingSpeak at the configured interval.
9. Reconnect automatically if Wi-Fi drops.
10. Repeat continuously.

The exact original firmware control flow should be restored from the project source code when available.

---

## Reported testing

### Test plan

| Scenario | Reported setup | Expected/observed behavior |
|---|---|---|
| Empty bin | Sensor at about 3 m; rain off; network connected | LCD: `Empty`; dashboard: `0%` fill |
| Half-full bin | Sensor at about 1.5 m; rain off; network connected | LCD: `Middle`; dashboard: `50%` fill |
| Full bin | Sensor at < 0.3 m; rain off; network connected | LCD: `Full`; dashboard: `90%` fill |
| Rain condition | Rain sensor triggered regardless of ultrasonic reading | LCD: `Rain Detected`; dashboard pauses fill updates |

> The published text contains a measurement/unit inconsistency between the stated **3 ft physical bin** and the **3 m empty-bin test description**. This repository preserves the published wording rather than silently changing it. See [`docs/TESTING_AND_RESULTS.md`](docs/TESTING_AND_RESULTS.md).

### Performance results

![Reported performance](docs/figures/performance.svg)

| Metric | Reported result |
|---|---:|
| Fill-level accuracy | 99% correct readings |
| Rain detection accuracy | 99% correct readings |
| Dashboard update latency | < 2 s average |
| Cases within 2 s | 95% |
| Successful transmissions | 99% |
| Ultrasonic calibration result | approximately +/- 2 cm in the reported tests |

The above values are reported in the 2026 publication for this project; they are not independent replication results from this repository.

---

## Implementation details documented in the publication

The published implementation describes:

- Arduino IDE 1.8.13 with C++ for ESP32.
- `WiFi.h`, `ThingSpeak.h`, `Wire.h`, and `LiquidCrystal_PCF8574.h`.
- I2C LCD address `0x27`.
- ESP32 onboard/status LED on GPIO 2.
- Serial debugging at 115200 baud.
- A 500 ms delay after ultrasonic measurement to address occasional stuck readings.
- LCD second-line clearing to prevent cursor-overwrite artifacts.
- A 10,000 mAh power bank as the prototype's 5 V power source.
- Continuous 12-hour runs in testing.
- Reconnection testing up to 30 m from the router.

These are documented implementation facts from the accessible publication, not claims that the exact original FYP firmware has been recovered.

---

## Repository structure

```text
iot-smart-waste-management-system/
├── README.md
├── CITATION.cff
├── CONTRIBUTING.md
├── .gitignore
├── .github/
│   └── ISSUE_TEMPLATE/
│       ├── bug_report.md
│       └── feature_request.md
├── src/
│   ├── README.md
│   ├── esp32_smart_waste_monitoring_reference.ino
│   └── secrets.example.h
├── hardware/
│   └── README.md
├── data/
│   ├── test_plan.csv
│   └── test_results.csv
├── docs/
│   ├── REPORT_EXTRACTION.md
│   ├── PROJECT_OVERVIEW.md
│   ├── HARDWARE.md
│   ├── SOFTWARE.md
│   ├── TESTING_AND_RESULTS.md
│   ├── LIMITATIONS_AND_FUTURE_WORK.md
│   ├── PUBLICATION.md
│   ├── SOURCE_STATUS.md
│   ├── tables/
│   │   ├── component_inventory.md
│   │   ├── test_plan.md
│   │   └── performance.md
│   └── figures/
│       ├── architecture.svg
│       ├── workflow.svg
│       ├── performance.svg
│       └── data-flow.mmd
└── references/
    └── references.bib
```

---

## Quick start

### 1. Install Arduino IDE

Use the Arduino IDE version recorded in the publication (1.8.13) or a later compatible version.

### 2. Install ESP32 board support

Add ESP32 support through the Arduino IDE Boards Manager.

### 3. Install libraries

Install the libraries used by the documented implementation:

- `WiFi`
- `ThingSpeak`
- `LiquidCrystal_PCF8574`

`Wire` is provided with the Arduino environment.

### 4. Configure secrets

Copy:

```text
src/secrets.example.h
```

to:

```text
src/secrets.h
```

and add your own Wi-Fi and ThingSpeak credentials. `secrets.h` is ignored by Git.

### 5. Verify hardware pin mapping

The publication identifies GPIO 2 for the status LED and the LCD I2C address as `0x27`, but the accessible project description does **not** provide all HC-SR04/rain-sensor pin assignments. The reference firmware therefore marks those pins as configurable and should not be presented as the recovered original wiring.

### 6. Upload and test

Start with the local LCD and Serial Monitor, then verify ThingSpeak upload behavior. Use the test cases under `docs/TESTING_AND_RESULTS.md` as the minimum documentation baseline.

---

## Limitations documented for the project

The project is a prototype rather than a production municipal waste platform. The main future extensions discussed in the publication include:

- Machine-learning-based waste classification.
- Mobile application support.
- Solar/renewable power options.
- More advanced collection-route optimization.
- Expanded notification and control features.

See [`docs/LIMITATIONS_AND_FUTURE_WORK.md`](docs/LIMITATIONS_AND_FUTURE_WORK.md).

---

## Publication

The project was published as:

> Saeed, O., Noroz, A., Waqar, M., Ali, A., & Butt, D. (2026). *IoT-based smart waste management system: real-time monitoring and environmental compensation*. **Natural and Applied Sciences International Journal (NASIJ), 7**(1), 42-53. https://doi.org/10.47264/idea.nasij/7.1.3

Official article page: https://www.ideapublishers.org/index.php/nasij/article/view/7.1.3

The publication page identifies the article as open access under **CC BY 4.0**.

---

## Attribution and academic integrity

This repository is intended to document the project clearly and reproducibly. The redrawn diagrams in `docs/figures/` are original repository assets based on the documented system description. The reference firmware is clearly marked as reconstructed/reference material and should not be confused with the original FYP source code until that source is restored.

---

## Project status

**Documentation-ready | Original source extraction pending complete FYP report/code**

The repository is intentionally structured so the original report PDF, original firmware, wiring diagram, prototype photographs, ThingSpeak screenshots, and experimental raw data can be added later without reorganizing the project.
