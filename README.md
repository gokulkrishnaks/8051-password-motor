# 8051 Password-Protected DC Motor Control System

This project demonstrates a Password-Protected DC Motor Control System using an 8051 Microcontroller (AT89C51), a 4x3 Keypad, 16x2 LCD Display, and Push Buttons. The user must enter a correct password to control the motor direction via push buttons.

## Project Description
- Microcontroller: AT89C51 (8051 Architecture)
- Features:
  - Password-based user authentication
  - LCD interface to display prompts and status
  - Keypad-based password input
  - DC Motor direction control (Forward, Backward, Stop) using a button
  - Proteus simulation-ready
- Application: Basic Security Control Systems, Access-controlled Motor Drives, Academic Projects.

## Hardware Requirements
- AT89C51: 8051 Microcontroller
- 16x2 LCD: HD44780 compatible
- 4x3 Matrix Keypad: Tactile Switch Keypad
- DC Motor: Generic DC Motor
- Motor Driver Circuit: L293D or equivalent
- Push Buttons: For system activation and motor control
- Power Supply: 5V regulated
- Resistors, Breadboard, Jumpers: Standard electronics lab kit

## Software Requirements
- Keil uVision (for C code compilation & HEX generation)
- Proteus Design Suite (for circuit simulation)
- (Optional): Flash programmer if implementing on actual hardware.

## Project Folder Structure
```
8051-password-motor/
├── src/
│   └── main.c               # C Source Code
├── simulation/
│   └── project.pdsprj       # Proteus simulation file
└── README.md                # Project Overview & Instructions
```

## Steps to Compile HEX File in Keil
1. Open Keil uVision IDE.
2. Create a New Project:
   - Project > New Project
   - Name it: Password_Motor_Control
3. Select Microcontroller:
   - From the device database, select Atmel > AT89C51.
4. Add Source File to Project:
   - Right-click Source Group 1 > Add Existing Files to Group.
   - Browse and select the provided `main.c` from `/src/`.
5. Configure Output HEX File:
   - Go to Project > Options for Target 'Target 1'.
   - Under the Output tab, check "Create HEX File".
6. Build the Project:
   - Press F7 or go to Project > Build Target.
   - The generated HEX file will be located inside the project directory.

## Running the Simulation in Proteus
### Simulation Prerequisites:
- Ensure you have the following Proteus component libraries:
  - 8051 Microcontroller (AT89C51)
  - HD44780 LCD
  - 4x3 Matrix Keypad
  - DC Motor
  - L293D Motor Driver (or equivalent)
  - Push Buttons, Resistors, and Power Sources

### Simulation Steps:
1. Open Proteus Design Suite.
2. Open the Provided Simulation File:
   - Navigate to `/simulation/` folder.
   - Open `project.pdsprj`.
3. Load the HEX File to the Microcontroller:
   - Double-click on the 8051 microcontroller (AT89C51) symbol.
   - In the Program File field, browse and select the generated HEX file.
4. Run the Simulation:
   - Click **Play (Run Simulation)**.

### Operation Flow:
- Press **Button 1 (P1.2)** to initiate password entry.
- Enter Password **"1234"** using the Keypad.
- On successful authentication:
  - **Button 2 (P1.6)** controls the Motor:
    - When pressed: Motor Stops.
    - When released: Motor Runs in the backwards direction.
- Incorrect Password will display **"Try Again"** message.

## How the Code Works
- The microcontroller initializes the LCD.
- When Button 1 (P1.2) is pressed, it prompts the user to enter a 4-digit password via keypad.
- Entered password is masked as ‘****’ on LCD.
- If the password matches “1234”, the user is granted access and can control motor direction.
- Button 2 (P1.6) acts as a toggle switch for motor control.

## Flowchart
```
Start
  |
  |---> Initialize LCD
  |
  |---> Wait for Button 1 Press (P1.2)
         |
         |---> Prompt "Enter Password"
         |
         |---> Accept 4-digit input via Keypad
         |
         |---> Compare with Stored Password "1234"
                      |
         +------------+------------+
         |                         |
   Password Match              Wrong Password
         |                         |
  Display "Access Granted"     Display "Try Again"
         |                         |
         |                         |
   Wait for Button 2 (P1.6)        |
    |              |
 Motor Stop      Motor Backward
    |
  Loop (Monitor Button 2)
```

## Notes
- The **motor_en (P1.3)** pin is reserved for future use (e.g., PWM speed control).
- The keypad scanning uses a basic row-column scanning technique for a 4x3 matrix.
- For physical hardware implementations, software debouncing is recommended for reliable keypad response.

## Troubleshooting
- **HEX File Not Loading in Proteus?**
  - Ensure the HEX file is correctly generated from Keil.
  - Recompile in Keil if necessary.
- **LCD Not Displaying Correctly?**
  - Verify LCD connections (RS, EN, Data Lines) in simulation.
  - Adjust delays in code if the response is slow.
- **Keypad Inputs Not Working?**
  - Confirm row/column connections in Proteus.
  - Ensure no floating inputs (use pull-up resistors if necessary).

## License
This project is licensed under the MIT License. You are free to use, modify, and distribute this code and simulation files.

## Preview (Add Screenshots in /docs/)
- Simulation Circuit Diagram
- LCD showing Password Entry
- LCD showing "Welcome User"
- Motor Movement Control Demo

## Author
GOKUL KRISHNA K S
