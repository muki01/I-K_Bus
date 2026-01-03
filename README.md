# 🚙BMW I/K Bus

![GitHub forks](https://img.shields.io/github/forks/muki01/I-K_Bus?style=flat)
![GitHub Repo stars](https://img.shields.io/github/stars/muki01/I-K_Bus?style=flat)
![GitHub Issues or Pull Requests](https://img.shields.io/github/issues/muki01/I-K_Bus?style=flat)
![GitHub License](https://img.shields.io/github/license/muki01/I-K_Bus?style=flat)
![GitHub last commit](https://img.shields.io/github/last-commit/muki01/I-K_Bus)

Unlock the full potential of your BMW's communication network. This project provides a comprehensive solution for interfacing with the BMW I-Bus (Instrumentation Bus) and K-Bus (Body Bus) using microcontrollers like Arduino, ESP32, or STM32.

With this project, you can sniff bus traffic, read real-time sensor data, and send custom commands to control lights, windows, locks, and multimedia systems.

I will share more information about I/K Bus protocol and communication later. Stay tuned 😉.

You can also see my other car projects:
1. [Тhis](https://github.com/muki01/I-K_Bus) project is for BMW with I/K bus system. 
2. [Тhis](https://github.com/muki01/OBD2_CAN_Bus_Reader) project is for Cars with CAN Bus.
3. [Тhis](https://github.com/muki01/OBD2_K-line_Reader) project is for Cars with ISO9141 and ISO14230 protocols.
4. [Тhis](https://github.com/muki01/OBD2_CAN_Bus_Library) is my OBD2 CAN Bus Communication Library for Arduino IDE.
5. [Тhis](https://github.com/muki01/OBD2_KLine_Library) is my OBD2 K-Line Communication Library for Arduino IDE.
6. [Тhis](https://github.com/muki01/VAG_KW1281) project is for VAG Cars with KW1281 protocol.
<!--7. [Тhis](https://github.com/muki01/I-K_Bus_Library) is my I/K Bus Communication Library for Arduino IDE.-->


> [!WARNING] 
> I am not responsible for any issues or damages that may occur during your testing. Please proceed with caution and at your own risk.

## 🌟 Overview
The I/K-Bus is a single-wire, serial communication protocol used in classic BMW models (E38, E39, E46, E53, etc.). It operates at 9600 baud, 8E1 (Even Parity). This repository contains the source code and hardware schematics needed to bridge this automotive protocol with modern development boards.

## 🚀 Key Features
- Real-time Sniffing: Monitor every message sent across the bus.
- Bi-directional Control: Not just reading; you can inject packets to control car modules.
- Multi-Platform Support: Tested on Arduino Nano, but compatible with ESP32, STM32, and Teensy.
- Hardware Flexibility: Includes schematics for Optocouplers, TH3122, and MCP2025.

## 📡Supported BMW Models
This protocol applies to the bus system in the models listed below.

Model|Series|Period|I-Bus|K-Bus
:--|:--|:--|:--|:--
E31|8 Series|1989 - 1999|✅|
E38|7 Series|1999 - 2001|✅|✅
E39|5 Series|1995 - 2004|✅|✅
E46|3 Series|1997 - 2006||✅
E52|Z8|2000 - 2003||✅
E53|X5|1999 - 2006|✅|✅|
E83|X3|2003 - 2010||✅
E85|Z4|2002 - 2008||✅
E87|1 series|2004 - 2013||✅

## 🔌 Where Can We Connect to the K-Bus? (BMW E46 Example)
There are several locations in a BMW E46 where you can tap into the K-Bus wiring. Below are common and practical connection points.

 - CD Changer connector – Trunk
 - Radio K-Bus wiring
 - K-Bus junction block (above fuse box)

#### 1. CD Changer Connector

This is the easiest place to connect an Arduino or similar interface.

- Provides +12V, GND, and K-Bus in one connector
- CD Changer is optional, but the wiring is usually present
- Located in the trunk, driver’s side, behind trim

Connector: X18180 (BMW WDS) </br>
K-Bus wire color: White / Red with Yellow dots </br>
Ground wire color: Brown </br>
12V wire color: Red/ Green </br>

📷 Photos below:

<img src="https://github.com/user-attachments/assets/ab4edfaf-d4b3-4959-bf2b-50629cbed732" width=30%>
<img src="https://github.com/user-attachments/assets/97caebba-a70d-4942-9719-27ab205abc5b" width=30%>
<img src="https://github.com/user-attachments/assets/533fbc3a-88c3-4680-a70a-eb40f322cd6e" width=30%>

#### 2. K-Bus junction block (above fuse box)
The K-Bus line can also be accessed at the junction block located above the fuse box.

- Used as a central distribution point for the K-Bus
- K-Bus wire color: White / Red with Yellow dots

From this point, you can tap the K-Bus line. +12V and GND must be taken from another location.

📷 Photos below:

<img width="30%" src="https://github.com/user-attachments/assets/ec82d99d-8513-423b-8a5d-ba343372bc39" />
<img width="23%" src="https://github.com/user-attachments/assets/8826ea1a-691a-4a71-bc7f-ec63ecb5e486" />
<img width="33%" src="https://github.com/user-attachments/assets/f1cdddcf-d070-4638-a611-9fd835a9931c" />
<img width="30%" src="https://github.com/user-attachments/assets/2e64254e-ea59-4758-a92b-0ae215f1ce00" />

## 🔧 Installation

1. Clone this repository or download the `.zip` file
2. Open the `.ino` file with Arduino IDE
3. Select your board (e.g., Arduino Nano, ESP32)
4. Set the correct COM port and upload the code

## 🛠️Schematics for communication
Interfacing a 5V/3.3V microcontroller with a 12V bus requires level shifting. I have provided three verified methods:

### 🔹Schematic with Optocouplers
<img src="https://github.com/muki01/I-K_Bus/blob/main/Schematics/Optocoupler%20Schematic.png" width=60%>

### 🔹Schematic with TH3122.4 or ELMOS 10026B
<img src="https://github.com/muki01/I-K_Bus/blob/main/Schematics/TH3122.4%20or%20ELMOS%2010026B.png" width=60%>

### 🔹Schematic with MCP2025
<img src="https://github.com/muki01/I-K_Bus/blob/main/Schematics/MCP2025.png" width=60%>

---

## ☕ Support My Work

If you enjoy my projects and want to support me, you can do so through the links below:

[![Buy Me A Coffee](https://img.shields.io/badge/-Buy%20Me%20a%20Coffee-FFDD00?style=for-the-badge&logo=buy-me-a-coffee&logoColor=black)](https://www.buymeacoffee.com/muki01)
[![PayPal](https://img.shields.io/badge/-PayPal-00457C?style=for-the-badge&logo=paypal&logoColor=white)](https://www.paypal.com/donate/?hosted_button_id=SAAH5GHAH6T72)
[![GitHub Sponsors](https://img.shields.io/badge/-Sponsor%20Me%20on%20GitHub-181717?style=for-the-badge&logo=github)](https://github.com/sponsors/muki01)

---

## 📬 Contact

For information, job offers, collaboration, sponsorship, or purchasing my devices, you can contact me via email.

📧 Email: muksin.muksin04@gmail.com

---
