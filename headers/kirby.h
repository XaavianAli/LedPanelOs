#ifndef KIRBY_H
#define KIRBY_H

void kirbyMe(){
  
  // Setup
  dma_display->clearScreen();
  printIcon(0,0,&korby);
  
  // Loop
  int loopDelay = -1;
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
    
  }
  
}

#endif
