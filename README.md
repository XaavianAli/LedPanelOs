# LedPanelOS *(Name Pending)*
# Introduction
This is just a little pet project of mine. The goal is to have a little stock-ticker like device that can sit on your desk and do neat things like show you live sports scores, track the prices of stocks, or simply display the time.
# Getting Started
## Hardware
### Supported Hardware
As of right now, an ESP32 (Original ESP WROOM 32) is being used as the brains. The ESP32-S2 and ESP32-S3 should also work fine, but have not been tested yet. A generic 32x64 LED panel used as display. Other hardware used includes a generic SD card reader. Buttons to be added in the future :)
### Wiring Diagram
To be created once wiring is *sorta* done (aka when buttons are added).
### Power
Oh boy.
## Software
Something about an SD card, arduino libraries idk
### Config files
There are config files on the SD card, so that you don't have to reflash the board to make a small change for something like changing what WiFi network the board uses
### How to flash ESP32
Use Arduino IDE dummy
## Applications
Goal is to have a little home screen where you can navigate to different apps. Currently in development.
### Current Apps
Currently, I only have a date and time app (Which is quite ugly to say the least). More coming in the future.
### How to add an app
Unsupported as of right now. If your app needs assets, consider putting them on the SD card in a folder with the application name, and loading them only when needed.
# Further Information
## Why did you do *x* like this? Wouldn't it be faster/better/safer to do it like *this* instead?
Probably.
## Can I use a different microcontroller for this? How about an Arduino UNO? A RaspberryPi? ESP8266?
Only the ESP32 will work directly out of the box with this code. It is HIGHLY dependent on [*this*](https://github.com/mrfaptastic/ESP32-HUB75-MatrixPanel-DMA) library for the graphics interface, which only supports the ESP32. If you want to port this to work with another microcontroller, you will have to completely replace the graphics interface. Keep in mind that for whatever you use, you'll need enough IO pins for the panel, buttons, and SD card reader. Also, microcontrollers like the Arduino UNO have a very small amount of SRAM on them, meaning they will most likely not be suitable for this type of project.
## Can I use this code in my own project?
Definitely feel free to use and/or modify this code to suit your needs! However, you may **NOT** monetize any project that uses this code, in full or in part. Open source is the backbone of the internet!
# Thanks
The following libraries were used to project. Thank you so much!
