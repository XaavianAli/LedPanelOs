// Made by Xaavian Ali :) contact at xaavian@hotmail.com
// Version 0.1.0

//PIN 25 ON THE WROOM-ESP32 SHOULD NOT BE USED AS GPIO FOR VOLTAGE SENSITIVE DEVICES WHEN WIFI IS ENABLED AS IT CAUSES VOLTAGE SPIKES DURING WIFI UPLINK/DOWNLINK OPERATIONS
//Pin 2 also causes some dumb issues
//Use Serial1 or Serial2 instead of Serial or else you degrade the speed of the LED panel (Unless you set a very high baud rate I guess (Which you should do))

#include <WiFi.h>
#include <UnixTime.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <ESP32Ping.h>
#include <Adafruit_GFX.h>
#include <ArduinoJson.h>
#include "AiEsp32RotaryEncoder.h"

#include "./headers/const.h"
#include "./headers/display.h"
#include "./headers/sd.h"
#include "./headers/config.h"
#include "./headers/system.h"
#include "./headers/icons.h"
#include "./headers/input.h"
#include "./headers/apps.h"

void setup() {

  // Module configuration
  HUB75_I2S_CFG mxconfig(
    PANEL_RES_X,   // module width
    PANEL_RES_Y,   // module height
    PANEL_CHAIN    // Chain length
  );

  // Display Setup
  dma_display = new MatrixPanel_I2S_DMA(mxconfig);
  dma_display->begin();
  dma_display->setBrightness8(90); //0-255
  dma_display->clearScreen();

  //Splash Screen
  printIcon(0,0,&splash);
  delay(3000);

  // fill the screen with 'black'
  dma_display->fillScreen(dma_display->color444(0, 0, 0));
  dma_display->setTextColor(dma_display->color444(0,8,15));
  dma_display->setTextSize(1);     // size 1 == 8 pixels high
  dma_display->setCursor(0,0 + fontDelta);
  //dma_display->setFont(&Tiny3x3a2pt7b);
  dma_display->setTextWrap(true);

  Serial.begin(500000);

  sdSetup();
  loadConfig();
  rotarySetup();
  initWiFi();
  initTime();

}

void loop(){

  // Setup
  dma_display->clearScreen();
  menuItem menuItems[] = {
    {"Clock", displayTime},
    {"Kirby", kirbyMe},
    {"Snake", snake},
    {"Rot.Test", rotaryTest},
    {"Plasma", plasma},
    {"Sample", sampleApp},
    {"Settings", reset},
    {"Reboot", reset}, 
  };
  int mod = sizeof(menuItems)/sizeof(menuItem);
  int select = mod * 1000000 + 1;
  int menuChar = 0;
  String menuChars[] = {"-",">"};
  wheel.readR();

  // Loop
  int loopDelay = 500;
  int loopCounter = 0;
  for(;;){
    
    // Menu Check
    delay(50);
    if (loopCounter < loopDelay) {
      select += wheel.readR();
      if (wheel.readB() == 1) {
        if (menuItems[select%mod].name == "Reboot") {
          menuItems[select%mod].start();
        }
        dma_display->clearScreen();
        dma_display->setCursor(1,1 + fontDelta);
        dma_display->print("Loading...");
        menuItems[select%mod].start();
        break;
      }
      dma_display->clearScreen();
      dma_display->setTextColor(dma_display->color444(0,8,15));
      dma_display->setCursor(1,1 + fontDelta);
      dma_display->print(menuItems[(select-1)%mod].name);
      dma_display->setTextColor(dma_display->color444(0,15,8));
      dma_display->setCursor(1,10 + fontDelta);
      dma_display->print(menuChars[menuChar%2]+String(menuItems[(select)%mod].name));
      dma_display->setTextColor(dma_display->color444(0,8,15));
      dma_display->setCursor(1,19 + fontDelta);
      dma_display->print(menuItems[(select+1)%mod].name);
      loopCounter += 50;
      continue;
    } else {
      loopCounter = 0;
    }

    // Code
    // TODO: fix bug where menu will crash after being on for 64 years straight
    menuChar++;
    
  }
  
}
