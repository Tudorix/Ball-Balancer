# Ball-Balancer
![Ball-Balancer](Media/Final%20(1).jpeg)

A ball balancing platform that uses three SG90 servos to tilt a plate and keep a yellow ball stable on top. The ball position is detected with a webcam, processed in Python on a laptop, and sent to an ESP32 through WebSockets, where a PD control loop adjusts the plate angle.

Watch Demo: https://youtu.be/whYIulDktMQ

# Features
3-servo balancing platform
Webcam-based ball detection
Python image processing
ESP32 communication through WebSockets
PD control for plate stabilization

# Hardware
ESP32
3x SG90 servos
Webcam
Balancing plate with a microfiber cloth on top to increase grip
Yellow ball
Power supply
Laptop for image processing

![Ball-Balancer](Media/Final%20(2).jpeg)

# How it works
A webcam captures the position of the ball on the plate. A Python script processes the image, detects the yellow ball, and computes its position. The position data is sent to the ESP32 through WebSockets. The ESP32 runs a PD control loop and adjusts the three servos to tilt the plate and keep the ball balanced.

# Setup
Assemble the balancing platform
Mount the three servos under the plate
Connect the servos to the ESP32
Run the Python ball detection script on the laptop
Start communication between the laptop and the ESP32
Power the system and tune the controller

# Notes
Lighting conditions affect ball detection accuracy
Servo calibration is important for stable balancing
The PD controller can be tuned for smoother response
This project combines computer vision, control systems, and embedded programming
