#include <reg51.h>   // Include 8051 SFR definition header
#include <string.h>  // Include for strcmp() function

/************** LCD Control Pins **************/
sbit rs = P1^1;  // Register Select (RS) pin connected to P1.1
sbit en = P1^0;  // Enable (EN) pin connected to P1.0

/************** Push Buttons **************/
sbit btn = P1^2;   // Password Activation Button (P1.2)
sbit btn2 = P1^6;  // Motor Control Button (P1.6)

/************** DC Motor Control Pins **************/
sbit motor_in1 = P1^5;  // Motor Direction Control IN1 (P1.5)
sbit motor_in2 = P1^4;  // Motor Direction Control IN2 (P1.4)
sbit motor_en = P1^3;   // Motor Enable Pin (Not used actively in code)

/************** Keypad Rows (P3.0 - P3.3) **************/
sbit r1 = P3^0;
sbit r2 = P3^1;
sbit r3 = P3^2;
sbit r4 = P3^3;

/************** Keypad Columns (P3.4 - P3.7) **************/
sbit c1 = P3^4;
sbit c2 = P3^5;
sbit c3 = P3^6;
sbit c4 = P3^7;   // c4 is unused in scanning logic (4x3 Keypad)

/************** Global Variables **************/
unsigned char password[5] = "1234";  // Predefined password (must end with '\0')
unsigned char entered[5];            // Array to store entered password

/************** Function Prototypes **************/
void cmd(int);                  // Send Command to LCD
void data1(char);                // Send Data to LCD
void lcd_init();                 // Initialize LCD
void delay();                    // Generic Delay Function
void display(char*);             // Display String on LCD
int key();                       // Keypad Scanning Function
bit password_system();           // Complete Password Flow
void enter_password();           // Accept Password Input from Keypad
bit check_password();            // Validate Entered Password
void motor_forward();            // Motor Forward
void motor_backward();           // Motor Backward
void motor_stop();               // Motor Stop

/************** Main Function **************/
void main() {
    // Wait for Button Press to Initiate Password System
    if (btn == 0) {  // Active Low Button (Pressed when 0)
        bit result;

        result = password_system();  // Execute Password Authentication Flow

        if (result) {  // If password correct
            cmd(0x01);  // Clear LCD
            display("Welcome User");  // Display Welcome Message
            
            // Motor Control Based on btn2 Status
            if (btn2 == 0) {
                motor_stop();  // Stop Motor if btn2 is pressed
            } else if (btn2 == 1) {
                motor_backward();  // Motor Runs in Backward Direction
            }
        } else {  // Password Incorrect
            cmd(0x01);  // Clear LCD
            display("Try Again");  // Display Retry Message
        }

        while(1);  // Infinite Loop to Halt System after Operation
    }
}

/************** Password Authentication Flow **************/
bit password_system() {
    lcd_init();         // Initialize LCD Display
    enter_password();   // Capture 4-digit Password Input
    return check_password();  // Validate Password & Return Result
}

/************** Capture Password Input from Keypad **************/
void enter_password() {
    int i = 0;
    char key_val;

    cmd(0x01);  // Clear LCD Screen
    display("Enter Password:");  // Prompt Message
    cmd(0xC0);  // Move Cursor to Second Line

    // Accept 4 digits from Keypad
    while (i < 4) {
        key_val = key();  // Scan Keypad
        if (key_val != -1) {  // If a valid key is pressed
            entered[i++] = key_val + '0';  // Convert numeric value to ASCII & store
            data1('*');  // Display '*' for privacy
            delay();     // Debounce Delay to avoid repeated reads
        }
    }
    entered[4] = '\0';  // Null-Terminate Entered Password String
}

/************** Compare Entered Password with Stored Password **************/
bit check_password() {
    cmd(0x01);  // Clear LCD
    if (strcmp(entered, password) == 0) {  // If passwords match
        display("Access Granted");
        delay();
        return 1;  // Return Success
    } else {
        display("Wrong Password");
        delay();
        return 0;  // Return Failure
    }
}

/************** LCD Initialization Sequence **************/
void lcd_init() {
    cmd(0x38);  // Function Set: 2 Lines, 5x7 Matrix
    cmd(0x0E);  // Display ON, Cursor ON
    cmd(0x01);  // Clear Display
    cmd(0x06);  // Auto Increment Cursor
    cmd(0x80);  // Set Cursor to Beginning
}

/************** Send Command to LCD **************/
void cmd(int a) {
    P2 = a;  // Send Command Byte to Port 2
    rs = 0;  // RS = 0 for Command Register
    en = 1;  // EN High
    delay(); // Small Delay
    en = 0;  // EN Low (Latch Command)
}

/************** Send Data to LCD **************/
void data1(char x) {
    P2 = x;  // Send Data Byte to Port 2
    rs = 1;  // RS = 1 for Data Register
    en = 1;  // EN High
    delay(); // Small Delay
    en = 0;  // EN Low (Latch Data)
}

/************** Display String on LCD **************/
void display(char *s) {
    while (*s) {
        data1(*s++);  // Send Each Character to LCD
    }
}

/************** 4x3 Keypad Scanning Routine **************/
int key() {
    // Row 1 Active
    r1 = 0; r2 = r3 = r4 = 1;
    if (c1 == 0) { delay(); while(c1==0); return 7; }
    if (c2 == 0) { delay(); while(c2==0); return 8; }
    if (c3 == 0) { delay(); while(c3==0); return 9; }

    // Row 2 Active
    r2 = 0; r1 = r3 = r4 = 1;
    if (c1 == 0) { delay(); while(c1==0); return 4; }
    if (c2 == 0) { delay(); while(c2==0); return 5; }
    if (c3 == 0) { delay(); while(c3==0); return 6; }

    // Row 3 Active
    r3 = 0; r1 = r2 = r4 = 1;
    if (c1 == 0) { delay(); while(c1==0); return 1; }
    if (c2 == 0) { delay(); while(c2==0); return 2; }
    if (c3 == 0) { delay(); while(c3==0); return 3; }

    // Row 4 Active
    r4 = 0; r1 = r2 = r3 = 1;
    if (c2 == 0) { delay(); while(c2==0); return 0; }

    return -1;  // No key pressed
}

/************** Motor Forward Direction **************/
void motor_forward() {
    motor_in1 = 1;  // IN1 High
    motor_in2 = 0;  // IN2 Low
}

/************** Motor Backward Direction **************/
void motor_backward() {
    motor_in1 = 0;  // IN1 Low
    motor_in2 = 1;  // IN2 High
}

/************** Stop Motor **************/
void motor_stop() {
    motor_in1 = 0;  // IN1 Low
    motor_in2 = 0;  // IN2 Low
}

/************** Generic Software Delay **************/
void delay() {
    int i, j;
    for(i = 0; i < 50; i++)
        for(j = 0; j < 200; j++);
}
