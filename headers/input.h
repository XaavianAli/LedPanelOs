#ifndef INPUT_H
#define INPUT_H

//Kinda snapped with how stupid this is, created off of the perc30
class rotary {
  public:
  AiEsp32RotaryEncoder r;
  int b;
  int m;
  int previousR = 0;
  bool pressedM = false;
  bool pressedB = false;
  int readR(){
    int current = r.readEncoder();
    if (current == previousR) {
      return 0;
    } else if (current > previousR) {
      previousR = current;
      return 1 * reverseRotary;
    } else {
      previousR = current;
      return -1 * reverseRotary;
    }
  }
  int getR() {
    return r.readEncoder();
  }
  int readB(){
    int current = !digitalRead(b);
    if (current == 1 && !pressedB){
      pressedB = true;
      return 1;
    } else if (current == 0 && pressedB){
      pressedB = false;
    }
    return 0;
  }
  int getB() {
    return !digitalRead(b);
  }
  int readM(){
    int ccurrent = digitalRead(m);
    if (ccurrent == 1 && !pressedM){
      pressedM = true;
      return 1;
    } else if (ccurrent == 0 && pressedM){
      pressedM = false;
    }
    return 0;
  }
  int getM() {
    return digitalRead(m);
  }
};

rotary wheel; // Horrible name

void IRAM_ATTR readEncoderISR()
{
  wheel.r.readEncoder_ISR();
}

void rotarySetup() {

  wheel.r = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN, ROTARY_ENCODER_STEPS);
  wheel.b = 34;
  wheel.m = 1;
  pinMode(wheel.b, INPUT_PULLUP);
  pinMode(wheel.m, INPUT_PULLUP);
  wheel.r.begin();
  wheel.r.setup(readEncoderISR);
  wheel.r.setBoundaries(0, 100000000, false);
  // TODO: Fix bug where 50 million consecutive wheel turns in the same direction, the 50 millionth + 1 turn is inverted
  wheel.r.setEncoderValue(50000000);
  dma_display->clearScreen();
  dma_display->setCursor(1,1 + fontDelta);
  dma_display->print("Rotary OK");
  delay(1000);
}

#endif
