# Phoneme-Articulation-Localization: 3D Spatial Speech Articulation Platform

[![Version](https://img.shields.io/badge/version-v3.1.3-blue)](https://github.com/slam-prog/Phoneme-Articulation-Localization/releases)
[![License](https://img.shields.io/badge/license-HEUL-brightgreen)](https://github.com/slam-prog/Phoneme-Articulation-Localization/blob/main/LICENSE)
[![Platform](https://img.shields.io/badge/platform-RP2040-red)](https://www.raspberrypi.com/products/rp2040/)
[![Status](https://img.shields.io/badge/status-active-brightgreen)](https://github.com/slam-prog/Phoneme-Articulation-Localization)
[![Accuracy](https://img.shields.io/badge/accuracy-%3C%201mm-brightgreen)](https://github.com/slam-prog/Phoneme-Articulation-Localization/blob/main/simulation/SIMULATION_RESULTS.md)

---

## 🌐 Vision & Concept

**Phoneme-Articulation-Localization** is an open-source, low-cost hardware and software platform designed to localize and classify vocal tract articulation points in real-time using 3D spatial audio processing. By transforming acoustic time-delays into 3D spatial coordinates \((X, Y, Z)\), the system enables precise tracking of speech articulation without relying on expensive imaging equipment.

### 🎯 Why This Project Matters

- **For Humanity**: The primary goal is to assist individuals with speech disorders (e.g., Aphasia) by providing real-time, non-invasive biofeedback for speech rehabilitation.
- **Cross-Lingual**: By focusing on the **biomechanics of speech** (where sounds are produced), the system can recognize phonemes regardless of language, paving the way for universal real-time translation.
- **Open Technology**: All hardware, software, and algorithms are open-source, allowing anyone to build upon, modify, or use the platform for research and clinical applications.

### 🚀 Future Vision (v4.0)

We are actively developing the fourth version of the platform, which will feature a **5th microphone** arranged in a symmetric 5‑microphone cube array. This enhancement will:
- Improve **Z‑axis accuracy** (anatomical depth) by up to 60%.
- Reduce errors caused by head movement through 3D microphone distribution.
- Enhance system stability in noisy environments.

### ⚙️ How It Works (Simplified)

1. **Sound Capture**: Five microphones (arranged in a 3D array) capture speech from the speaker.
2. **Time‑Difference Measurement**: The RP2040 microcontroller computes the microsecond‑level time differences between microphone arrivals.
3. **Spatial Trilateration**: Using the **Tanweer Algorithm**, these time differences are converted into 3D spatial coordinates \((X, Y, Z)\) within the vocal tract.
4. **Anatomical Zone Classification**: The coordinates are mapped to **6 distinct anatomical zones** (e.g., Lips, Dental, Palatal, Velar, Throat) to identify the phoneme.
5. **Output**: Coordinates and zone labels are transmitted wirelessly via Bluetooth Low Energy (BLE) or USB to any device (phone, computer) for applications such as real‑time translation, device control, and medical diagnostics.

---

## ⚡ Quick Start

This guide explains how to set up a prototype of the Phoneme‑Articulation‑Localization platform and read data in under 10 minutes.

### 1️⃣ Prerequisites

**Hardware**:
- 1 × **Arduino Nano RP2040 Connect** (or any RP2040‑based board with BLE).
- 5 × **INMP441** digital microphones (I2S interface).
- 1 × 3.7V Li‑Po battery (600mAh) with TP4056 charging module.
- Connecting wires and soldering equipment.

**Software**:
- **Arduino IDE** (version 1.8.19 or later).
- Board package: **Raspberry Pi Pico/RP2040** (install via Boards Manager).
- Library: **ArduinoBLE** (install via Library Manager).

### 2️⃣ Circuit Assembly

Connect the five microphones to the board according to the table below (pins may be adjusted as needed):

| Microphone | Function | Arduino Pin |
| :--- | :--- | :--- |
| M1 | TDOA - Top‑Left | D2 |
| M2 | TDOA - Top‑Right | D3 |
| M3 | TDOA - Bottom‑Left (Reference) | D4 |
| M4 | TDOA - Bottom‑Right | D5 |
| M5 | Proximal Reference (Close to Mouth) | D6 |

> **Note**: Ensure all microphones share a common 3.3V and GND connection.

### 3️⃣ Flashing the Firmware

1. Clone the repository:
   ```bash
   git clone https://github.com/slam-prog/Phoneme-Articulation-Localization.git
Open firmware/kinetic_vocal_core.ino in Arduino IDE.

Select board: Raspberry Pi Pico from Tools → Board.

Click Upload to flash the firmware.

4️⃣ Testing
Open the Serial Monitor (Tools → Serial Monitor) and set baud rate to 115200.

Speak any sound (e.g., "ah" or "bee") near the microphone array.

You should see output like:

text
X:12.4,Y:46.2,Z:8.1,LIPS
X:-0.5,Y:2.1,Z:52.4,THROAT
Use a BLE scanner app (e.g., nRF Connect) to discover the device PhonemeCore and read the 2A19 characteristic, which contains the same data.

✅ What This Means
Congratulations! You have successfully run the platform. The data represents the 3D spatial coordinates 
(
X
,
Y
,
Z
)
(X,Y,Z) of your speech articulation points, along with the classified anatomical zone.

📐 How It Works
1. Microphone Array Topology
The five microphones are arranged in a symmetric 3D configuration with a 60 mm × 60 mm base and a proximal reference anchor:

text
                     +Z (Vertical)
                      |
                      |   [M4] (0, 0, d)
                      |
                      |
                      |_______________________ +Y (Azimuth)
                     / 0,0,0
                    /  [M1] (Central) \
                   /                    \  [M3] (0, d, 0)
                  /                      \
                 /                        \
               +X                          \
         (Width)                           \
         [M2] (d, 0, 0)                     \
                                              ▼
                                      [M5] (Proximal Reference)
                                    (Close‑talk Reference)
                                     [T₀ - Time‑of‑Flight Anchor]
2. Time‑Difference of Arrival (TDOA)
When the user speaks, the sound wave reaches each microphone at a different time. The microcontroller computes these time differences with microsecond precision using hardware interrupts.

3. Spatial Trilateration (Tanweer Algorithm)
Using the Tanweer Algorithm, the time differences are converted into 3D coordinates 
(
X
,
Y
,
Z
)
(X,Y,Z) via closed‑form algebraic equations (no iterative solvers).

4. 3D Kalman Filter (Optional)
A 3D Kalman filter can be applied to smooth the coordinates and reduce noise from head movement and environmental vibrations.

5. Anatomical Zone Classification
The coordinates are mapped to 6 anatomical zones based on predefined boundaries:

Zone	Y‑Range (mm)	Z‑Range (mm)	Example Phonemes
LIPS	45 – 60	0 – 15	/p/, /b/, /m/
DENTAL	30 – 45	15 – 25	/t/, /d/, /n/
ALVEOLAR	20 – 35	25 – 35	/r/, /ʃ/, /tʃ/
PALATAL	15 – 25	35 – 45	/j/, /c/
VELAR	10 – 20	45 – 55	/k/, /g/, /ŋ/
THROAT	0 – 10	55 – 65	/h/, /q/
For more details, see ANATOMICAL_ZONES.md.

📊 Results & Performance
Version	X Accuracy (mm)	Y Accuracy (mm)	Z Accuracy (mm)	Latency (ms)
v3.1.3 (Current)	±2.0	±2.0	±5.0 (Indirect)	<1
v4.0 (Experimental)	±2.0	±2.0	±2.0 (Direct)	<1.5
Performance Comparison: v4.0 improves Z‑axis accuracy by 60% thanks to the 5‑microphone cube array.

Noise Resilience: The system maintains stability even in environments with up to 15 dB SNR.

For detailed simulation results, see simulation/SIMULATION_RESULTS.md.

🛠️ Installation & Development
Recommended Development Environment
Arduino IDE (version 1.8.19 or later) with Raspberry Pi Pico/RP2040 board package.

PlatformIO (optional) for advanced developers.

Code Structure
firmware/kinetic_vocal_core.ino: Core firmware (v3.1.3).

firmware/tanweer_core.cpp: C++ implementation of the Tanweer algorithm for RP2040.

examples/v4_experimental/: Experimental code for v4.0.

simulation/: Python simulation environment.

python/: Python library for reading device data.

Customization
Change Microphone Pins: Modify pin definitions in the firmware.

Adjust Zone Boundaries: Update y and z thresholds in classifyZone().

Change Baud Rate: Update Serial.begin() in setup().

📦 Hardware Design
Core Components
Processor: Arduino Nano RP2040 Connect (or equivalent).

Microphones: 5 × INMP441 (I2S interface).

Battery: 3.7V Li‑Po, 600mAh with TP4056 charging module.

Enclosure: Open‑source 3D‑printable design (available in /hardware).

Design Files
Schematic: [Link to PDF or image].

PCB Files: [Link to KiCad or Eagle files].

3D Models: [Link to STL folder].

🤝 Integration with AI & Tri‑Party Partnership
Partnerships
This project is the result of a unique tri‑party collaboration:

Human Lead (Engineer Najib): Mechanical design, physical framework, and project management.

Google AI (Gemini Core): Computational core, mathematical algorithms, and performance optimisation.

DeepSeek AI: Hardware optimisation, hybrid circuits, and SDK development.

Integration Examples
With Google Cloud AI:

Use Google Speech‑to‑Text to convert spatial outputs to text.

Use Google Translation API for real‑time cross‑lingual translation.

(Examples will be added in /examples/integration).

With DeepSeek AI:

Use the official Python library to read device data.

Analyse hierarchical fingerprints for medical diagnostics.

📚 Full Documentation
User Manual: Daily operation and usage instructions.

Developer Guide: Code structure, contribution guidelines, and customisation.

API Reference: Data format and helper libraries.

Technical Evaluation: Mathematics and physics behind the system.

Anatomical Zones: Full anatomical zone classification details.

🤝 Contributing & Community
We welcome contributions! To get involved:

Read the Contributing Guide.

Explore open issues.

Join our discussions on GitHub Discussions or the community Discord (announcement coming soon).

📜 License
This project is licensed under the Humanitarian & Ethical Use License (HEUL) v1.0, ensuring open access while prohibiting harmful applications. For full details, see the LICENSE file.

"Technology should be a tree of goodness, from which all humans benefit, and which serves the dignity and well‑being of every person."

Quick Links:

Main Repository

Releases

Simulation Results
