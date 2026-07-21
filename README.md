<div align="center">

# 🚙 BMW I/K Bus — Interface for Classic BMW

**A complete solution for interfacing with the BMW I-Bus and K-Bus using Arduino, ESP32, STM32 or Raspberry Pi Pico — sniff bus traffic, read live data and inject commands to control lights, windows, locks and multimedia on classic BMWs (E38, E39, E46, E53 and more).**

![GitHub Repo stars](https://img.shields.io/github/stars/muki01/I-K_Bus?style=flat)
![GitHub forks](https://img.shields.io/github/forks/muki01/I-K_Bus?style=flat)
![GitHub Issues or Pull Requests](https://img.shields.io/github/issues/muki01/I-K_Bus?style=flat)
![GitHub License](https://img.shields.io/github/license/muki01/I-K_Bus?style=flat)
![GitHub last commit](https://img.shields.io/github/last-commit/muki01/I-K_Bus)
![Arduino](https://img.shields.io/badge/Arduino-00979D?logo=arduino&logoColor=white)
![ESP32](https://img.shields.io/badge/ESP32-000000?logo=espressif&logoColor=red)
![BMW](https://img.shields.io/badge/Vehicle-BMW-0066B1)

</div>

---

## 🌟 Overview

An Arduino / ESP32 interface and library for the **BMW I-Bus (Instrumentation Bus)** and **K-Bus (Body Bus)**. It lets you **sniff bus traffic, decode messages in real time, and inject commands** to control lights, windows, locks and multimedia modules on classic BMWs — using microcontrollers like **Arduino, ESP32, STM32 or Raspberry Pi Pico**.

The I/K-Bus is a **single-wire serial protocol** used in classic BMW models (E38, E39, E46, E53, etc.), operating at **9600 baud, 8E1 (even parity)**. This repository contains the source code, an Arduino library and hardware schematics needed to bridge this automotive protocol with modern development boards.

## 💼 Hire Me

I design custom automotive diagnostic tools, firmware and apps — this is what I do professionally. Whether you need a full product or just the communication layer, I can help.

- **Custom protocol implementation** — BMW I/K-Bus, K-Line (ISO 9141-2 / KWP2000), CAN bus, and other manufacturer-specific protocols (VAG KW1281, and more)
- **Custom bus & protocol communication code** — low-level drivers and communication routines for any automotive bus or proprietary/custom protocol you need
- **ECU security access** — seed-key (security access) algorithms and unlock routines for KWP2000 / UDS ECUs
- **Custom mobile & desktop apps** — Android / iOS / web companion apps to visualize, log and control your device
- **Bespoke hardware** — diagnostic shields & PCBs designed around your requirements
- **ECU communication & reverse engineering** — bus sniffing, packet decoding, module control, undocumented buses
- **Embedded firmware** — Arduino, ESP32, ESP8266, STM32, Raspberry Pi Pico

Need something else related to **automotive communication or electronics**? Just reach out — if it involves cars, buses or embedded hardware, I can most likely help.

**Have a project in this space?** → 📧 **[muksin.muksin04@gmail.com](mailto:muksin.muksin04@gmail.com)**

## ✨ Features

**Bus Communication**
- 🔍 **Real-time sniffing** — monitor and decode every message on the bus.
- 🔁 **Bi-directional control** — not just reading; inject packets to control car modules.
- 📦 **Packet decoding** — source, length, destination and data parsing via the `IbusSerial` library.
- 💤 **Sleep / wake handling** — automatic bus sleep support to avoid draining the battery.

**Hardware & Platforms**
- 🧩 **Multi-platform** — tested on Arduino Nano; compatible with ESP32, STM32, Raspberry Pi Pico and more.
- 🛠️ **Hardware flexibility** — schematics for optocouplers, TH3122 / ELMOS and MCP2025.
- ⚡ **Standard bus timing** — 9600 baud, 8E1, single-wire, matching the classic-BMW spec.

### 📨 Message Frame Format

Every I/K-Bus message follows the same structure:

| Byte | Field | Description |
|------|-------|-------------|
| 0 | **Source** | Sender module ID |
| 1 | **Length** | Number of bytes from *Destination* to *Checksum* |
| 2 | **Destination** | Target module ID |
| 3 … n-1 | **Data** | Command byte + payload |
| n | **Checksum** | XOR of all preceding bytes |

## 📡 Supported BMW Models

| Model | Series | Period | I-Bus | K-Bus |
| :-- | :-- | :-- | :-- | :-- |
| E31 | 8 Series | 1989–1999 | ✅ | |
| E38 | 7 Series | 1999–2001 | ✅ | ✅ |
| E39 | 5 Series | 1995–2004 | ✅ | ✅ |
| E46 | 3 Series | 1997–2006 | | ✅ |
| E52 | Z8 | 2000–2003 | | ✅ |
| E53 | X5 | 1999–2006 | ✅ | ✅ |
| E83 | X3 | 2003–2010 | | ✅ |
| E85 | Z4 | 2002–2008 | | ✅ |
| E87 | 1 Series | 2004–2013 | | ✅ |

## 🚀 Quick Start

First, build a bus interface from one of the [Schematics](#-schematics-for-communication) below and tap into the bus — see [Where to Connect](#-where-to-connect-to-the-k-bus-bmw-e46-example). Then install the library and pick an example that fits your goal:

1. **Install the library** — [BMW I/K Bus Library](https://github.com/muki01/I-K_Bus_Library) in the Arduino IDE.
2. **Choose an example sketch:**

### 🔍 Just reading / sniffing? → `Basic_Code`
Reads and decodes all traffic on the bus and prints it to a debug serial — the fastest way to see what's happening.

👉 **Sketch:** [`Codes/Basic_Code`](Codes/Basic_Code)

### 🎛️ Controlling an E46? → `E46_KBus_Code`
Example for reading and sending commands to K-Bus modules on the BMW E46.

👉 **Sketch:** [`Codes/E46_KBus_Code`](Codes/E46_KBus_Code)

3. **Select your board** (Arduino Nano, ESP32, …), set the COM port, and upload.

> ⚠️ **Disclaimer:** This is a hobby / development project. I am not responsible for any issues or damage that may occur during testing. Injecting packets onto a live vehicle bus can affect its modules — proceed with caution and at your own risk.

## 🔌 Where to Connect to the K-Bus (BMW E46 Example)

Common, practical places to tap the K-Bus wiring:
- **CD Changer connector** – trunk
- **Radio K-Bus wiring**
- **K-Bus junction block** (above the fuse box)

### 1. CD Changer Connector
The easiest place to connect an Arduino or similar interface.
- Provides **+12V, GND and K-Bus** in one connector
- CD changer is optional, but the wiring is usually present
- Located in the trunk, driver's side, behind the trim

> Connector: **X18180** (BMW WDS) · K-Bus wire: **White/Red with yellow dots** · Ground: **Brown** · 12V: **Red/Green**

<img src="https://github.com/user-attachments/assets/ab4edfaf-d4b3-4959-bf2b-50629cbed732" width="30%">
<img src="https://github.com/user-attachments/assets/97caebba-a70d-4942-9719-27ab205abc5b" width="30%">
<img src="https://github.com/user-attachments/assets/533fbc3a-88c3-4680-a70a-eb40f322cd6e" width="30%">

### 2. K-Bus Junction Block (above the fuse box)
A central distribution point for the K-Bus.
- K-Bus wire color: **White/Red with yellow dots**
- Tap the K-Bus here; take **+12V and GND** from another location.

<img width="30%" src="https://github.com/user-attachments/assets/ec82d99d-8513-423b-8a5d-ba343372bc39" />
<img width="23%" src="https://github.com/user-attachments/assets/8826ea1a-691a-4a71-bc7f-ec63ecb5e486" />
<img width="33%" src="https://github.com/user-attachments/assets/f1cdddcf-d070-4638-a611-9fd835a9931c" />
<img width="30%" src="https://github.com/user-attachments/assets/2e64254e-ea59-4758-a92b-0ae215f1ce00" />

## 🛠️ Schematics for Communication

Interfacing a 5V / 3.3V microcontroller with the 12V single-wire bus requires level shifting. Pick the approach that suits your project:

### 🔹 Optocouplers
<img src="https://raw.githubusercontent.com/muki01/I-K_Bus/main/Schematics/Optocoupler%20Schematic.png" width="60%">

A simple, low-cost and electrically isolated interface — great for prototyping and safe experimentation.

### 🔹 TH3122.4 or ELMOS 10026B
<img src="https://raw.githubusercontent.com/muki01/I-K_Bus/main/Schematics/TH3122.4%20or%20ELMOS%2010026B.png" width="60%">

Dedicated BMW bus transceiver ICs with built-in level shifting and protection — the most reliable, production-grade option.

### 🔹 MCP2025
<img src="https://raw.githubusercontent.com/muki01/I-K_Bus/main/Schematics/MCP2025.png" width="60%">

A LIN transceiver-based interface — a compact, standards-based alternative.

## 🔗 Related Projects

Part of a full automotive communication & diagnostics ecosystem:

| Firmware & Readers | Libraries | Manufacturer Protocols | UI |
|--------------------|-----------|------------------------|-----|
| [OBD2 K-line Reader](https://github.com/muki01/OBD2_K-line_Reader) | [OBD2 K-Line Library](https://github.com/muki01/OBD2_KLine_Library) | [BMW I/K Bus](https://github.com/muki01/I-K_Bus) | [OBD2 Diagnostic UI](https://github.com/muki01/OBD2-Diagnostic-UI) |
| [OBD2 CAN Bus Reader](https://github.com/muki01/OBD2_CAN_Bus_Reader) | [OBD2 CAN Bus Library](https://github.com/muki01/OBD2_CAN_Bus_Library) | [VAG KW1281](https://github.com/muki01/VAG_KW1281) | |

## ☕ Support My Work

If you enjoy my projects and want to support me, you can do so through the links below:

[![Buy Me A Coffee](https://img.shields.io/badge/-Buy%20Me%20a%20Coffee-FFDD00?style=for-the-badge&logo=buy-me-a-coffee&logoColor=black)](https://www.buymeacoffee.com/muki01)
[![PayPal](https://img.shields.io/badge/-PayPal-00457C?style=for-the-badge&logo=paypal&logoColor=white)](https://www.paypal.com/donate/?hosted_button_id=SAAH5GHAH6T72)
[![GitHub Sponsors](https://img.shields.io/badge/-Sponsor%20Me%20on%20GitHub-181717?style=for-the-badge&logo=github)](https://github.com/sponsors/muki01)

---

## 📬 Contact

For custom development, job offers, collaboration, sponsorship, or purchasing my devices, feel free to reach out.

📧 **Email:** [muksin.muksin04@gmail.com](mailto:muksin.muksin04@gmail.com)

---

<div align="center">

Created by [**Muki**](https://github.com/muki01) · If you find this useful, consider giving it a ⭐

</div>
