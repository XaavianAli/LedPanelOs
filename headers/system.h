//Constants or wtv that shouldn't be stored on SD

#ifndef SYSTEM_H
#define SYSTEM_H

#define ROTARY_ENCODER_A_PIN 36
#define ROTARY_ENCODER_B_PIN 39
#define ROTARY_ENCODER_BUTTON_PIN -1
#define ROTARY_ENCODER_VCC_PIN -1
#define ROTARY_ENCODER_STEPS 4

struct time_conf {
  int zone;
};

time_conf timeConf = {
  -5,
};

UnixTime* stamp;

String load[4] = {"-","\\","|","/"};

const char* ntpServer = "pool.ntp.org";
unsigned long epochTime;

const int reverseRotary = -1; // Switch between -1 and 1 to get desired function

struct menuItem {
  char name[10];
  void (*start)();
};

void(* resetFunc) (void) = 0; // This is so ghetto man omg theres gotta be a better way (Im not wiring anything tho)
void reset() {
  dma_display->clearScreen();
  dma_display->setCursor(1,1 + fontDelta);
  dma_display->print("Bye!");
  delay(700);
  resetFunc();
}

// Initialize WiFi
void initWiFi() {

  if (!sysConf.wifi_en) {
    dma_display->clearScreen();
    dma_display->setCursor(1,1 + fontDelta);
    dma_display->print("Wifi");
    dma_display->setCursor(1,10 + fontDelta);
    dma_display->print("Disabled");
    delay(2000);
    return;
  }

  dma_display->clearScreen();
  dma_display->setCursor(1,1 + fontDelta);
  dma_display->print("Connecting");
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(sysConf.wifi_ssid, sysConf.wifi_pswd);
  //Serial.print("Connecting to WiFi ..");
  for (int i = 0; WiFi.status() != WL_CONNECTED; i++) {
    //Serial.print('.');
    dma_display->clearScreen();
    dma_display->setCursor(1,1 + fontDelta);
    dma_display->setTextColor(dma_display->color444(0,8,15));
    dma_display->print("Connecting");
    dma_display->setCursor(1,12 + fontDelta);
    dma_display->print(load[i%4]);
    delay(250);
  }
  //Serial.println(WiFi.localIP());
  dma_display->clearScreen();
  dma_display->setCursor(1,1 + fontDelta);
  dma_display->print("Connected!");
  dma_display->setCursor(1,12 + fontDelta);
  dma_display->print(WiFi.localIP());

  bool success = Ping.ping("www.google.com", 3);
 
  if(!success){
    //Serial.println("Ping failed");
    dma_display->clearScreen();
    dma_display->setCursor(1,1 + fontDelta);
    dma_display->print("Ping BAD");
    return;
  }
 
  //Serial.println("Ping succesful.");
  dma_display->clearScreen();
  dma_display->setCursor(1,1 + fontDelta);
  dma_display->print("Ping OK");
  delay(1000);
}

void loadTimeConfig(){
  File file = SD.open("/time.json");
  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, file);
  if (error) {
    Serial.println(F("Failed to read file, using default configuration"));
    Serial.println(error.code());
    return;
  }
  timeConf.zone = doc["zone"];
  file.close();
}

void initTime(){

  configTime(0, 0, ntpServer);
  loadTimeConfig();

}

// Function that gets current epoch time
unsigned long getTime() {
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    //Serial.println("Failed to obtain time");
    return(0);
  }
  time(&now);
  return now;
}

#endif
