# Self Stabilizing Boat using Reaction Wheel + BLDC + BNO055 + VESC

## Overview

This project is a single-axis self-Stabilizing boat stabilization prototype using:

- ESP8266
- BNO055 IMU Sensor
- VESC BLDC Controller
- BLDC Motor with Reaction Wheel
- Blynk IoT Monitoring

The system reads the roll angle from the BNO055 sensor and dynamically changes BLDC motor RPM through VESC UART communication to counteract tilt.

The project demonstrates the core working principle of:

- Reaction wheel stabilization
- Anti-roll stabilization
- Gyroscopic stabilization
- Flywheel balancing systems

---

# Features

- Single-axis roll stabilization
- Real-time angle correction
- BLDC motor RPM control using VESC UART
- Blynk IoT graph monitoring
- Adjustable dead zone
- Smooth RPM proportional response
- Real-time serial debugging
- Lightweight ESP8266 implementation

---

# Hardware Used

| Component | Description |
|---|---|
| ESP8266 NodeMCU | Main controller |
| BNO055 | Orientation sensor |
| VESC | BLDC motor controller |
| BLDC Motor | Reaction wheel motor |
| Flywheel | Stabilization inertia wheel |
| Power Supply | Motor + controller supply |

---

# Wiring

## VESC UART

| ESP8266 | VESC |
|---|---|
| D5 | TX |
| D6 | RX |
| GND | GND |

---

## BNO055 I2C

| ESP8266 | BNO055 |
|---|---|
| D1 | SDA |
| D2 | SCL |
| 3.3V | VIN |
| GND | GND |

---

# Blynk IoT Setup

## Virtual Pins

| Virtual Pin | Function |
|---|---|
| V0 | Angle Graph |
| V1 | RPM Graph |

---

## Recommended Widgets

### SuperChart

Add:

- V0 → Angle
- V1 → RPM

Recommended update interval:

- 100 ms

---

# Working Principle

1. BNO055 measures boat roll angle.
2. ESP8266 processes tilt data.
3. If tilt exceeds dead zone:
   - RPM increases proportionally.
   - BLDC motor spins reaction wheel.
4. Reaction wheel produces counter torque.
5. Boat attempts to stabilize.
6. Angle and RPM are plotted live using Blynk.

---

# Stabilization Logic

The stabilization logic used:

```text
Small angle  -> low RPM
Large angle  -> high RPM
Opposite tilt -> opposite motor direction
```

Dead zone prevents unnecessary corrections near zero degrees.

---

# Tuning

## Dead Zone

```cpp
if(abs(angle) <= 3)
```

Increase:
- less sensitivity
- more stable

Decrease:
- more responsive
- more oscillation risk

---

## RPM Range

```cpp
map(abs(angle),3,30,0,6000)
```

Adjust:

- minimum angle threshold
- maximum angle
- maximum RPM

based on flywheel size and motor power.

---

# Recommended Improvements

Future upgrades:

- ESP32 instead of ESP8266
- MPU6500 interrupt-based reading
- PID control
- Gyroscope damping
- Soft RPM ramping
- Kalman filtering
- Dual reaction wheel system
- Gimbal flywheel system

---

# Known Limitations

This prototype:

- demonstrates stabilization principle
- works best for small disturbances
- is not intended for real marine deployment
- depends heavily on flywheel inertia
- requires careful mechanical balancing

---

# Recommended Flywheel Design

Better stabilization requires:

- larger diameter flywheel
- heavier flywheel
- higher RPM capability
- rigid mounting
- low vibration

---

# Serial Monitor Output

```text
Angle: -4.23 RPM: 1260
Angle: -7.12 RPM: 2340
Angle: 2.01 RPM: 0
```

---

# Required Arduino Libraries

Install:

- ESP8266 Board Package
- Blynk
- Adafruit BNO055
- Adafruit Unified Sensor
- VescUart

---

# Applications

- Boat stabilization prototype
- Reaction wheel experiments
- Gyroscopic balancing systems
- Educational stabilization platform
- Control systems learning

---

# License

MIT License

---

# Author

Self Balancing Boat Reaction Wheel Project
