# Hardware

## Component inventory

| Component | Function | Notes |
|---|---|---|
| ESP32 Dev Board | Main controller, sensor processing, Wi-Fi transmission | Publication identifies it as the central controller |
| HC-SR04 | Ultrasonic fill-level measurement | Mounted inside/top of the bin |
| Rain sensor | Rain detection / environmental compensation | Connected to an ADC-capable input in the publication |
| 16x2 I2C LCD | Local feedback | I2C address `0x27` |
| Status LED | Device/connection indication | GPIO 2 |
| 3 ft dustbin | Prototype container | Used as the physical test vessel |
| 10,000 mAh 5 V power bank | Power | Reported for continuous prototype operation |

## Physical placement described in the publication

The published implementation states that the HC-SR04 and rain sensor were mounted near the top edge of the lid, while the ESP32, LCD, and battery pack were secured beneath the lid. Wiring used DuPont cables on a compact breadboard and the electronics were enclosed in a weather-resistant plastic box.

## Calibration and testing notes

The publication reports:

- HC-SR04 calibration with known-height objects.
- Approximately +/- 2 cm calibration accuracy in the reported tests.
- Rain-sensor threshold setup using a spray bottle.
- 12-hour continuous testing.
- Wi-Fi reconnection testing up to 30 m from the router.

## Wiring status

Only some hardware addresses/pins are explicit in the accessible publication:

| Signal/device | Published detail |
|---|---|
| LCD | I2C address `0x27` |
| Status LED | GPIO 2 |
| Rain sensor | ADC pin, exact pin not given in accessible text |
| HC-SR04 | Exact trigger/echo pins not given in accessible text |

The repository therefore intentionally avoids claiming an exact original pinout. Add the recovered wiring diagram to `hardware/` when the original FYP report is available.
