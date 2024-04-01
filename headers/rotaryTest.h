#ifndef ROTARYTEST_H
#define ROTARYTEST_H

// To exit, press menu and rotary button at the same time
void rotaryTest(){

  // Setup
  
  // Loop
  int loopDelay = -1;
  int loopCounter = 0;
  for(;;){
    // This bit checks for the menu button press and handles the loop conter
    // Menu Check
    delay(50);
    if (loopDelay < 0){
      if (wheel.readM() && wheel.readB()) {break;}
    } else if (loopCounter < loopDelay) {
      if (wheel.readM() && wheel.readB()) {break;}
      loopCounter += 50;
      continue;
    } else {
      loopCounter = 0;
    }

    //Put whatever code you want to loop here
    // Code
    dma_display->clearScreen();
    dma_display->setCursor(1,1 + fontDelta);
    dma_display->print(wheel.readR());
    dma_display->setCursor(1,12 + fontDelta);
    dma_display->print(wheel.readB());
    dma_display->setCursor(7,12 + fontDelta);
    dma_display->print(wheel.getB());
    dma_display->setCursor(21,12 + fontDelta);
    dma_display->print(wheel.readM());
    dma_display->setCursor(27,12 + fontDelta);
    dma_display->print(wheel.getM());
    dma_display->setCursor(1,23 + fontDelta);
    dma_display->print(wheel.getR());
    
  }
  
}

#endif
