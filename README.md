# ESP32 Lidar Sensing: Integrating TTFMini with ESP-IDF
This repository hosts an ESP-IDF (Espressif IoT Development Framework) project designed for interfacing with the TTFMini Lidar sensor. Leveraging the capabilities of the ESP32 development platform, this project facilitates seamless integration of the TTFMini Lidar sensor into ESP32-based projects.

## Features:
TTFMini Lidar Integration: Provides comprehensive support for interfacing with the TTFMini Lidar sensor, allowing accurate distance measurements in ESP32 applications.

## Installation
### ESP-IDF
Install ESP-IDF by following the instructions in the Espressif IoT Development Framework (ESP-IDF) documentation.
https://docs.espressif.com/projects/esp-idf/en/stable/esp32/index.html 

## Usage

### Cloning micro-ROS Repository

Clone this repository by executing the following command:
```bash
git clone https://github.com/micro-ROS/micro_ros_espidf_component
```

### Once the repository is cloned, perform the following steps:

```bash
idf.py set-target esp32
idf.py menuconfig
```

### Build the project using:
```bash
idf.py build
```
### Flash the project onto your ESP32 board:
```bash
idf.py flash
```
OR
```bash
idf.py -p <PORT> flash 
```
### Monitor the output to observe the flight controller behavior:
```bash
idf.py monitor
```
OR
```bash
idf.py -p <PORT> monitor 
```
## Additional Notes
Ensure that your ESP32 board is properly connected and configured before flashing the project.
