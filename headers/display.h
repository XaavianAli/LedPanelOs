/* 
 *  LED Matrix config
 */

#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <FastLED.h>

#ifndef DISPLAY_H
#define DISPLAY_H

#define PANEL_RES_X 64
#define PANEL_RES_Y 32
#define PANEL_CHAIN 1

MatrixPanel_I2S_DMA *dma_display = nullptr;

uint16_t myBLACK = dma_display->color565(0, 0, 0);
uint16_t myWHITE = dma_display->color565(255, 255, 255);
uint16_t myRED = dma_display->color565(255, 0, 0);
uint16_t myGREEN = dma_display->color565(0, 255, 0);
uint16_t myBLUE = dma_display->color565(0, 0, 255);

#endif
