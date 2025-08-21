<h1 align="center">BiruniVerse Team</h1>
<p align="center">
  <img src="logo.PNG" alt="BiruniVerse Logo" width="300"/>

>  This repository documents the technical design, engineering processes, and development stages of our autonomous vehicle prototype. Built by three passionate engineering students, this robot is our gateway to the universe. United by creativity and curiosity, and supported by Birzeit University, we proudly present our journey in the WRO Future Engineers Challenge 2025.
## Content

* `t-photos` contains 2 photos of the team (an official one and one funny photo with all team members)
* `v-photos` contains 6 photos of the vehicle (from every side, from top and bottom)
* `video` contains the video.md file with the link to a video where driving demonstration exists
* `schemes` contains one or several schematic diagrams in form of JPEG, PNG or PDF of the electromechanical components illustrating all the elements (electronic components and motors) used in the vehicle and how they connect to each other.
* `src` contains code of control software for all components which were programmed to participate in the competition
* `models` is for the files for models used by 3D printers, laser cutting machines and CNC machines to produce the vehicle elements. If there is nothing to add to this location, the directory can be removed.
* `other` is for other files which can be used to understand how to prepare the vehicle for the competition. It may include documentation how to connect to a SBC/SBM and upload files there, datasets, hardware specifications, communication protocols descriptions etc. If there is nothing to add to this location, the directory can be removed.

## Table of Contents

1. [Project Overview](#1-project-overview)  
   1.1 [Competition Context](#11-competition-context)  
   1.2 [Team Management](#12-team-management)  
   1.3 [Vehicle Strengths & Limitations](#13-vehicle-strengths--limitations)  

2. [Programming & Navigation](#2-programming--navigation)  
   2.1 [Programming Language & Libraries](#21-programming-language--libraries)  
   2.2 [Turn & Direction Detection](#22-turn--direction-detection)  
   2.3 [Lap Counting Method](#23-lap-counting-method)  
   2.4 [IMU-Based Steering](#24-imu-based-steering)  

3. [Open Challenge](#3-open-challenge)  
   3.1 [Challenge Overview](#31-challenge-overview)  
   3.2 [PID Controller](#32-pid-controller)  
   3.3 [Turn Execution](#33-turn-execution)  

4. [Obstacle Avoidance](#4-obstacle-avoidance)  
   4.1 [Overview](#41-overview)  
   4.2 [Pillar Detection](#42-pillar-detection)  
   4.3 [Avoidance Strategy](#43-avoidance-strategy)  

5. [Design Process](#5-design-process)
# Engineering Material
- Raspberri pi 4
- ESP-WROOM-32
- ESP32 expansion board
- H-bridge
- DC Mototr
- Servo Motor
- Infrared Sensor
- Color Sensor
- ultrasonics : we used 3 ultrasonics 2 on the sides and 1 in the front
