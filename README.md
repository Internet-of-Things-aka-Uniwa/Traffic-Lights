<p align="center">
  <img src="https://www.especial.gr/wp-content/uploads/2019/03/panepisthmio-dut-attikhs.png" alt="UNIWA" width="150"/>
</p>

<p align="center">
  <strong>UNIVERSITY OF WEST ATTICA</strong><br>
  SCHOOL OF ENGINEERING<br>
  DEPARTMENT OF COMPUTER ENGINEERING AND INFORMATICS
</p>

<p align="center">
  <a href="https://www.uniwa.gr" target="_blank">University of West Attica</a> ·
  <a href="https://ice.uniwa.gr" target="_blank">Department of Computer Engineering and Informatics</a>
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

</hr>

---

<p align="center">
  Athens, January 2025
</p>

---

<p align="center">
  <img src="https://i.ytimg.com/vi/764bRMvGZR4/maxresdefault.jpg" width="250"/>
</p>

---

# README

## Traffic Light Sequence with Arduino UNO, ESP-01 and ThingSpeak

This project focuses on the development of an **automated traffic light system** using an **Arduino UNO**, integrated with the **ThingSpeak IoT platform** for real-time monitoring and remote control. The system simulates a classic traffic light sequence and transmits its operational state to the cloud via an **ESP-01 (ESP8266) WiFi module**.

---

## Table of Contents

| Section | Folder                                     | Description                                        |
| ------: | ------------------------------------------ | -------------------------------------------------- |
|       1 | `assign/`                                  | Assignment material for the Traffic Lights project |
|     1.1 | `assign/Final-Project.pdf`                 | Final project description in English               |
|     1.2 | `assign/Τελικη-Εργασία.pdf`                | Τελική εργασία (Greek)                             |
|       2 | `docs/`                                    | Project documentation and theoretical background   |
|     2.1 | `docs/Electrical-Signal-Light.pdf`         | Electrical traffic light theory (EN)               |
|     2.2 | `docs/Ηλεκτρικός-Φωτεινός-Σηματοδότης.pdf` | Θεωρία ηλεκτρικού φωτεινού σηματοδότη (EL)         |
|       3 | `src/`                                     | Arduino source code and execution outputs          |
|     3.1 | `src/A4/A4.ino`                            | Arduino implementation – Scenario A4               |
|     3.2 | `src/B/B.ino`                              | Arduino implementation – Scenario B                |
|     3.3 | `src/C1/C1.ino`                            | Arduino implementation – Scenario C1               |
|     3.4 | `src/C2/C2.ino`                            | Arduino implementation – Scenario C2               |
|     3.5 | `src/Output/A4.txt`                        | Execution output for scenario A4                   |
|     3.6 | `src/Output/B.txt`                         | Execution output for scenario B                    |
|     3.7 | `src/Output/C1.txt`                        | Execution output for scenario C1                   |
|     3.8 | `src/Output/C2.txt`                        | Execution output for scenario C2                   |
|       4 | `README.md`                                | Repository overview                                |
|       5 | `INSTALL.md`                               | Usage instructions                                 |

---

## 1. Features

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

## 2. Hardware Components

- **Microcontroller:** Arduino UNO
- **WiFi Connectivity:** ESP-01 (ESP8266) module
- **Circuitry:** Breadboard, jumper wires
- **Passive Components:** Resistors (used for voltage division)

---

## 3. System Architecture

### 3.1 Arduino Programming

The Arduino is programmed in **C/C++** to control both the traffic light logic and network communication.

- **Timing Control:**  
  Uses the `delay()` function to define each light phase.
- **Network Communication:**  
  Sends **AT commands** to the ESP-01 to:
  - Connect to WiFi
  - Open TCP connections
  - Transmit HTTP requests to ThingSpeak

---

### 3.2 ThingSpeak Integration

A dedicated ThingSpeak channel (**ID: 2749755**) is used for data visualization and control.

- **Field 1:** Red signal status
- **Field 2:** Orange signal status
- **Field 3:** Green signal status
- **Field 8:** Alert signal / remote control switch

---

## 4. Logic and Analysis

The system periodically retrieves data from ThingSpeak in **JSON format** to determine operating mode:

- **Value `0`:**  
  Normal traffic light sequence (Red → Green → Orange)
- **Value `1`:**  
  Standby / out-of-service mode (Orange light only)

This allows remote intervention without physical access to the system.

---

## 5. Setup Requirements

### 5.1 Hardware Setup

- Connect the Arduino UNO to the ESP-01 module.
- Ensure:
  - **Arduino TX → ESP-01 RX** through a **voltage divider** (5V → 3.3V)
  - Proper common ground (GND)

### 5.2 Network Configuration

- Configure WiFi credentials in the Arduino code using:

```yaml
AT+CWJAP="SSID","PASSWORD"
```

### 5.3 ThingSpeak Configuration

- Insert the following into the code:
- **Write API Key:** For uploading traffic light status
- **Read API Key:** For reading control commands from Field 8

---

## 6. Conclusion

This project demonstrates a practical **IoT-based traffic control system**, combining embedded programming, wireless communication.
