#ifndef SAMPLE_H
#define SAMPLE_H

// Apps can only return void and take no arguments. Sorry!
void sampleApp(){

  // Do whatever set up you want done outside of the loop
  // Setup
  String x = "Hello";
  String y = "World!";

  // Setting loopDelay simulates whatever delay you'd like to have at the end of your loop
  // This is so that regardless of what delay you set for your loop, we still check for menu button press every ~50ms (depending on variable set in config)
  // Loop
  int loopDelay = 500;
  int loopCounter = 0;
  for(;;){
    // This bit checks for the menu button press and handles the loop conter
    // Menu Check
    delay(50);
    if (loopDelay < 0){
      if (wheel.readM()) {break;}
    } else if (loopCounter < loopDelay) {
      if (wheel.readM()) {break;}
      loopCounter += 50;
      continue;
    } else {
      loopCounter = 0;
    }

    //Put whatever code you want to loop here
    // Code
    dma_display->clearScreen();
    dma_display->setCursor(1,1 + fontDelta);
    dma_display->setTextColor(dma_display->color444(random(16),random(16),random(16)));
    dma_display->print(x);
    dma_display->setCursor(1,10 + fontDelta);
    dma_display->setTextColor(dma_display->color444(random(16),random(16),random(16)));
    dma_display->print(y);
    
  }
  
}

#endif

// Heres a blank template
/*
void sampleApp(){

  // Setup

  // Loop
  int loopDelay = 500;
  int loopCounter = 0;
  for(;;){
    
    // Menu Check
    delay(50);
    if (loopDelay < 0){
      if (wheel.readM()) {break;}
    } else if (loopCounter < loopDelay) {
      if (wheel.readM()) {break;}
      loopCounter += 50;
      continue;
    } else {
      loopCounter = 0;
    }

    // Code
    
  }

  // Clean up after yourself
  
}
*/
