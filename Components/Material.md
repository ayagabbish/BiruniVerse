# Material
The Material we used to build our robot car
## Raspberry Pi 4
<p align="center">
  <img src="./RAS.gif" alt="Raspberry Pi 4" width="50%">
</p>

- **Processor**: 1.5GHz 64-bit quad-core  
- **RAM**: 8GB LPDDR4  
- **SD card**: 32GB 
- **Ports**: 2 USB 3.0 ports, 2 USB 2.0 ports
- **Operation Voltage** : 5.1V at 3A
- **Dimensions** : 85mm x 56mm x 17mm
- **Connectivity**:  
  - Dual-band Wi-Fi  
  - Bluetooth 5.0  
  - Gigabit Ethernet  
  - USB 3.0

***Purpose*** : The purpose of using the Raspberry Pi 4 was to connect a camera that provides visual input to the system. This input is then processed using machine learning, including image classification and recognition. Moreover, these methods guide the robot car to determine the turning direction based on live information and observations. In addition, the system can make decisions on the spot in a changing environment.

***Selection reason*** : As for the reason for choosing the Raspberry Pi 4, it is due to its easier-to-provide power source and lower power consumption. It is also more compatible when coding and using libraries. and lastly, its accessories are more affordable, and it generates less heat compared to the Raspberry Pi 5.


## ESP32
<p align="center">
  <img src="./ESP32model3d.gif" alt="Raspberry Pi 4" width="50%">
</p>

- 
- **Model**: ESP32-WROOM-32 
- **Board**: NodeMCU-ESP32 (ESP32 DEVKITV1)  
- **Chip**: ESP32 (Dual-core Xtensa LX6, up to 240MHz)  
- **Wi-Fi**: 802.11 b/g/n (2.4GHz)  
- **Bluetooth**: v4.2 BR/EDR + BLE  
- **RAM**: 520KB SRAM  
- **Flash**: 4MB (or 16MB, depending on variant)  
- **GPIO Pins**: 38 (including ADC, DAC, UART, SPI, I2C)  
- **USB**: Micro-USB (for power/programming)  
- **Operating Voltage**: 3.3V
- **Dimensions** : 18mm x 25.5mm x 3.1mm

***Purpose*** : its to connect the rest of the robots components, sensors and motors, to ensure their best performance, we programmed the microcontroller using C++, It connects to the Raspberry Pi, which handles image recognition. Based on camera input (red or green obstacle), the Raspberry Pi sends commands to the ESP32, which then executes movement based on the code the esp32 runs, through the connected hardware.

***Selection reason*** : The ESP32 has many captivating and suitable features for our project, it has processing power of Dual-core 32-bit Xtensa CPU, up to 240 MHz, it has both Wi-Fi and Bluetooth (Classic + BLE) built-in, enough memory (520KB) to handle our code and execute it smoothly, has PWM On most GPIOs, its more cost effective, and it has more advanced features.

## Ultrasonic Sensor
<p align="center">
<picture>
  <img alt="Ultrasonic Sensor" src="ultrasonic.webp" width="50%" hight="40%" >
</picture>
</p>

**Model**: HC-SR04
**Voltage:** 5V DC  
**Current:** 15mA  
**Frequency:** 40Hz  
**Max Range:** 4m  
**Min Range:** 2cm  
**Measuring Angle:** 15°  
**Trigger Input:** 10µs TTL pulse  
**Echo Output:** TTL level signal (range proportional)  
**Dimensions:** 45 × 20 × 15 mm  

***Purpose*** : We have adopted a strategy that requires three ultrasonic sensors to be used effectively. Two sensors are placed on the sides, while the third is positioned at the front of the car. The side sensors are responsible for measuring the distance between the car and the walls on each side of the path. They continuously compare the two readings to determine the car’s position. When one of the side sensors detects a distance greater than the other by more than 2 meters, the system will determine that side as the turning direction of the path. As for the third sensor at the front, its main purpose is to measure the distance between the car and any obstacles, which will later be used to decide when the car should start turning at an angle to avoid collisions. It will also measure the distance between the walls of the track and the car, which will be useful—combined with our servomotor and camera in Task 2.

## Infrared Sensor
<p align="center">
  <img src="./.gif" alt="Infrared Sensor" width="50%">
</p>

- **Model**: TCRT5000  
- **Operating Voltage**: 3.3V – 5V  
- **Current Consumption**: ~18–20 mA  
- **Detection Range**: 2 mm – 15 mm (optimal within 2–10 mm)  
- **Output Signal**: Digital (HIGH/LOW) or Analog (depending on board version)  
- **Detection Type**: Reflective infrared (IR LED + phototransistor)  
- **Wavelength**: ~950 nm (IR emitter)  
- **Response Time**: <1 ms (fast switching)  
- **Adjustable Sensitivity**: Yes (via onboard potentiometer, if available)  
- **Indicator LEDs**: Power and output status  
- **Dimensions (module)**: ~3.2 cm × 1.4 cm (can vary by version)  

***Purpose*** : The purpose of this sensor is to detect short distances between the robot and its surroundings. While it may seem similar to the ultrasonic sensor, its main role is to provide an extra layer of safety to prevent collisions with obstacles or walls. It also helps the robot determine when to move backwards if needed.  

***Selection reason*** : It senses short distances more precisely than the ultrasonic sensor.  

## Color Sensor
<p align="center">
  <img src="./.gif" alt="Color Sensor" width="50%">
</p>

- **Model**: TCS3200 Color Sensor  
- **Operating Voltage**: 2.7V – 5.5V (typically 5V)  
- **Operating Current**: ~2.5 mA (average)  
- **Output Type**: Frequency (square wave) proportional to light intensity  
- **Sensing Element**: 8×8 array (64 photodiodes):  
  - 16 red filters  
  - 16 green filters  
  - 16 blue filters  
  - 16 clear (no filter)  
- **Selectable Output Frequency Scaling**: 100%, 20%, and 2%  
- **Measurement Range**: Full visible spectrum (RGB + clear)  
- **Response Time**: <100 ms typical  
- **Interface**: Digital output (no ADC needed)  
- **Detection Method**: Measures reflected light intensity of different colors  
- **Module Dimensions**: ~28 mm × 28 mm (may vary by version)  

***Purpose*** : Its main job is to detect either a green or orange line on the mat, which is used to count how many laps the robot car has completed. If it detects 12 orange lines, it means the car has finished 3 laps and should park (the mat has 4 orange lines at each corner, so 4 lines equal one lap). The color sensor also had another role in a different strategy: to determine the direction of the car (clockwise or counterclockwise). This was based on the color of the first line detected, which guided the system to track that color and decide turning direction.  

***Selection reason*** : Provides reliable detection of specific colors, enabling lap counting and alternative navigation strategies.  

---

## H-Bridge
<p align="center">
  <img src="./.gif" alt="H-Bridge" width="50%">
</p>

- **Voltage**: 5V to 35V  
- **Logic Voltage**: 5V  
- **Continuous Current**: 2A per channel  
- **Peak Current**: 3A per chann
- **Channels**: 2 (dual H-Bridge)  
- **Speed Control**: PWM (ENA/ENB pins)  
- **Direction Control**: IN1, IN2, IN3, IN4  
- **Protection**: Thermal shutdown, current limiting  
- **Flyback Diodes**: Included  

***Purpose*** : The ESP32 cannot directly reverse motor direction, but an H-Bridge enables this through simple digital HIGH/LOW signals. It also supports braking and freewheeling modes, offering finer control. It acts as a power driver, handling higher motor currents safely.  

***Selection reason*** : Without an H-Bridge, a DC motor can only spin one way. The H-Bridge makes motor control safe, programmable, and reliable.  

---

## DC Motor
<p align="center">
  <img src="./.gif" alt="DC Motor" width="50%">
</p>

- **Voltage**: 3V to 6V  
- **Rated Voltage**: 6V  
- **No-load Speed**: ~30 to 1000 RPM (depends on gear ratio)  
- **No-load Current**: ~40 mA to 150 mA  
- **Stall Current**: ~300 mA to 600 mA  
- **Stall Torque**: ~0.1 to 1.2 kg·cm (varies by gear ratio)  
- **Motor Type**: Brushed DC with metal gearbox  
- **Shaft Diameter**: 3 mm (D-shaped)  
- **Gearbox Size**: 12 mm × 10 mm × 26 mm (approx.)  
- **Rotation Direction**: Reversible by switching polarity  

***Purpose*** : Provides forward and backward movement for the robot based on sensor inputs.  

***Selection reason*** : Small, lightweight, affordable, and works well with the L298N H-Bridge. Its gearbox increases torque, supports reversible motion, and operates efficiently at 3V–6V.  

---

## Servo Motor
<p align="center">
  <img src="./.gif" alt="Servo Motor" width="50%">
</p>

- **Voltage**: 4.8V to 6V  
- **Operating Current**: ~100 mA to 250 mA (under load)  
- **Stall Torque**: 1.8 kg·cm at 4.8V  
- **Speed**: ~0.1 sec/60° at 4.8V  
- **Rotation Range**: 0° to ~180° (limited by internal stops)  
- **Control Signal**: PWM (50 Hz, 1–2 ms pulse width)  
- **Motor Type**: Brushed DC motor with control circuitry and feedback  
- **Weight**: ~9 g  
- **Dimensions**: 22.8 × 12.2 × 29.5 mm  
- **Gear Type**: Plastic gears  
- **Shaft Type**: Spline (21 teeth)  
- **Connector**: 3-pin (Signal, VCC, GND)  

***Purpose*** : Used in the robot car’s steering mechanism. In Task 2, it worked with the camera and Teachable Machine to avoid obstacles dynamically by adjusting angles gradually. In Task 1, it turned 90° at track edges with ultrasonic input to keep the car aligned.  

***Selection reason*** : Compact, affordable, easy to control, and accurate for 0°–180° rotation, making it ideal for steering.  

---

## ESP32 Expansion Board
<p align="center">
  <img src="./.gif" alt="ESP32 Expansion Board" width="50%">
</p>

- **Microcontroller**: ESP32 (dual-core, 240 MHz)  
- **Connectivity**: Wi-Fi + Bluetooth  
- **Operating Voltage**: 3.3V  
- **Programming**: Arduino IDE or MicroPython  
- **USB**: For power and programming (usually Micro-USB)  

***Purpose*** : Acts as the main controller for connecting sensors, processing inputs, and controlling outputs such as LEDs and motors.  

***Selection reason*** : Supports wireless communication, IoT applications, and runs code directly (Arduino/MicroPython). Flexible, powerful, and easy to integrate.  

---

## Camera
<p align="center">
  <img src="./.gif" alt="Camera" width="50%">
</p>

***Specification*** : (to be filled)  

***Purpose*** : Provides real-time visual input for machine learning–based navigation and obstacle detection.  

***Selection reason*** : Essential for implementing image recognition and guiding the robot’s decision-making system.  

---

## Teachable Machine
<p align="center">
  <img src="./.gif" alt="Teachable Machine" width="50%">
</p>

***Purpose*** : Allowed the team to quickly train an image classification model without complex coding. The model was exported as TensorFlow Lite and deployed to the device for real-time object recognition, integrating machine learning into the robot’s decision-making system.  

***Selection reason*** : Simplified ML integration, reduced development time, and provided accessible tools for fast prototyping.  

