# Project Overview

## Abstract

This project presents an IoT-based smart waste management prototype designed for real-time monitoring of waste-bin fill level and environmental conditions. The system uses an ESP32 to process readings from an HC-SR04 ultrasonic sensor and a rain sensor, provides local status through a 16x2 I2C LCD, and transmits monitoring data to ThingSpeak for remote visualization.

The project adds environmental compensation by detecting rainfall and suspending fill-level updates during the reported rain condition. The accessible publication reports 99% correct fill-level and rain-monitoring readings, 15-second reporting intervals, average dashboard latency below 2 seconds, and 99% successful transmissions.

## Objectives

1. Monitor waste-bin fill level remotely.
2. Detect rainfall as an environmental condition that can affect ultrasonic measurements.
3. Provide local status feedback.
4. Provide cloud-based remote monitoring and historical visualization.
5. Maintain operation during temporary Wi-Fi disruptions through reconnection logic.
6. Demonstrate a low-cost, modular IoT architecture suitable for future expansion.

## System boundaries

### Included

- Fill-level measurement
- Rain detection
- ESP32 processing
- LCD status display
- ThingSpeak cloud logging/visualization
- Wi-Fi communication
- Reconnection logic

### Not represented as complete production features

- Municipal-scale route dispatching
- Fleet management
- Mobile application
- AI-based waste classification
- Production-grade security architecture
- Formal smart-city certification

## High-level data flow

```text
Waste Bin
   |
   +--> HC-SR04 ----+
   |                 |
   +--> Rain Sensor -+--> ESP32 --> Decision / Processing --> LCD
                                  |
                                  +--> Wi-Fi --> ThingSpeak --> Dashboard
```

## Engineering principle

The design keeps the edge node relatively simple. Sensing and immediate decisions occur on the ESP32, while cloud services provide remote visibility and historical visualization.
