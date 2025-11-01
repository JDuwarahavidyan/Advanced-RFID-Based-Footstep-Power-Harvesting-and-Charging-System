# ⚡ Advanced RFID-Based Footstep Power Harvesting and Charging System

[![Platform](https://img.shields.io/badge/Platform-Arduino%20Mega%202560-blue)]()
[![Simulation](https://img.shields.io/badge/Simulation-Proteus-green)]()
[![Language](https://img.shields.io/badge/Firmware-C%20Embedded-orange)]()
[![RFID](https://img.shields.io/badge/Tech-RFID%20%7C%20Piezoelectric%20Energy-red)]()
[![Status](https://img.shields.io/badge/Status-Completed-success)]()

---

## 🧠 Project Overview
This project focuses on **energy harvesting using footstep pressure** via **piezoelectric transducers**, integrated with **RFID-based user authentication** and **GSM-enabled notifications**.  
The system charges low-power devices such as **mobile phones** while ensuring that **only authorized users** can initiate charging.  

It demonstrates embedded system design principles including:
- Sensor integration
- Power electronics (rectifier, regulation)
- RFID communication
- UART-based GSM interfacing
- Real-time LCD user feedback

---

## 🏫 Academic Details
**Module:** EE6304 – Embedded Systems Design  
**Department:** Electrical and Information Engineering  
**University:** University of Ruhuna, Sri Lanka  
**Submission Date:** 09 October 2024  

**👩‍💻 Group Members**
- Duwarahavidyan Jeganathan 
- Deshan Dissanayake 
- Sachinthana Fernando

---

## ⚙️ Problem Statement
In today’s energy-dependent world, generating sufficient power for portable electronics in public or outdoor environments remains challenging.  
This project introduces a **renewable, self-powered charging system** that harvests **kinetic energy from footsteps** and converts it into usable electrical energy.  

The system uses **RFID for access control**, ensuring that only **authenticated users** can utilize the harvested energy.

---

## 🎯 Core Objectives
1. Harvest mechanical energy using **piezoelectric transducers**.
2. Implement **RFID-based user authentication** to control access.
3. Regulate and store energy using **rectifier and battery modules**.
4. Provide **real-time feedback** through LCD and buzzer indicators.
5. Send **charging notifications** via GSM.
6. Build an embedded system with **minimal energy loss** and **maximum efficiency**.

---

## 🔩 System Architecture

### 🔸 Block Diagram
![Block Diagram](project/img/1.png)

**Block Description**
| Component | Function |
|------------|-----------|
| **Piezoelectric Sensor Array** | Converts mechanical stress into electrical voltage (AC). |
| **Bridge Rectifier + Capacitor** | Converts AC to DC and smoothens the output. |
| **Voltage Regulator (LM7805)** | Provides stable 5V DC output to protect the battery and load. |
| **Rechargeable Battery** | Stores generated energy for later use. |
| **RFID Module (RDM6300)** | Authenticates users using unique card IDs. |
| **Microcontroller (ATmega2560)** | Controls the relay, LCD, buzzer, and GSM module logic. |
| **Relay Driver** | Acts as a switch to allow or restrict charging. |
| **LCD Display (16x2)** | Displays user and charging status. |
| **GSM Module (SIM900)** | Sends SMS alerts for charging status. |
| **USB Output Module** | Provides 5V regulated power to charge the device. |

---

## 💻 Circuit Simulation
![Proteus Simulation](/project/img/2.jpg)

Simulated using **Proteus Design Suite**, which validates:
- UART communication between RFID → MCU → LCD  
- Proper rectification from AC to DC  
- Relay and LED indication logic  
- Energy flow and voltage regulation  

---

## 🔬 Hardware Implementation

### 🧱 Power Generation and Rectification
![Piezo Test](project/img/4.jpg)
The **piezo array** is connected in parallel and series configurations to optimize voltage gain.  
Testing shows ~5–7V DC generation from consistent foot pressure.

### 🔋 Battery Charging Verification
![Battery Test](project/img/5.jpg)
Rechargeable **Li-ion cell** stores the generated power.  
Charging waveform verified using an **oscilloscope** to ensure smooth DC output.

### 💳 RFID & LCD Integration
![RFID Module](project/img/6.jpg)
RFID reader verifies user identity and sends signals to the microcontroller for access control.

### ⚡ Charging Display
![Charging Display](project/img/7.jpg)
LCD shows live charging status and access feedback.

---

## 🧠 Firmware Design

### 📈 Flow of Firmware
![Firmware Flowchart](project/img/3.png)

### 🔹 Firmware Architecture

**Layers:**
1. **Hardware Abstraction Layer (HAL)** – GPIO, UART, and LCD drivers.  
2. **RFID Interface Layer** – Handles RDM6300 frame validation and tag ID extraction.  
3. **Control Logic Layer** – Authenticates user, triggers relay and buzzer actions.  
4. **Application Layer** – Updates LCD, sends GSM messages, and handles timeout.  

---

## 🧾 Firmware Code Snippet
```c
#define ACCESS_GRANTED_TAG_ID 0x39123B

if (tag_id == ACCESS_GRANTED_TAG_ID) {
    Lcd_displayMessage("Access Granted");
    PORTE &= ~(1 << RELAY_PIN); // Enable charging
    _delay_ms(50000);
    PORTE |= (1 << RELAY_PIN);  // Disable after timeout
    Lcd_displayMessage("Charging Complete");
} else {
    Lcd_displayMessage("Access Denied");
    PORTE |= (1 << READ_LED_PIN);
}
```

## 🧠 Key Features
| Feature | Description |
|----------|--------------|
| **Energy Source** | Foot pressure via Piezoelectric effect |
| **Authentication** | RFID (RDM6300/EM18) |
| **Controller** | Arduino Mega 2560 |
| **Storage** | Rechargeable battery |
| **Display** | 16x2 LCD module |
| **Alert System** | Buzzer + GSM message |
| **Charging Output** | 5V USB port |
| **Security** | Authorized access only |

---

## 🧰 Technologies & Components
- Arduino Mega 2560  
- RDM6300 RFID Module  
- GSM SIM900 Module  
- Piezoelectric Discs (x6)  
- Full Bridge Rectifier  
- Rechargeable Battery (3.7V Li-ion)  
- USB Charging Module  
- LCD 16x2 Display  
- Buzzer & Relay  

---

## 📈 Results
- Successfully harvested voltage from foot pressure.  
- Verified real-time charging using oscilloscope.  
- Implemented working RFID authentication and GSM notification.  
- Achieved 5V output for mobile charging.  

---

## 🌱 Future Enhancements
- Integrate **supercapacitors** for higher energy storage.  
- Improve **RFID security** using encrypted tags.  
- Deploy in **public spaces** (bus stands, malls, etc.).  
- Use **IoT monitoring** for energy analytics.

---

## 📚 References
1. A. Babu, *“Advanced Footstep Power Generation System”*, Instructables, 2017.  
2. S. Panghate, *“Advanced Footstep Power Generation System using RFID for Charging”*, IRJET, 2020.


