#ifndef KIRBY_H
#define KIRBY_H

void kirbyMe(){
  
  // Setup
  dma_display->clearScreen();
  int i = 0;
  //printIcon(0,0,&korby);
  
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
    

    
    dma_display->clearScreen();
    printIcon(0,0,kirbys[i%2]);
    i++;

  }
  
}

#endif
