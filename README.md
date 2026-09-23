# IoT-Based Smart Waste Management System

An IoT-based smart waste management prototype developed as a Final Year Project for the Associate Degree in Computer Networking.

The system is designed to monitor the fill level of a waste bin in real time, detect rainfall conditions, provide local status feedback through an LCD, and transmit monitoring data to an online ThingSpeak dashboard using an ESP32 Wi-Fi module.

---

## Table of Contents

- [Project Overview](#project-overview)
- [Motivation](#motivation)
- [Problem Statement](#problem-statement)
- [Aim](#aim)
- [Objectives](#objectives)
- [Key Features](#key-features)
- [System Architecture](#system-architecture)
- [System Workflow](#system-workflow)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [How the System Works](#how-the-system-works)
- [Waste-Level Detection](#waste-level-detection)
- [Rain Detection](#rain-detection)
- [Local LCD Feedback](#local-lcd-feedback)
- [IoT Data Monitoring](#iot-data-monitoring)
- [Data Flow](#data-flow)
- [Requirements Summary](#requirements-summary)
- [Project Scope](#project-scope)
- [Advantages](#advantages)
- [Limitations](#limitations)
- [Future Improvements](#future-improvements)
- [Project Documentation](#project-documentation)
- [Repository Structure](#repository-structure)
- [Project Team](#project-team)
- [Academic Project](#academic-project)
- [License](#license)

---

## Project Overview

Waste management is an important part of urban infrastructure because overflowing waste bins can contribute to unhygienic conditions, environmental problems, and inefficient collection operations.

Traditional waste collection often depends on fixed schedules and manual monitoring. As a result, collection teams may visit bins before they are full, while other bins may remain overflowing until the next scheduled collection.

Our project proposes an **IoT-Based Smart Waste Management System** that continuously monitors a waste bin and provides its status through both local and remote interfaces.

The prototype uses:

- **ESP32 Wi-Fi module** as the main controller and communication unit
- **HC-SR04 ultrasonic sensor** to measure the distance between the sensor and waste surface
- **Rain sensor** to detect rainfall conditions
- **16×2 LCD display** for local status feedback
- **ThingSpeak** for online data logging and visualization
- **3-foot trash bin** as the prototype container
- **Power supply / rechargeable battery** for continuous operation

The system collects measurements approximately every **15 seconds** and sends the data to ThingSpeak using the ESP32's Wi-Fi connectivity.

---

## Motivation

The project was motivated by common waste-management problems observed in local surroundings, including:

- Overflowing garbage bins
- Foul odors
- Unhygienic public areas
- Inefficient manual monitoring
- Collection of bins that are not yet full
- Difficulty planning collection routes without real-time information

The project explores how IoT technology can make waste collection more data-driven, responsive, and efficient.

---

## Problem Statement

The existing waste management approach commonly operates according to fixed collection schedules regardless of the actual amount of waste inside a bin.

This can result in:

- Overflowing bins in high-traffic areas
- Inefficient use of collection resources
- Unnecessary collection trips
- Delayed identification of full bins
- Difficulty planning effective waste collection routes
- Problems caused by the lack of real-time monitoring

Therefore, there is a need for a system that can detect bin fill levels in real time and provide information that can support more timely and efficient waste collection.

---

## Aim

> **To design and develop an IoT-based smart waste management system that monitors bin fill levels and enables timely waste collection.**

---

## Objectives

The project objectives are:

1. Detect waste levels using an ultrasonic sensor.
2. Send real-time alerts when bins become full.
3. Reduce manual monitoring and improve collection efficiency.
4. Contribute to a cleaner and smarter urban environment.

---

## Key Features

| Feature | Description |
|---|---|
| Real-Time Fill Monitoring | Measures waste level using an HC-SR04 ultrasonic sensor |
| Rain Detection | Detects rainfall conditions using a rain sensor |
| Environmental Compensation | Pauses measurements during rainfall to avoid incorrect readings |
| Local Feedback | Displays bin status on a 16×2 LCD |
| Remote Monitoring | Sends data to an online ThingSpeak dashboard |
| Wi-Fi Connectivity | Uses the ESP32 Wi-Fi capability for data transmission |
| Periodic Updates | Collects and transmits measurements approximately every 15 seconds |
| Full-Bin Alert | Identifies an almost-full bin condition |
| Prototype Deployment | Tested using a 3-foot-tall waste bin |

---

# System Architecture

The overall system combines sensing, local processing, wireless communication, and cloud-based monitoring.

```mermaid
flowchart LR

    A[HC-SR04<br/>Ultrasonic Sensor] --> C[ESP32<br/>Controller]
    B[Rain Sensor] --> C

    C --> D[16x2 LCD<br/>Local Feedback]
    C --> E[Wi-Fi]
    E --> F[ThingSpeak<br/>Online Platform]

    F --> G[Web Dashboard<br/>Remote Monitoring]
    G --> H[Waste Collection<br/>Planning]