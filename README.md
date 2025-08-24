# Motor-Control
Simulation of a PWM-based motor control with LCD monitoring, built in SimulIDE and Arduino IDE
This project demonstrates a basic motor control system using an Arduino Uno, simulated in SimulIDE. The motor speed is controlled via PWM, the LCD displays real-time voltage and ON/OFF state, and serial communication (USART) provides logs to the monitor. Includes .sim1 simulation file, Arduino .ino sketch, and compiled .hex file

## 🔧 Features
![Alt text](Layout.png)
- Control motor speed using PWM
- Display motor ON/OFF state and voltage on LCD
- USART logging to serial monitor
- Built in SimulIDE with schematic provided

## 🚀 Project Files
- `src/MotorControl.ino` → Arduino sketch
- `src/MotorControl.hex` → Compiled hex
- `simulide/MotorControl.sim1` → SimulIDE project file
- `docs/schematic.png` → Project schematic screenshot

## ⚠️ Known Issues
- Motor toggle sometimes fails to update correctly.
- USART1 logs are not showing in SimulIDE serial monitor.

(Feel free to fix and submit a PR!)

## ▶️ How to Run
1. Open `MotorControl.sim1` in **SimulIDE**.
2. Upload `MotorControl.hex` into the Arduino board inside SimulIDE.
3. Open the serial monitor to view USART logs.
4. Adjust motor control input to test speed variation.
