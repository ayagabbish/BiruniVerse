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

| **Section**                      | **Description** |
|----------------------------------|-----------------|
| **🔷 Project Overview**          |                 |
| [Introduction](#introduction)    | Technical overview of the code structure, modules, and uploading process. |
| [Video Demonstration](#video-demonstration) | Link to the official driving demo video of the robot. |

| **👥 Team**                      |                 |
| [Team Photos](#team-photos)      | Includes official and funny photos of the full team. |

| **🤖 The Robot**                |                 |
| [Vehicle Photos](#vehicle-photos) | Shows 6 detailed images of the robot from all sides, including top and bottom. |
| [Schematics](#schematics)        | Diagrams illustrating electronic and mechanical connections of the robot. |
| [3D/CNC Models](#3dcnc-models)   | Files for 3D printing, laser cutting, or CNC machine use. |

| **💻 Code & Software**          |                 |
| [Source Code](#source-code)      | Contains code for all programmed components used in the vehicle. |

| **📄 Documentation**            |                 |
| [Other Documentation](#other-documentation) | Includes datasets, connection guides, protocols, and specifications. |

## Introduction

_This section should explain what your codebase includes: the main modules (like motor control, line following, lap counter, etc.), how each is linked to physical components (like servo, motor, sensors), and instructions on compiling/uploading the code (e.g., using Arduino IDE or PlatformIO)._

## Team Photos

_A folder with two photos: one official and one funny showing the whole team._

## Vehicle Photos

_Six images showing the vehicle from all angles: front, back, left, right, top, and bottom._

## Video Demonstration

_Link to a demo video showing your robot navigating as per the task requirements._

## Schematics

_Images (PNG/JPEG/PDF) of your electromechanical diagrams showing how every component is wired or connected._

## Source Code

_All Arduino/Python/C++ code and libraries for sensors, motors, servos, etc._

## 3D/CNC Models

_STL, DXF, or other model files used for manufacturing vehicle parts. If not used, this section can be deleted._

## Other Documentation

_Includes manuals, connection instructions, SBC/ESP32 guides, datasets, protocols, or additional helpful content._
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
