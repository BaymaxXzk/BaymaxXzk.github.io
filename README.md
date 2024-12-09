# Group 14 Smart Robot

    * Team Name: Smart Robot
    * Team Members: Zhongkun Xue and Toma Yasuda
    * Github Repository URL: https://github.com/BaymaxXzk/BaymaxXzk.github.io.git
    * Github Pages Website URL: https://baymaxxzk.github.io/
    * Description of hardware: EMG Sensor, 328PB, LCD, Serveo, Battery, Voltage Regulator, 3D printer


# Motivation

## 1. To help people with disabilities or injuries gain the ability to perform everyday tasks that require hand movements. 

![image1](fig1.png)

## 2.To show the human-machine interaction like the Spider-Man

![image1](fig2.png)

# Video demonstration

[Video](https://drive.google.com/file/d/1i9hbKQyfXkABlJKTv1TeEoS8o1czEdYp/view?usp=sharing)


# GIF demonstration

## Gripper part

![image1](gripper.gif)

## Spider shooter

![image1](spider.gif)


# Images demonstration

### firmware_diagram
![image1](fir.png)

### Circuit
![image1](cir.png)

### Project
![image1](4.jpg)


# SRS Validation


|      |Detail                                                                                                                            |Achievement  |
|------|----------------------------------------------------------------------------------------------------------------------------------| ------|
|SRS 1  |The software shall detect EMG signals between 0 and 1024 by ADC, filter noise under, and classify signal strength                |Yes      |
|SRS 2  |Decision-making algorithms shall open or close the claw within 0.5 seconds of detecting an EMG signal based on EMG signal thresholds, which is 200       |Yes      |
|SRS 3  |The system shall include fail-safe controls to prevent accidental or unsafe activation of the claw                                 |No      |
|SRS 4  |The system shall include the battery health calculation by ADC to show the percentage of the current battery                      |Yes      |
|SRS 5  |The software will output the PWM to control the servo degree       |Yes      |
|SRS 6  |The software shall include the ISR to handle the interrupt by the button, ensuring a response time of less than 1 seconds          |Yes      |
|SRS 7  | The software shall provide a user interface to display the real-time data, including EMG signal, battery health, and claw angle updating every 500 millisecond|Yes      |
|SRS 8  |The software shall communicate with the LCD display using SPI protocol to send data       |Yes      |


SRS 1: The software detects EMG signals between 0 and 1024 by ADC, filters noise under, and classifies signal strength. This requirement was tested by displaying the data corrected by the EMG signals on the serial terminal. The values corrected were between 0 and 1024 by ADC.  The data is showed in the video and the final_version.c file.

SRS 02: We measured the time between detecting an EMG signal and claw being opened and closed by displaying the time on the serial monitor. We tested 10 times and the maximum time is less than 0.5 seconds. 

|      |time(s)          |
|------|-----------------|
| 1  | 0.22|
| 2  | 0.35|
| 3  | 0.32|
| 4  | 0.19|
| 5  | 0.44|
| 6  | 0.34|
| 7  | 0.24|
| 8  | 0.47|
| 9  | 0.32|
| 10 | 0.33|

SRS 03: Not achieved because we did not include fail-safe controls to prevent accidental or unsafe activation of the claw. However, there is a button that can be used to stop the control of servo manually.

SRS 04: Achieved and the system includes battery health calculation by ADC to show the percentage of the current battery on the LCD screen. We tested this requirement by showing battery percentage on the screen and compared it with the measured value by the multimeter. The image of the LCD screen is shown in the video and the images part.

SRS 05: Achieved and the software outputs the PWM to control the servo degree. The servo can move the claw based on the input of the EMG signal. The code of final_version.c is showing the work and the video shows that the servo is controlled by the PWM.

SRS 06: We measured the response time to handle the interrupt by the button by printing on the serial. We tested 10 times and data is shown below.

|      |time(s)          |
|------|-----------------|
| 1  | 0.34|
| 2  | 0.54|
| 3  | 0.43|
| 4  | 0.41|
| 5  | 0.44|
| 6  | 0.56|
| 7  | 0.89|
| 8  | 0.54|
| 9  | 0.50|
| 10 | 0.67|


SRS 07: The time to update the LCD screen was measured and displayed on the serial monitor. We can check it from the video.


SRS 08: Achieved and the LCD screen displays the data including EMG signal, battery health, and claw angle. The image of the LCD screen displaying the data from the images part.



# HRS Validation


|      |Detail                                                                                                                            |Achievement  |
|------|----------------------------------------------------------------------------------------------------------------------------------| ------|
|HRS 1  |Project shall be based on ATmega328PB microcontroller operating at 16MHz           |Yes      |
|HRS 2  |EMG sensors (Myoware Muscle Sensor or equivalent) shall be used for muscle activity detection. The sensor shall detect muscle electrical activity in the range of 0-5V    |Yes      |
|HRS 3  |A 1.8" Color TFT LCD (ST7735R controller) shall be used for user interface                             |Yes      |
|HRS 4  |System shall include a servo motor with minimum 180-degree rotation capability for mechanical actuation controlled by PWM                    |Yes      |
|HRS 5  |Power supply shall be provided by a portable battery pack capable of supplying 5V DC or convert to 5V     |Yes      |


HRS 01:

Achieved. ATmega328PB microcontroller operating at 16MHz is used for this project. The proof is in the code which is final_version.c file.

HRS 02:
Myoware Muscle Sensor is used, the connection is good. The circuit image shows the voltage range and the funciton of the sensor in video shows it works well.

HRS 03:
Achieved. A 1.8" Color TFT LCD (ST7735R controller) to display data for users. The proof is in our video.

HRS 04:
Achieved. A servo motor with 180-degree rotation capability for mechanical actuation controlled by PWM is used for our project. Here is the link for the datasheet of the servo.

[datasheet_SG90](http://www.ee.ic.ac.uk/pcheung/teaching/DE1_EE/stores/sg90_datasheet.pdf)

HRS 05:
A 9V battery is used for power supply and converted to 5 volts by using a voltage regulator. We measured the voltage supplied to the ATmega328PB by using a multimeter. We checked the voltage by using a multimeter and it was about 5 volts. Our circuit image can proof it.





# Conclusion

In this project, we were able to design a smart robot system that demonstrated key principles of embedded systems: real-time control, efficient power management, and robust sensor integration. With the use of advanced microcontrollers and carefully chosen components, we were able to find a balance between performance and functionality. The robot performed its designed tasks efficiently, showing our understanding of embedded software design, hardware interfacing, and system optimization.

# What Would You Have Done Differently?
Reflecting on the project, there are several aspects we would approach differently to further enhance the system:

### Hardware Optimization:

We would have chosen more modular and scalable hardware components to allow for easier integration and future upgrades.
Exploring alternative power sources or optimizing power consumption would have extended operational time.

### Improved Testing and Debugging:

Incorporating more systematic testing at every development stage would have reduced debugging time.
Adding diagnostic tools or logging mechanisms would have provided clearer insights into system behavior under different conditions.

### Algorithm Refinement:

Implementing more advanced control algorithms, such as predictive or adaptive controls, could have improved the robot's efficiency and responsiveness.
Exploring machine learning techniques could have added an element of autonomy and adaptability.


# Final_version.c file Code Blocks

```c
/**
* This is C language.
*/
#define F_CPU 16000000UL
#include <avr/io.h>
#include "ST7735.h"
#include "LCD_GFX.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

// Global variables
#define MAX_DISPLAY_LINES 10  // Number of lines visible on screen

int mode_num = 1;
uint16_t background_color;
uint16_t signal_color;
uint16_t battery_percent_color;
uint16_t mode_color;
uint16_t line_color;

// EMG and Servo variables
const int EMG_THRESHOLD = 150;
int current_angle = 90;
int signal_index = 0;

int last_signal[100];
int last_signal_index = 0;

// Servo definitions - Updated for Timer3
#define SERVO_PIN PD0        // Using PD0 for OC3A
#define SERVO_MIN 1000       // Minimum pulse width in microseconds
#define SERVO_MAX 2000       // Maximum pulse width in microseconds
#define TIMER_TOP 20000      // TOP value for 50Hz (20ms period)

// Function declarations
void initServo(void);
uint16_t angle_to_ocr(uint8_t angle);
void adc_init(void);
void updateSignalArray(int newValue);

// Global variables for servo control
volatile uint8_t current_servo_angle = 30;  // 30 (ori is 100)
volatile uint8_t servo_state = 0;           // Track servo state (0 = 60°, 1 = 180°)

// Battery monitoring constants
const int batteryPin = PC2;
const float refVoltage = 5.0;
const float r1 = 10000.0;
const float r2 = 4700.0;

// Signal array
int signal[100];  // Signal array
const int SIGNAL_SIZE = 100;

// Initialize servo
void initServo(void) {
    // Configure PD0 (OC3A) as output
    DDRD |= (1 << SERVO_PIN);

    // Configure Timer3 for Phase and Frequency Correct PWM
    TCCR3A |= (1 << COM3A1);       // Non-inverting mode on OC3A
    TCCR3A &= ~(1 << COM3A0);      // Clear on compare match, set at BOTTOM
    TCCR3B |= (1 << WGM33);        // Phase and Frequency Correct PWM with ICR3 as TOP
    TCCR3B &= ~((1 << WGM32) | (1 << WGM31));
    TCCR3A &= ~(1 << WGM30);

    // Set TOP value for 50Hz PWM frequency
    ICR3 = TIMER_TOP;

    // Set prescaler to 8
    TCCR3B |= (1 << CS31);
    TCCR3B &= ~((1 << CS32) | (1 << CS30));

    // Set initial position to 100 degrees
    OCR3A = angle_to_ocr(30);
}

// Updated angle calculation function
uint16_t angle_to_ocr(uint8_t angle) {
    return SERVO_MIN + (((uint32_t)(SERVO_MAX - SERVO_MIN) * angle) / 180);
}

// Combined ADC initialization for both EMG and battery monitoring
void adc_init(void) {
    // Set PC1 and PC2 as inputs
    DDRC &= ~((1 << DDC1) | (1 << DDC2));
    
    // Reference voltage: AVCC
    ADMUX = (1 << REFS0);
    
    // Initially select ADC1 (PC1) for EMG
    ADMUX |= (1 << MUX0);
    
    // Enable ADC and set prescaler to 128
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

// Updated battery voltage reading function
float readBatteryVoltage() {
    // Save current ADMUX
    uint8_t old_admux = ADMUX;
    
    // Switch to ADC2 (PC2) for battery reading
    ADMUX = (1 << REFS0) | (1 << MUX1);
    _delay_us(100);  
    
    // Start conversion
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));
    uint16_t adcValue = ADC;
    
    // Restore previous ADMUX
    ADMUX = old_admux;
    
    // Debug: Print raw ADC value to LCD
    char debug_str[20];
    sprintf(debug_str, "ADC: %d", adcValue);
    LCD_drawString(2, 40, debug_str, rgb565(255, 255, 255), rgb565(0, 0, 0));
    
    float vOut = (adcValue / 1023.0) * refVoltage;
    return vOut * (r1 + r2) / r2;
}

uint16_t adc_read(void) {
    // Ensure ADMUX is set for EMG reading (ADC1)
    ADMUX = (1 << REFS0) | (1 << MUX0);
    _delay_us(100);
    
    // Start conversion
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));
    
    return ADC;
}

void updateSignalArray(int newValue) {
    for (int i = 0; i < SIGNAL_SIZE - 1; i++) {
        signal[i] = signal[i + 1];
    }
    signal[SIGNAL_SIZE - 1] = newValue;
}

float getBatteryPercent(float voltage) {
    float fullVoltage = 9.0;
    float emptyVoltage = 5.0;
    float percent = ((voltage - emptyVoltage) / (fullVoltage - emptyVoltage)) * 100.0;
    
    // Debug: Print voltage value
    char debug_str[20];
    sprintf(debug_str, "V: %.2f", voltage);
    LCD_drawString(2, 50, debug_str, rgb565(255, 255, 255), rgb565(0, 0, 0));
    
    if (percent > 100.0) percent = 100.0;
    if (percent < 0.0) percent = 0.0;
    return percent;
}

// Initialize system
void Initialize() {
    background_color = rgb565(0, 0, 0);
    signal_color = rgb565(255, 255, 255);
    battery_percent_color = rgb565(255, 255, 255);
    mode_color = rgb565(255, 255, 255);
    line_color = rgb565(255, 255, 255);
    lcd_init();
    initServo();
    LCD_setScreen(background_color);
    initialize_line();
    initialize_battery();
    initialize_mode();
    initialize_angle();
    
    for(int i = 0; i < SIGNAL_SIZE; i++) {
        signal[i] = 0;
    }
}

void initialize_line() {
    LCD_drawBlock(LCD_WIDTH * 2 /3 - 1, 0, LCD_WIDTH * 2 /3 + 1, LCD_HEIGHT, line_color);
    LCD_drawBlock(LCD_WIDTH * 2 /3, LCD_HEIGHT / 3 - 1, LCD_WIDTH, LCD_HEIGHT/3 + 1, line_color);
    LCD_drawBlock(LCD_WIDTH * 2 / 3, LCD_HEIGHT * 2 / 3, LCD_WIDTH, LCD_HEIGHT * 2 / 3 + 1, line_color);
}

void initialize_angle() {
    LCD_drawLine(LCD_WIDTH * 2 /3 + 5, LCD_HEIGHT * 2 / 3 + 25, LCD_WIDTH * 2 /3 + 15, LCD_HEIGHT * 2 / 3 + 25, rgb565(255, 255, 255));
    LCD_drawLine(LCD_WIDTH * 2 /3 + 5, LCD_HEIGHT * 2 / 3 + 25, LCD_WIDTH * 2 /3 + 15, LCD_HEIGHT * 2 / 3 + 17, rgb565(255, 255, 255));
    char angle_str[10];
    sprintf(angle_str, ":%d", current_servo_angle);
    LCD_drawString(LCD_WIDTH * 2 / 3 + 20, LCD_HEIGHT * 2 / 3 + 18, angle_str, rgb565(255, 255, 255), background_color);
}

void initialize_battery() {
    int battery1 = 100;
    char battery1_str[10];
    sprintf(battery1_str, "%d%%", battery1);    
    
    uint16_t battery1_color = rgb565(0, 0, 255);
    if (battery1 < 20) {
        battery1_color = rgb565(255, 0, 0);
    } else if (battery1 < 50) {
        battery1_color = rgb565(255, 255, 0);
    }

    LCD_drawString(LCD_WIDTH * 2 / 3 + 22, LCD_HEIGHT / 3 + 20, battery1_str, rgb565(255, 255, 255), background_color);
    LCD_drawBlock(LCD_WIDTH * 2 /3 + 8, LCD_HEIGHT / 3 + 13, LCD_WIDTH * 2 /3 + 13, LCD_HEIGHT / 3 + 17, battery1_color);
    LCD_drawBlock(LCD_WIDTH * 2 /3 + 5, LCD_HEIGHT / 3 + 17, LCD_WIDTH * 2 /3 + 16, LCD_HEIGHT / 3 + 30, battery1_color);
}

void initialize_mode() {
    LCD_drawString(LCD_WIDTH * 2 / 3 + 7, 10, "Servo", mode_color, background_color);
    LCD_drawString(LCD_WIDTH * 2 / 3 + 7, 20, "Mode ", mode_color, background_color);
    LCD_drawChar(LCD_WIDTH * 2 / 3 + 37, 20, mode_num + '0', mode_color, background_color);
}

void servo1() {
    LCD_drawBlock(LCD_WIDTH * 2 / 3 + 4, 8, LCD_WIDTH - 1, 35, background_color);
    initialize_mode();
    
    int current_signal = signal[SIGNAL_SIZE - 1];
    
    // Debug: Print EMG value
    char debug_str[20];
    sprintf(debug_str, "EMG: %d", current_signal);
    LCD_drawString(2, 20, debug_str, signal_color, background_color);
    
    if (current_signal > 200) {
        if (servo_state == 0) {
            OCR3A = angle_to_ocr(180);
            current_servo_angle = 180;
            servo_state = 1;
            LCD_drawString(2, 30, "State: 180", signal_color, background_color);
        } else {
            OCR3A = angle_to_ocr(30);
            current_servo_angle = 30;
            servo_state = 0;
            LCD_drawString(2, 30, "State: 30", signal_color, background_color);
        }
        
        char angle_str[10];
        sprintf(angle_str, ":%d", current_servo_angle);
        LCD_drawBlock(LCD_WIDTH * 2 / 3 + 20, LCD_HEIGHT * 2 / 3 + 18, LCD_WIDTH - 1, LCD_HEIGHT * 2 / 3 + 25, background_color);
        LCD_drawString(LCD_WIDTH * 2 / 3 + 20, LCD_HEIGHT * 2 / 3 + 18, angle_str, rgb565(255, 255, 255), background_color);
        
        _delay_ms(500);
    }
}

void servo2() {
    // Clear and update mode display
    LCD_drawBlock(LCD_WIDTH * 2 / 3 + 4, 8, LCD_WIDTH - 1, 35, background_color);
    initialize_mode();
    
    // Get the latest EMG signal value
    int current_signal = signal[SIGNAL_SIZE - 1];
    
    // Debug: Print EMG value
    char debug_str[20];
    sprintf(debug_str, "EMG: %d", current_signal);
    LCD_drawString(2, 20, debug_str, signal_color, background_color);
    
    // Check if signal exceeds threshold and update servo position
    if (current_signal > 200) {
        if (servo_state == 0) {
            // Move to 180 degrees
            OCR3A = angle_to_ocr(180);
            current_servo_angle = 180;
            servo_state = 1;
            
            // Debug: Print state change
            LCD_drawString(2, 30, "State: 180", signal_color, background_color);
        } else {
            // Move to 60 degrees
            OCR3A = angle_to_ocr(80);
            current_servo_angle = 80;
            servo_state = 0;
            
            // Debug: Print state change
            LCD_drawString(2, 30, "State: 80", signal_color, background_color);
        }
        
        // Update angle display on LCD
        char angle_str[10];
        sprintf(angle_str, ":%d", current_servo_angle);
        LCD_drawBlock(LCD_WIDTH * 2 / 3 + 20, LCD_HEIGHT * 2 / 3 + 18, LCD_WIDTH - 1, LCD_HEIGHT * 2 / 3 + 25, background_color);
        LCD_drawString(LCD_WIDTH * 2 / 3 + 20, LCD_HEIGHT * 2 / 3 + 18, angle_str, rgb565(255, 255, 255), background_color);
        
        _delay_ms(500);  // Debounce delay
    }
}

void servo3() {
    // Clear and update mode display
    LCD_drawBlock(LCD_WIDTH * 2 / 3 + 4, 8, LCD_WIDTH - 1, 35, background_color);
    initialize_mode();
    
    // Get the latest EMG signal value
    int current_signal = signal[SIGNAL_SIZE - 1];
    
    // Debug: Print EMG value
    char debug_str[20];
    sprintf(debug_str, "EMG: %d", current_signal);
    LCD_drawString(2, 20, debug_str, signal_color, background_color);
    
    // Check if signal exceeds threshold and update servo position
    if (current_signal > 200) {
        if (servo_state == 0) {
            // Move to 180 degrees
            OCR3A = angle_to_ocr(180);
            current_servo_angle = 180;
            servo_state = 1;
            
            // Debug: Print state change
            LCD_drawString(2, 30, "State: 180", signal_color, background_color);
        } else {
            // Move to 60 degrees
            OCR3A = angle_to_ocr(90);
            current_servo_angle = 90;
            servo_state = 0;
            
            // Debug: Print state change
            LCD_drawString(2, 30, "State: 90", signal_color, background_color);
        }
        
        // Update angle display on LCD
        char angle_str[10];
        sprintf(angle_str, ":%d", current_servo_angle);
        LCD_drawBlock(LCD_WIDTH * 2 / 3 + 20, LCD_HEIGHT * 2 / 3 + 18, LCD_WIDTH - 1, LCD_HEIGHT * 2 / 3 + 25, background_color);
        LCD_drawString(LCD_WIDTH * 2 / 3 + 20, LCD_HEIGHT * 2 / 3 + 18, angle_str, rgb565(255, 255, 255), background_color);
        
        _delay_ms(500);  // Debounce delay
    }
}

void spider_shooter() {
    // Clear and update mode display
    LCD_drawBlock(LCD_WIDTH * 2 / 3 + 7, 10, LCD_WIDTH * 2 / 3 + 48, 27, background_color);
    LCD_drawBlock(LCD_WIDTH * 2 / 3 + 7, 20, LCD_WIDTH * 2 / 3 + 48, 27, background_color);
    LCD_drawString(LCD_WIDTH * 2 / 3 + 4, 8, "Spider", mode_color, background_color);
    LCD_drawString(LCD_WIDTH * 2 / 3 + 4, 18, "Shooter", mode_color, background_color);
    LCD_drawString(LCD_WIDTH * 2 / 3 + 4, 28, "Mode", mode_color, background_color);
    
    // Get the latest EMG signal value
    int current_signal = signal[SIGNAL_SIZE - 1];
    
    // Debug: Print EMG value
    char debug_str[20];
    sprintf(debug_str, "EMG: %d", current_signal);
    LCD_drawString(2, 20, debug_str, signal_color, background_color);
    
    // Check if signal exceeds threshold and update servo position
    if (current_signal > 200) {
        if (servo_state == 0) {
            // Move to 180 degrees
            OCR3A = angle_to_ocr(180);
            current_servo_angle = 180;
            servo_state = 1;
            
            // Debug: Print state change
            LCD_drawString(2, 30, "State: 180", signal_color, background_color);
        } else {
            // Move to 100 degrees
            OCR3A = angle_to_ocr(0);
            current_servo_angle = 0;
            servo_state = 0;
            
            // Debug: Print state change
            LCD_drawString(2, 30, "State: 0", signal_color, background_color);
        }
        
        // Update angle display on LCD
        char angle_str[10];
        sprintf(angle_str, ":%d", current_servo_angle);
        LCD_drawBlock(LCD_WIDTH * 2 / 3 + 20, LCD_HEIGHT * 2 / 3 + 18, LCD_WIDTH - 1, LCD_HEIGHT * 2 / 3 + 25, background_color);
        LCD_drawString(LCD_WIDTH * 2 / 3 + 20, LCD_HEIGHT * 2 / 3 + 18, angle_str, rgb565(255, 255, 255), background_color);
        
        _delay_ms(500);  // Debounce delay
    }
}

void setup() {
    // Button setup on PD1
    DDRD &= ~(1 << PD1);    // Set PD1 as input
    PORTD |= (1 << PD1);    // Enable pull-up resistor on PD1
    
    // LED on PC5 (if you're still using it)
    DDRC |= (1 << PC5);     // Set PC5 as output
    PORTC &= ~(1 << PC5);   // Set PC5 low initially
    
    // Pin change interrupt setup for PD1
    PCICR |= (1 << PCIE2);  // Enable pin change interrupts for PORTD (PCIE2 for PCINT16..23)
    PCMSK2 |= (1 << PCINT17); // Enable pin change interrupt on PD1 (PCINT17)
    
    // Global interrupt enable
    sei();
}

volatile uint8_t button_pressed = 0;

ISR(PCINT2_vect) {
    static uint8_t debounce_count = 0;
    
    // Check if button is pressed (PD1 is low)
    if (!(PIND & (1 << PD1))) {
        if (!button_pressed) {  // If button wasn't previously pressed
            button_pressed = 1;
            update_mode();      // Update the mode
        }
    } else {
        button_pressed = 0;  // Button is released
    }
    
    _delay_ms(50);  // Debounce delay
}

void update_mode() {
    mode_num = (mode_num % 4) + 1;
    
    // Set servo to 180 degrees whenever button is pressed
    OCR3A = angle_to_ocr(180);
    current_servo_angle = 180;
    servo_state = 1;
    
    // Display new angle immediately
    char angle_str[10];
    sprintf(angle_str, ":%d", current_servo_angle);
    LCD_drawBlock(LCD_WIDTH * 2 / 3 + 20, LCD_HEIGHT * 2 / 3 + 18, LCD_WIDTH - 1, LCD_HEIGHT * 2 / 3 + 25, background_color);
    LCD_drawString(LCD_WIDTH * 2 / 3 + 20, LCD_HEIGHT * 2 / 3 + 18, angle_str, rgb565(255, 255, 255), background_color);
    
    // Update mode display
    if(mode_num == 1) {
        servo1();
    }
    else if(mode_num == 2) {
        servo2();
    }
    else if(mode_num == 3) {
        servo3();
    }
    else if(mode_num == 4) {
        spider_shooter();
    }
}

void update_battery(int battery_percent) {
    char battery__percent_str[20];  // Increased buffer size
    sprintf(battery__percent_str, "%d%% ADC:%d", battery_percent, ADC);  // Added ADC value for debug
    
    LCD_drawBlock(LCD_WIDTH * 2 / 3 + 22, LCD_HEIGHT / 3 + 20, LCD_WIDTH * 2 / 3 + 48, LCD_HEIGHT / 3 + 20 + 7, background_color);
    LCD_drawString(LCD_WIDTH * 2 / 3 + 22, LCD_HEIGHT / 3 + 20, battery__percent_str, battery_percent_color, background_color);
    
    uint16_t battery_color = rgb565(0, 0, 255);
    if (battery_percent < 20) {
        battery_color = rgb565(255, 0, 0);
    } else if (battery_percent < 50) {
        battery_color = rgb565(255, 255, 0);
    }
    LCD_drawBlock(LCD_WIDTH * 2 /3 + 8, LCD_HEIGHT / 3 + 13, LCD_WIDTH * 2 /3 + 13, LCD_HEIGHT / 3 + 17, battery_color);
    LCD_drawBlock(LCD_WIDTH * 2 /3 + 5, LCD_HEIGHT / 3 + 17, LCD_WIDTH * 2 /3 + 16, LCD_HEIGHT / 3 + 30, battery_color);
}

void printEMG(int signal[], int arrayLength) {
    char EMG_str[10];
    
    // Clear the previous value
    LCD_drawBlock(2, 2, LCD_WIDTH * 2/3 - 2, 11, background_color);
    
    // Print new value
    sprintf(EMG_str, "%d", signal[arrayLength - 1]);  // Only show the most recent value
    LCD_drawString(2, 2, "EMG Value: ", signal_color, background_color);
    LCD_drawString(75, 2, EMG_str, signal_color, background_color);
}

int main(void) {
   // Single ADC initialization for both EMG and battery
   adc_init();
   lcd_init();
   Initialize();
   setup();
   
   float batteryVoltage;
   float batteryPercent;
   char EMG_signal_str[10];
   uint16_t raw_adc_value;
   
   while (1) {
       // Read EMG signal
       int emg_value = adc_read();
       updateSignalArray(emg_value);
       
       // Handle servo control based on current mode
       if (mode_num == 1) {
           servo1();
       } else if (mode_num == 2) {
           servo2();
       } else if (mode_num == 3) {
           servo3();
       } else if (mode_num == 4) {
           spider_shooter();
       }
       
       sprintf(EMG_signal_str, "%d", emg_value);        
       printEMG(signal, SIGNAL_SIZE);
       
       // Read and update battery display
       batteryVoltage = readBatteryVoltage();
       batteryPercent = getBatteryPercent(batteryVoltage);
       update_battery((int)batteryPercent);
       
       // Update last signal array
       for (last_signal_index = 0; last_signal_index < SIGNAL_SIZE; last_signal_index++) {
           last_signal[last_signal_index] = signal[last_signal_index];
       }
       
       // Debug battery values
       char debug_str[20];
       sprintf(debug_str, "V: %.2f", batteryVoltage);
       LCD_drawString(2, 50, debug_str, rgb565(255, 255, 255), rgb565(0, 0, 0));
       
       raw_adc_value = ADC;  // Get current ADC value
       sprintf(debug_str, "ADC: %d", raw_adc_value);
       LCD_drawString(2, 60, debug_str, rgb565(255, 255, 255), rgb565(0, 0, 0));
       
       _delay_ms(50);  // 50ms delay for stability
   }
   
   return 0;
}
```