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