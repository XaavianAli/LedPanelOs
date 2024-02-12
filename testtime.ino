#include <WiFi.h>
#include <UnixTime.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <ESP32Ping.h>

#include "time.h"
#include "display.h"
#include "icons.h"

UnixTime stamp(-5);

String load[4] = {"-","\\","|","/"};

const char* ssid = "Homenet-Games";
const char* password = "i love supersmashbros";
const char* ntpServer = "pool.ntp.org";
unsigned long epochTime;

// Function that gets current epoch time
unsigned long getTime() {
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return(0);
  }
  time(&now);
  return now;
}

// Initialize WiFi
void initWiFi() {

  dma_display->clearScreen();
  dma_display->setCursor(1,1);
  dma_display->setTextColor(dma_display->color444(0,8,15));
  dma_display->print("Connecting");
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  for (int i = 0; WiFi.status() != WL_CONNECTED; i++) {
    //Serial.print('.');
    dma_display->clearScreen();
    dma_display->setCursor(1,1);
    dma_display->setTextColor(dma_display->color444(0,8,15));
    dma_display->print("Connecting");
    dma_display->setCursor(1,12);
    dma_display->print(load[i%4]);
    delay(250);
  }
  Serial.println(WiFi.localIP());
  dma_display->clearScreen();
  dma_display->setCursor(1,1);
  dma_display->print("Connected!");
  dma_display->setCursor(1,12);
  dma_display->print(WiFi.localIP());

  bool success = Ping.ping("www.google.com", 3);
 
  if(!success){
    Serial.println("Ping failed");
    dma_display->clearScreen();
    dma_display->setCursor(1,1);
    dma_display->print("Ping BAD");
    return;
  }
 
  Serial.println("Ping succesful.");
  dma_display->clearScreen();
  dma_display->setCursor(1,1);
  dma_display->print("Ping OK");
}

void displayTime(){

  String curTime = "ERR";
  String curDate = "ERR";
  String curWeekDay = "ERR";
  String curMonth = "ERR";
  String curHour = "ER";
  String curMin = "ER";
  String curSec = "ER";
  
  epochTime = getTime();
  if (epochTime == 0){
    dma_display->clearScreen();
    dma_display->setCursor(1,1);
    dma_display->setTextColor(dma_display->color444(0,8,15));
    dma_display->print("ERROR!\nCould not get time");
    delay(1000);
    return;
  }
  //Serial.println(getTime());
  //Serial.println(epochTime);
  stamp.getDateTime(epochTime);
  //Serial.print(stamp.dayOfWeek);

  switch(stamp.dayOfWeek) {
    case 1:
      curWeekDay = "Mon";
      break;
    case 2:
      curWeekDay = "Tue";
      break;
    case 3:
      curWeekDay = "Wed";
      break;
    case 4:
      curWeekDay = "Thu";
      break;
    case 5:
      curWeekDay = "Fri";
      break;
    case 6:
      curWeekDay = "Sat";
      break;
    case 7:
      curWeekDay = "Sun";
      break;
  }

  switch(stamp.month) {
    case 1:
      curMonth = "Jan";
      break;
    case 2:
      curMonth = "Feb";
      break;
    case 3:
      curMonth = "Mar";
      break;
    case 4:
      curMonth = "Apr";
      break;
    case 5:
      curMonth = "May";
      break;
    case 6:
      curMonth = "Jun";
      break;
    case 7:
      curMonth = "Jul";
      break;
    case 8:
      curMonth = "Aug";
      break;
    case 9:
      curMonth = "Sep";
      break;
    case 10:
      curMonth = "Oct";
      break;
    case 11:
      curMonth = "Nov";
      break;
    case 12:
      curMonth = "Dec";
      break;
  }

  curHour = String(stamp.hour);
  if (stamp.hour < 10) {curHour = "0" + curHour;}
  curMin = String(stamp.minute);
  if (stamp.minute < 10) {curMin = "0" + curMin;}
  curSec = String(stamp.second);
  if (stamp.second < 10) {curSec = "0" + curSec;}

  curDate = curWeekDay + " " + curMonth + " " + stamp.day;
  curTime = curHour + ":" + curMin + ":" + curSec;
  
  dma_display->clearScreen();
  
  dma_display->setCursor(1,1);
  dma_display->setTextColor(dma_display->color444(0,8,15));
  dma_display->print(curDate);
  //Serial.println(curDate);

  dma_display->setCursor(1,12);
  dma_display->setTextColor(dma_display->color444(0,8,15));
  dma_display->print(curTime);
  Serial.println(curTime);
  
  delay(1000);
}

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
  printIcon(0,0,&windows);
  delay(2500);

  // fill the screen with 'black'
  dma_display->fillScreen(dma_display->color444(0, 0, 0));
  dma_display->setTextSize(1);     // size 1 == 8 pixels high
  dma_display->setTextWrap(true); // Don't wrap at end of line - will do ourselves

  Serial.begin(115200);
  
  initWiFi();
  configTime(0, 0, ntpServer);
}

void loop() {
  displayTime();
  //printKirby(kirby);
  //dma_display->fillScreen(myRED);
  //printIcon(0,0,&korby);
}
