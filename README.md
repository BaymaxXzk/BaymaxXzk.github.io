# Group 14 Smart Robot

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


SRS 1 was achieved? The software detects EMG signals between 0 and 1024 by ADC, filters noise under, and classifies signal strength. This requirement was tested by displaying the data corrected by the EMG signals on the serial terminal. The values corrected were between 0 and 1024 by ADC.???  The data corrected is shown below as the proof of the work.

SRS 02, will measure time to test
We measured the time between detecting an EMG signal and claw being opened and closed by displaying the time on the serial monitor. We tested 50 times and the average time is , max is , and min is 
All the data collected is shown below.

SRS 03 was not achieved because we did not include fail-safe controls to prevent accidental or unsafe activation of the claw. However, there is a button that can be used to stop the control of servo manually.
SRS 04 was achieved and the system includes battery health calculation by ADC to show the percentage of the current battery on the LCD screen. We tested this requirement by showing battery percentage on the screen and compared it with the measured value by the multimeter. The image of the LCD screen is shown below as the proof of the work.

SRS 05 was achieved and the software outputs the PWM to control the servo degree. The servo can move the claw based on the input of the EMG signal. The screenshot of the code controlling the servo is shown below as the proof of the work and the video shows that the servo is controlled by the PWM can be found in our demo video.
SRS 06 will measure time
We measured the response time to handle the interrupt by the button by printing on the serial. We tested 50 times and data is shown below. 

SRS 07 will measure time
The time to update the LCD screen was measured and displayed on the serial monitor. Data is corrected 50 times and shown below.

SRS 08 was achieved and the LCD screen displays the data including EMG signal, battery health, and claw angle. The image of the LCD screen displaying the data is shown below.


|      |Points   |Grade  |
|------|---------| ------|
|STU1  |50       |F      |
|STU2  |70       |C      |
|STU3  |90       |A      |



# HRS Validation

HRS 01
Achieved. ATmega328PB microcontroller operating at 16MHz is used for this project. The image is shown below as proof.
HRS 02
Myoware Muscle Sensor is used, will have to measure voltage

HRS 03
Achieved. A 1.8" Color TFT LCD (ST7735R controller) to display data for users. The image is shown below.

HRS 04
Achieved. A servo motor with 270-degree rotation capability for mechanical actuation controlled by PWM is used for our project. Here is the link for the datasheet of the servo.

HRS 05
A 9V battery is used for power supply and converted to 5 volts by using a voltage regulator. We measured the voltage supplied to the ATmega328PB by using a multimeter. Will have to check voltage


|      |Points   |Grade  |
|------|---------| ------|
|STU1  |50       |F      |
|STU2  |70       |C      |
|STU3  |90       |A      |


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
