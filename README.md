# Black3DPrintedRobot

This repository serves as an archive of the project, preserving its source code, documentation, and development history. The project consists of an autonomous robot capable of following a path on the ground using infrared sensors and an Arduino board, providing a foundation for educational purposes, prototyping, and robotics studies.


## Overview

The system continuously reads data from infrared sensors mounted underneath the robot. These sensors detect the contrast between the line (typically black) and the surface (typically white).

Based on these readings, the Arduino processes the information and dynamically adjusts the speed and direction of the motors, keeping the robot aligned with the track.

## 🧠 How It Works

* IR sensors detect the position of the line.
* The Arduino interprets the sensor readings.
* A control algorithm determines the required steering correction.
* The motor driver adjusts the DC motors accordingly.
* The robot continuously follows the designated path.

## 🛠 Hardware Components

* Arduino (Uno, Nano, or compatible board)
* Infrared (IR) sensors
* DC motors with wheels
* Motor driver (L298N or equivalent)
* Robotic chassis
* Battery pack
* Wires and jumper cables

## ⚙️ Applications

* Robotics competitions
* Embedded systems education
* Control systems studies (PID)
* Academic projects
* Autonomous system prototyping

## 🚀 Project Goals

* Develop an efficient control algorithm
* Improve tracking stability and accuracy
* Optimize speed while maintaining reliability
* Explore proportional and PID control techniques
* Build a scalable platform for future robotics projects
