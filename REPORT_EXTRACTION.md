# Key Project Details Extracted / Consolidated

## Important source-status note

The user-supplied `github-fyp-adp-iot-swms.pdf` file is truncated at exactly 2 MiB. Standard PDF readers report a missing trailer/xref table and the document cannot be rendered as a normal multi-page PDF. Because the report itself is not structurally recoverable from the attached bytes, the sections below are **not presented as a literal page-by-page extraction of that file**.

The project details were instead consolidated from the accessible 2026 publication with the same project title and system description. These details should be reconciled against the original FYP report after a complete copy is available.

## Project identity

- Title: **IoT-based smart waste management system: real-time monitoring and environmental compensation**
- Academic setting: Associate Degree in Computer Networking FYP (project metadata)
- Publication venue: Natural and Applied Sciences International Journal (NASIJ)
- Volume/issue: 7(1), 2026
- Pages: 42-53
- Publication date: 19 July 2026
- DOI: `10.47264/idea.nasij/7.1.3`

## Authors listed in the publication

1. Osama Saeed
2. Ayesha Noroz
3. Maimoona Waqar
4. Abuzar Ali
5. Daniyal Butt

## Core problem

The project addresses limitations of fixed-schedule waste collection, especially overflowing bins, inefficient collection planning, and the absence of real-time bin-condition monitoring.

## Main idea

Use an ESP32-based sensing node to:

1. Measure bin fill level using HC-SR04 ultrasonic ranging.
2. Detect rainfall using a rain sensor.
3. Suppress fill-level updates during rain to reduce false readings.
4. Show bin/environment status locally on a 16x2 LCD.
5. Send sensor data to ThingSpeak over Wi-Fi every 15 seconds.
6. Provide remote monitoring and time-series visualization.

## Hardware reported

| Component | Reported role |
|---|---|
| ESP32 Dev Board | Central controller and Wi-Fi data transmitter |
| HC-SR04 ultrasonic sensor | Fill-level measurement |
| Rain sensor | Rain detection / environmental compensation |
| 16x2 I2C LCD | Local status display |
| 3 ft dustbin | Prototype test vessel |
| 5 V 10,000 mAh power bank | Prototype power source |
| Status LED | Connection/status indication |

## Software reported

- Arduino IDE 1.8.13
- C++ / Arduino dialect
- `WiFi.h`
- `ThingSpeak.h`
- `Wire.h`
- `LiquidCrystal_PCF8574.h`
- ThingSpeak dashboard
- Serial debugging at 115200 baud

## Reported configuration facts

- LCD I2C address: `0x27`
- Status LED: GPIO 2
- ThingSpeak reporting interval: 15 seconds
- Wi-Fi reconnection retry timing: about 5 seconds
- Reconnection test distance: up to 30 m from router
- Ultrasonic calibration: approximately +/- 2 cm in reported tests
- Continuous test: 12 hours

## Reported operating states

The publication describes status labels such as:

- `Empty`
- `Middle`
- `Full`
- `Rain Detected`

The published test table reports approximate dashboard values of 0%, 50%, and 90% for the empty, half-full, and full scenarios respectively.

## Reported results

| Metric | Reported value |
|---|---:|
| Fill-level accuracy | 99% correct readings |
| Rain detection accuracy | 99% correct readings |
| Average update latency | < 2 s |
| Cases with dashboard response within 2 s | 95% |
| Successful transmissions | 99% |

## Reported future work

The publication identifies future directions including:

- Machine learning for waste classification.
- A user-facing mobile application.
- Solar/renewable power.
- Further collection-route optimization and related smart-city extensions.
