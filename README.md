# Mealy Pattern Detector

## Description
This project is a Mealy machine-based serial bit pattern detector designed to detect the sequence `1111` in a 15-bit input sequence. The detected sequence is displayed using a 7-segment display (common anode). The project uses JK flip-flops for the state machine and an Arduino Nano for input and clock signal generation.

## Components
- JK Flip-Flops
- 7-segment Display (common anode)
- Arduino Nano
- Push Buttons
- Breadboard and Connecting Wires

## Functionality
- **Preloaded Sequences**: The system has 3 preloaded 15-bit sequences.
- **User-defined Sequence**: Users can input their own 15-bit sequence using push buttons.
- **Detection**: On pressing the start button, the Arduino sends the 15-bit sequence to the circuit. If the sequence `1111` is detected, the 7-segment display shows `1`; otherwise, it shows `0`.

## Circuit Diagram
![image](https://github.com/user-attachments/assets/8c31b9d6-fb52-487a-9be5-0511d04d4fe6)
## Arduino Simulation
![image](https://github.com/user-attachments/assets/c179dd1a-3737-47ce-a337-1127ba1f4fcd)
## Simulation link of Arduino 
https://wokwi.com/projects/403477979726779393



