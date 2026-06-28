# Ball Balancer

![Ball Balancer](Media/Final%20(1).jpeg)

A ball balancing platform built using an ESP32, three SG90 servos and computer vision.

The system uses a webcam to track the position of a yellow ball on a tilting platform. A Python script processes the camera image and sends the ball coordinates to the ESP32 through Sockets, where a PD controller adjusts the platform angle to keep the ball balanced.

Watch demo: https://youtu.be/whYIulDktMQ

## What I learned

- Basic PD control systems
- Real-time computer vision using Python and OpenCV
- Communication between a laptop and ESP32 through TCP Sockets
- Coordinating multiple servos for platform movement
- Mechanical design and CAD modeling for balancing mechanisms

## Challenges

- Tuning the PD controller for stable balancing
- Reducing servo jitter and oscillations
- Handling camera latency and noisy position detection
- Calibrating the platform and servo angles
- Building joints and minimizing mechanical play

## Limitations

- SG90 servos are not very precise and introduce vibration
- Webcam latency limits response speed
- Lighting conditions affect ball detection accuracy
- The balancing area is relatively small
- Mechanical backlash reduces stability and repeatability

## Possible Improvements

- Using faster and more precise servos
- Replacing the webcam with a higher quality and lower latency camera
- Increasing the platform size for a larger balancing area
- Using better ball joints and stronger mechanical components
- Improving filtering and control algorithms for smoother motion
- Running the image processing directly on embedded hardware
