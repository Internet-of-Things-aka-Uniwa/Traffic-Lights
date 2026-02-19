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

# INSTALL

## Traffic Light Sequence with Arduino UNO, ESP-01 and ThingSpeak

This guide explains how to install, configure, and run the **IoT Traffic Lights** project using **Arduino UNO**, **ESP-01 (ESP8266)**, and **ThingSpeak**.

---

## 1. Prerequisites

### 1.1 Hardware Requirements

- Arduino UNO
- ESP-01 (ESP8266) WiFi module
- Breadboard
- Jumper wires (Male–Male, Male–Female)
- Resistors for voltage divider (e.g., 1.8kΩ and 3.3kΩ)
- USB cable (Arduino ↔ PC)

> **Warning:**  
> ESP-01 uses **3.3V logic**. A **voltage divider** is required between Arduino TX (5V) and ESP-01 RX.

---

## 2. Software Requirements

- Operating System: Windows / Linux / macOS
- Arduino IDE (v1.8.x or newer)
- USB drivers (CH340 or ATmega16U2, depending on board)
- Internet connection

---

## 3. Online Services

- ThingSpeak account: https://thingspeak.com

---

## 4. Software Installation

### 4.1 Install Arduino IDE

1. Download from: https://www.arduino.cc/en/software
2. Install with default options.
3. Launch Arduino IDE.

---

## 5. Verify Arduino Connection

1. Connect Arduino UNO via USB.
2. In Arduino IDE:
   - **Tools → Board → Arduino UNO**
   - **Tools → Port → Select correct port**
3. Upload the _Blink_ example to verify functionality.

---

## 6. Hardware Setup

### 6.1 ESP-01 Wiring

| Arduino UNO | ESP-01 | Description         |
| ----------: | ------ | ------------------- |
|        3.3V | VCC    | Power               |
|         GND | GND    | Common ground       |
|  TX (Pin 1) | RX     | Via voltage divider |
|  RX (Pin 0) | TX     | Direct              |
|        3.3V | CH_PD  | Enable              |

### 6.2 Voltage Divider

- Arduino TX → 1.8kΩ → ESP-01 RX
- ESP-01 RX → 3.3kΩ → GND

---

## 7. ThingSpeak Configuration

### 7.1 Create Channel

1. Log in to ThingSpeak.
2. Create a new channel.
3. Enable fields:
   - Field 1: Red
   - Field 2: Orange
   - Field 3: Green
   - Field 8: Remote Control

---

## 8. Obtain API Keys

- Navigate to **Channel Settings → API Keys**
- Copy:
  - Write API Key
  - Read API Key

---

## 9. Repository Setup

```bash
git clone https://github.com/Internet-of-Things-aka-Uniwa/Traffic-Lights.git
cd Traffic-Lights
```

---

## 10. Arduino Code Configuration

### 10.1 Open a Scenario

Open one of the following in Arduino IDE:

- `src/A4/A4.ino`
- `src/B/B.ino`
- `src/C1/C1.ino`
- `src/C2/C2.ino`

### 10.2 Configure WiFi

```c
AT+CWJAP="YOUR_SSID","YOUR_PASSWORD"
```

### 10.3 Configure ThingSpeak Keys

```c
String writeAPIKey = "YOUR_WRITE_API_KEY";
String readAPIKey  = "YOUR_READ_API_KEY";
```

---

## 11. Upload & Execution

### 11.1 Upload Code

1. Temporarily disconnect ESP-01 TX/RX.
2. Click Upload in Arduino IDE.
3. Reconnect ESP-01 after upload completes.

---

## 12. Monitor Serial Output

1. Open Tools → Serial Monitor
2. Set correct baud rate (as defined in code).
3. Verify:
   - WiFi connection
   - Data transmission to ThingSpeak
   - JSON responses

---

## 13. System Operation

### 13.1 Normal Mode

- ThingSpeak Field 8 = 0
- Sequence: Red → Green → Orange

### 13.2 Standby Mode

- ThingSpeak Field 8 = 1
- Orange light only

---

## 14. Troubleshooting

- ESP-01 not responding: Check 3.3V supply and voltage divider
- No ThingSpeak data: Verify API keys and WiFi credentials
- Upload errors: Disconnect ESP-01 TX/RX during upload

---

## 15. Open the Documentation

1. Navigate to the `docs/` directory
2. Open the report corresponding to your preferred language:
   - English: `Electrical-Signal-Light.pdf`
   - Greek: `Ηλεκτρικός-Φωτεινός-Σηματοδότης.pdf`
