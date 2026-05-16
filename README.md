# High-Transmission-Line-Inspection-Bot

**About This Repository**

This repository contains the embedded firmware and wireless control architecture developed for the High Transmission Line Inspection Bot — a robotic platform designed to traverse overhead high-voltage transmission lines and perform real-time visual inspection. The ESP32 microcontroller serves as the central wireless control unit, enabling low-latency Wi-Fi-based command transmission between the operator interface and the robot's actuation subsystems.
The firmware manages directional movement via high-torque DC motors, mechanism actuation through servo motors, and wireless telemetry over a lightweight HTTP server hosted by the ESP32 itself. The system is designed for reliable remote operation in environments where direct physical access is hazardous or operationally infeasible.

**Project Objective**

Manual inspection of high-voltage overhead transmission lines presents significant safety risks and operational inefficiencies. This project addresses that challenge by deploying a remotely operated robotic platform capable of traversing live conductor lines and inspecting components such as insulators, spacers, clamps, and conductor surfaces for physical anomalies.
The ESP32-based control system provides:

Reliable wireless command reception over Wi-Fi

Real-time actuation of drive and mechanism servos

A web-accessible control interface operable from any networked device

A modular embedded architecture suitable for future sensor and vision integration
