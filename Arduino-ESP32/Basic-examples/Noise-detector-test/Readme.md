# Noise detection with KY-037 and the ESP32 in Arduino

## Introduction

This project is for testing purpose and provides a working example to read out the binary noise detection of the noise detection sensor KY-037. The code is using an interrupt and prints the counted noise hits every 15 seconds.

### Usage

Just compile and upload the ".ino" file to the board, connect the sensor as shown below and the data will be shown in the serial terminal. Some KY-037 board also have an analog output but this will not be used in this example.

#### Fine tuning the sensor
After connecting the pins of the sensor as shown below and connect the ESP32 development board to power. You should see the right (power) LED of the noise sensor lit up. The left LED (L2) is depending on the resistor setting also on or off.

My advise is to go to a quiet room and adjust the resistor to a value where the LED L2 just goes off. This sets the sensitive of the sensor to your current noise level which is "quite". 

Now you shall see higher counts when noise is higher and a count of 0 when it is quiet.

### Schematic

![SDS011](pictures/KY038-esp32.png)
 
### Components
* [KY-037](https://create.arduino.cc/projecthub/electropeak/how-to-use-ky-037-sound-detection-sensor-with-arduino-a757a7)
* [ESP32 development board](https://www.espressif.com/en/products/devkits)
* [Arduino](https://www.arduino.cc) 


