# LedPanelOS *(Name Pending)*
# Current Version: 0.0.0
# Introduction
### This is still a MAJOR work in progress. If you stumble upon this repo in this state, don't expect anything to work or make any sense
This is just a little pet project of mine. The goal is to have a little stock-ticker like device that can sit on your desk and do neat things like show you live sports scores, track the prices of stocks, or simply display the time.
# Getting Started
## Hardware
### Supported Hardware
As of right now, an ESP32 (Original ESP WROOM 32) is being used as the brains. The ESP32-S2 and ESP32-S3 should also work fine, but have not been tested yet. A generic 32x64 LED panel used as display. Any one with **THIS** connector at the back should work fine. Other hardware used includes an SD card reader, a simple push button, and a rotary encoder with push button. Any generic component should work fine for these.
### Wiring Diagram
On the TODO list.
### Power
Oh boy.
## Software
Something about an SD card, arduino libraries idk
### Config files
There are config files on the SD card, so that you don't have to reflash the board to make a small change for something like changing what WiFi network the board uses.
- **wifi.conf**: Stores WiFi SSID and passwords
### How to flash ESP32
Use Arduino IDE dummy
And install some libraries too
## Applications
From the main screen after booting, you can select whatevery app to run. You can return to the menu by pressing the menu button
### Current Apps
- **Clock (WIP)**: Displays date and time
- **Settings (WIP)**: Modify certain system settings
More coming in the future.
### How to add an app
To add an app. first create a `<appname>.h` file in the root directory of the project. Next, use the template in `sample.h` to make your app. Note that the main function must return void and take no arguments. When done, add `#include "<appname>.h"` to the `app.h` file. Finally, in `main.ino`, add your app in the `menuItems` array, by supplying its name, and the name of its function. These names are limited to 9 characters long.    
If your app needs assets, consider putting them on the SD card in a folder with the application name, and loading them only when needed.
# Further Information
## Why did you do *x* like this? Wouldn't it be faster/better/safer to do it like *this* instead?
Probably.
## The Arduino IDE is giving me an error when I try to flash the board, how do I fix it?
Google is your friend here. If you believe it's an issue with the code, please reach out to me and let me know.
## Can I use a different microcontroller for this? How about an Arduino UNO? A RaspberryPi? ESP8266?
Only the ESP32 will work directly out of the box with this code. It is **HIGHLY** dependent on [*this*](https://github.com/mrfaptastic/ESP32-HUB75-MatrixPanel-DMA) library for the graphics interface, which only supports the ESP32. If you want to port this to work with another microcontroller, you will have to completely replace the graphics interface which at that point just start your own thing from scratch. Keep in mind that for whatever you use, you'll need enough IO pins for the panel, buttons, and SD card reader. Also, microcontrollers like the Arduino UNO have a very small amount of SRAM on them, meaning they will most likely not be suitable for this type of project.
## Can I use a bigger LED panel? How about chaining multiple together?
It's currently unsupported. everything is made to run on one 32x64 display, it would look/act weird on anything else.
## Can I use this code in my own project?
Definitely feel free to use and/or modify this code to suit your personal needs! However, you may **NOT** monetize any project that uses this code, in full or in part. Keep in mind that this project also uses many libraries, and that you should make sure that you have permissions to use those in whatever way you need to.
# Thanks
The following libraries were used to project. Thank you so much!
# Changelog
## 0.0.0
- HEHEHA
