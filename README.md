# Reference ESP32 Firmware

This directory contains a **reference/reconstructed firmware skeleton** based on the behavior documented in the accessible 2026 publication. It is deliberately not labeled as the original FYP code because the attached report/source package could not be fully recovered.

## Files

- `esp32_smart_waste_monitoring_reference.ino` - reference firmware
- `secrets.example.h` - credential template

## Before compiling

1. Copy `secrets.example.h` to `secrets.h`.
2. Add your Wi-Fi SSID/password and ThingSpeak Write API key/channel ID.
3. Verify the actual ESP32/HC-SR04/rain-sensor wiring.
4. Calibrate the bin-distance constants against the real prototype.

## Important

The accessible publication explicitly documents LCD address `0x27` and status LED GPIO 2, but does not provide the complete HC-SR04/rain-sensor pin map in the accessible text. The reference sketch uses configurable example pins and must be reconciled with the actual hardware before physical deployment.
