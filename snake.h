#ifndef SNAKE_H
#define SNAKE_H

class snakePart {
  public:
    snakePart *next; // Why double linked list?
    snakePart *last;
    int x;
    int y;
    snakePart(int a, int b, snakePart *n, snakePart *l){
      x = a;
      y = b;
      next = n;
      last = l;
      return;
    }
};

snakePart *snakeHead;
snakePart *snakeTail;

class snakeFood {
  public:
    int x;
    int y;
    void spawn(){
      bool f = true;
      x = random(64);
      y = random(32);
      snakePart *c = snakeTail;
      while (c->next != NULL){
        if (c->x == x && c->y == y){
          f = false;
          break;
        }
        c = c->next;
      }
      if (!f) {
        spawn();
      }
      return;
    }
    snakeFood(){
      spawn();
    }
};

snakeFood *food;

void snake(){

  // Setup
  snakeHead = new snakePart(3, 15, NULL, NULL);
  snakeTail = new snakePart(2, 15, snakeHead, NULL);
  food = new snakeFood();
  snakeHead->last = snakeTail;
  dma_display->clearScreen();
  int in = 500000000;
  int dir = in % 4;
  snakePart *curs = NULL;
  bool dead = false;
  bool ateFood = false;

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

    // Code
    in += wheel.readR();
    dir = in % 4;

    if (ateFood){
      snakePart *snakeAdd = NULL;
      snakeAdd = new snakePart(snakeHead->x, snakeHead->y, snakeHead, snakeHead->last);
      snakeHead->last->next = snakeAdd; // Revolting bit of code here
      snakeHead->last = snakeAdd;
      ateFood = false;
    } else {
      curs = snakeTail;
      while(curs->next != NULL){
        curs->x = curs->next->x;
        curs->y = curs->next->y;
        curs = curs->next;
      }
    }
    
    switch(dir){
      case(0):
        snakeHead->x += 1;
        snakeHead->x %= 64; // Shouldn't hard code this, should be global display height & width vars
        break;
      case(1):
        snakeHead->y -= 1;
        if (snakeHead->y < 0){
          snakeHead->y = 31;
        }
        break;
      case(2):
        snakeHead->x -= 1;
        if (snakeHead->x < 0){
          snakeHead->x = 63;
        }
        break;
      case(3):
        snakeHead->y += 1;
        snakeHead->y %= 32;
        break;
      default:
        Serial.println("If youre seeing this message, something has gone extremely wrong beyond my comprehension. oWo");
    };

    if (food->x == snakeHead->x && food->y == snakeHead->y){
      ateFood = true;
      food->spawn();
    }

    if (!dead){
      int q = 0;
      curs = snakeTail;
      dma_display->clearScreen();
      while(curs != NULL){
        dma_display->drawPixelRGB888(curs->x, curs->y, 0, 255, 0);
        curs = curs->next;
        q++;
      }
      dma_display->drawPixelRGB888(food->x, food->y, 0, 0, 255);
    }

    curs = snakeTail;
    while (curs->next != NULL){
      if (curs->x == snakeHead->x && curs->y == snakeHead->y){
        dead = true;
        curs = snakeTail;
        while(curs != NULL){
          dma_display->drawPixelRGB888(curs->x, curs->y, 255, 0, 0);
          curs = curs->next;
        }
        break;
      }
      curs = curs->next;
    }
    
  }
  
}

#endif
