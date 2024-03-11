// Entirely stolen from example sketch from panel library hehe

#ifndef PLASMA_H
#define PLASMA_H

CRGB currentColor;
CRGBPalette16 palettes[] = {HeatColors_p, LavaColors_p, RainbowColors_p, RainbowStripeColors_p, CloudColors_p};
CRGBPalette16 currentPalette = palettes[0];
uint16_t time_counter = 0, cycles = 0, fps = 0;
unsigned long fps_timer;

CRGB ColorFromCurrentPalette(uint8_t index = 0, uint8_t brightness = 255, TBlendType blendType = LINEARBLEND) {
    return ColorFromPalette(currentPalette, index, brightness, blendType);
}

void plasma(){

  // Setup
  int pcount = 0;

  // Loop
  int loopDelay = -1;
  int loopCounter = 0;
  
  for(;;){
    
    // Menu Check
    delay(50);
    if (loopDelay < 0){
      if (wheel.readM()) {break;}
      if (wheel.readB()) {pcount++; currentPalette = palettes[pcount%5];};
    } else if (loopCounter < loopDelay) {
      if (wheel.readM()) {break;}
      loopCounter += 50;
      continue;
    } else {
      loopCounter = 0;
    }

    // Code
    for (int x = 0; x < 64; x++) {
            for (int y = 0; y <  32; y++) {
                int16_t v = 0;
                uint8_t wibble = sin8(time_counter);
                v += sin16(x * wibble * 3 + time_counter);
                v += cos16(y * (128 - wibble)  + time_counter);
                v += sin16(y * x * cos8(-time_counter) / 8);

                currentColor = ColorFromPalette(currentPalette, (v >> 8) + 127); //, brightness, currentBlendType);
                dma_display->drawPixelRGB888(x, y, currentColor.r, currentColor.g, currentColor.b);
            }
    }

    ++time_counter;
    ++cycles;
    ++fps;

    if (cycles >= 1024) {
        time_counter = 0;
        cycles = 0;
    }
    
  }
  
}

#endif
