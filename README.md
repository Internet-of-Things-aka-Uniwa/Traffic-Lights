<p align="center">
  <img src="https://www.especial.gr/wp-content/uploads/2019/03/panepisthmio-dut-attikhs.png" alt="UNIWA" width="150"/>
</p>

<p align="center">
  <strong>UNIVERSITY OF WEST ATTICA</strong><br>
  SCHOOL OF ENGINEERING<br>
  DEPARTMENT OF COMPUTER ENGINEERING AND INFORMATICS
</p>

<hr/>

<p align="center">
  <strong>Internet of Things</strong>
</p>

<h1 align="center" style="letter-spacing: 1px;">
  Traffic Light Sequence with Arduino UNO, ESP-01 and ThingSpeak
</h1>

<p align="center">
  <strong>Vasileios Evangelos Athanasiou</strong><br>
  Student ID: 19390005
</p>

<p align="center">
  <a href="https://github.com/Ath21" target="_blank">GitHub</a> ·
  <a href="https://www.linkedin.com/in/vasilis-athanasiou-7036b53a4/" target="_blank">LinkedIn</a>
</p>

<p align="center">
  <strong>Angelos Vasileios Mantzoukas</strong><br>
  Student ID: 19390128
</p>

<p align="center">
  <a href="https://github.com/Mantzclb" target="_blank">GitHub</a> ·
  <a href="https://www.linkedin.com/in/aggelos-mantzoukas-a3538b233/" target="_blank">LinkedIn</a>
</p>

<p align="center">
  <strong>Christos Pylarinos</strong><br>
  Student ID: 20390278
</p>

<p align="center">
  <a href="https://github.com/ThodohrGoldhammer" target="_blank">GitHub</a>
</p>

<hr/>

<p align="center">
  <strong>Supervision</strong>
</p>

<p align="center">
  Supervisor: Panagiotis Karkazis, Associate Professor<br>
</p>

<p align="center">
  <a href="https://ice.uniwa.gr/en/emd_person/panagiotis-karkazis/" target="_blank">UNIWA Profile</a> ·
  <a href="https://www.linkedin.com/in/panos-karkazis-39ba1595/" target="_blank">LinkedIn</a>
</p>

<p align="center">
  Co-supervisor: Rania Garofalaki, Laboratory Teaching Staff<br>
</p>

<p align="center">
  <a href="https://ice.uniwa.gr/en/emd_person/zacharenia-garofalaki/" target="_blank">UNIWA Profile</a> ·
  <a href="https://www.linkedin.com/in/rania-garofalaki-4761b071/" target="_blank">LinkedIn</a>
</p>

<hr/>

<p align="center">
  Athens, January 2025
</p>

---

# Project Overview

This project focuses on the development of an **automated traffic light system** using an **Arduino UNO**, integrated with the **ThingSpeak IoT platform** for real-time monitoring and remote control. The system simulates a classic traffic light sequence and transmits its operational state to the cloud via an **ESP-01 (ESP8266) WiFi module**.

---

## Table of Contents

| Section | Folder | Description |
|------:|--------|-------------|
| 1 | `assign/` | Assignment material for the Traffic Lights project |
| 1.1 | `assign/Final-Project.pdf` | Final project description in English |
| 1.2 | `assign/Τελικη-Εργασία.pdf` | Τελική εργασία (Greek) |
| 2 | `docs/` | Project documentation and theoretical background |
| 2.1 | `docs/Electrical-Signal-Light.pdf` | Electrical traffic light theory (EN) |
| 2.2 | `docs/Ηλεκτρικός-Φωτεινός-Σηματοδότης.pdf` | Θεωρία ηλεκτρικού φωτεινού σηματοδότη (EL) |
| 3 | `src/` | Arduino source code and execution outputs |
| 3.1 | `src/A4/A4.ino` | Arduino implementation – Scenario A4 |
| 3.2 | `src/B/B.ino` | Arduino implementation – Scenario B |
| 3.3 | `src/C1/C1.ino` | Arduino implementation – Scenario C1 |
| 3.4 | `src/C2/C2.ino` | Arduino implementation – Scenario C2 |
| 3.5 | `src/Output/A4.txt` | Execution output for scenario A4 |
| 3.6 | `src/Output/B.txt` | Execution output for scenario B |
| 3.7 | `src/Output/C1.txt` | Execution output for scenario C1 |
| 3.8 | `src/Output/C2.txt` | Execution output for scenario C2 |
| 4 | `README.md` | Repository overview and usage instructions |

---

## Features

- **Classic Traffic Light Sequence:**  
  Automatically cycles through:
  - **Red:** 30 seconds  
  - **Green:** 30 seconds  
  - **Orange:** 20 seconds  

- **Real-Time Monitoring:**  
  Live visualization of traffic light status through the ThingSpeak platform.

- **Bi-directional Communication:**
  - **Data Upload:** Sends numeric status values to the cloud:
    - `1` → Red  
    - `2` → Orange  
    - `3` → Green  
  - **Remote Control:** Reads values from **Field 8** of the ThingSpeak channel to switch between normal operation and standby mode.

- **Hardware Protection:**  
  Uses a **voltage divider** to safely step down Arduino 5V signals to 3.3V for the ESP-01 module.

---

## Hardware Components

- **Microcontroller:** Arduino UNO  
- **WiFi Connectivity:** ESP-01 (ESP8266) module  
- **Circuitry:** Breadboard, jumper wires  
- **Passive Components:** Resistors (used for voltage division)

---

## System Architecture

### 1. Arduino Programming
The Arduino is programmed in **C/C++** to control both the traffic light logic and network communication.

- **Timing Control:**  
  Uses the `delay()` function to define each light phase.
- **Network Communication:**  
  Sends **AT commands** to the ESP-01 to:
  - Connect to WiFi
  - Open TCP connections
  - Transmit HTTP requests to ThingSpeak

---

### 2. ThingSpeak Integration
A dedicated ThingSpeak channel (**ID: 2749755**) is used for data visualization and control.

- **Field 1:** Red signal status  
- **Field 2:** Orange signal status  
- **Field 3:** Green signal status  
- **Field 8:** Alert signal / remote control switch

---

## Logic and Analysis
The system periodically retrieves data from ThingSpeak in **JSON format** to determine operating mode:

- **Value `0`:**  
  Normal traffic light sequence (Red → Green → Orange)
- **Value `1`:**  
  Standby / out-of-service mode (Orange light only)

This allows remote intervention without physical access to the system.

---

## Setup Requirements

### Hardware Setup
- Connect the Arduino UNO to the ESP-01 module.
- Ensure:
  - **Arduino TX → ESP-01 RX** through a **voltage divider** (5V → 3.3V)
  - Proper common ground (GND)

### Network Configuration
- Configure WiFi credentials in the Arduino code using:
AT+CWJAP="SSID","PASSWORD"

yaml
Αντιγραφή κώδικα

### ThingSpeak Configuration
- Insert the following into the code:
- **Write API Key:** For uploading traffic light status
- **Read API Key:** For reading control commands from Field 8

---

## Conclusion
This project demonstrates a practical **IoT-based traffic control system**, combining embedded programming, wirel

---

# Installation & Setup Guide

This guide explains how to install, configure, and run the **IoT Traffic Lights** project using **Arduino UNO**, **ESP-01 (ESP8266)**, and **ThingSpeak**.

---

## Prerequisites

### Hardware Requirements
- Arduino UNO
- ESP-01 (ESP8266) WiFi module
- Breadboard
- Jumper wires (Male–Male, Male–Female)
- Resistors for voltage divider (e.g., 1.8kΩ and 3.3kΩ)
- USB cable (Arduino ↔ PC)

> **Warning:**  
> ESP-01 uses **3.3V logic**. A **voltage divider** is required between Arduino TX (5V) and ESP-01 RX.

---

### Software Requirements
- Operating System: Windows / Linux / macOS
- Arduino IDE (v1.8.x or newer)
- USB drivers (CH340 or ATmega16U2, depending on board)
- Internet connection

---

### Online Services
- ThingSpeak account: https://thingspeak.com

---

## Software Installation

### Install Arduino IDE
1. Download from: https://www.arduino.cc/en/software
2. Install with default options.
3. Launch Arduino IDE.

---

### Verify Arduino Connection
1. Connect Arduino UNO via USB.
2. In Arduino IDE:
   - **Tools → Board → Arduino UNO**
   - **Tools → Port → Select correct port**
3. Upload the *Blink* example to verify functionality.

---

## Hardware Setup

### ESP-01 Wiring

| Arduino UNO | ESP-01 | Description |
|------------:|--------|-------------|
| 3.3V | VCC | Power |
| GND | GND | Common ground |
| TX (Pin 1) | RX | Via voltage divider |
| RX (Pin 0) | TX | Direct |
| 3.3V | CH_PD | Enable |

#### Voltage Divider
- Arduino TX → 1.8kΩ → ESP-01 RX
- ESP-01 RX → 3.3kΩ → GND

---

## ThingSpeak Configuration

### Create Channel
1. Log in to ThingSpeak.
2. Create a new channel.
3. Enable fields:
   - Field 1: Red
   - Field 2: Orange
   - Field 3: Green
   - Field 8: Remote Control

---

### Obtain API Keys
- Navigate to **Channel Settings → API Keys**
- Copy:
  - Write API Key
  - Read API Key

---

## Repository Setup

```bash
git clone https://github.com/Internet-of-Things-aka-Uniwa/Traffic-Lights.git
cd Traffic-Lights
```

---

## Arduino Code Configuration
### Open a Scenario
Open one of the following in Arduino IDE:
- `src/A4/A4.ino`
- `src/B/B.ino`
- `src/C1/C1.ino`
- `src/C2/C2.ino`

### Configure WiFi
```c
AT+CWJAP="YOUR_SSID","YOUR_PASSWORD"
```

### Configure ThingSpeak Keys
```c
String writeAPIKey = "YOUR_WRITE_API_KEY";
String readAPIKey  = "YOUR_READ_API_KEY";
```

---

## Upload & Execution
### Upload Code
1. Temporarily disconnect ESP-01 TX/RX.
2. Click Upload in Arduino IDE.
3. Reconnect ESP-01 after upload completes.

---

## Monitor Serial Output
1. Open Tools → Serial Monitor
2. Set correct baud rate (as defined in code).
3. Verify:
    - WiFi connection
    - Data transmission to ThingSpeak
    - JSON responses

---

## System Operation
### Normal Mode
- ThingSpeak Field 8 = 0
- Sequence: Red → Green → Orange

### Standby Mode
- ThingSpeak Field 8 = 1
- Orange light only

---

## Troubleshooting
- ESP-01 not responding: Check 3.3V supply and voltage divider
- No ThingSpeak data: Verify API keys and WiFi credentials
- Upload errors: Disconnect ESP-01 TX/RX during upload

---

## Open the Documentation
1. Navigate to the `docs/` directory
2. Open the report corresponding to your preferred language:
    - English: `Electrical-Signal-Light.pdf`
    - Greek: `Ηλεκτρικός-Φωτεινός-Σηματοδότης.pdf`

