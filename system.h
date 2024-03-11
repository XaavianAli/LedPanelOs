//Constants or wtv that shouldn't be stored on SD

#ifndef SYSTEM_H
#define SYSTEM_H

#define ROTARY_ENCODER_A_PIN 36
#define ROTARY_ENCODER_B_PIN 39
#define ROTARY_ENCODER_BUTTON_PIN -1
#define ROTARY_ENCODER_VCC_PIN -1
#define ROTARY_ENCODER_STEPS 4

UnixTime stamp(-5);

String load[4] = {"-","\\","|","/"};

// FOR THE LOVE OF GOD SQUASH THE COMMITS SO YOU CAN'T SEE THE WIFI PASSWORD IN GITHUB
const char* ssid = "Homenet-Games";
const char* password = "i love supersmashbros";
const char* ntpServer = "pool.ntp.org";
unsigned long epochTime;

const int fontDelta = 0;
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

  dma_display->clearScreen();
  dma_display->setCursor(1,1 + fontDelta);
  dma_display->print("Connecting");
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
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

#endif
