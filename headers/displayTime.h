#ifndef DISPLAYTIME_H
#define DISPLAYTIME_H

void displayTime(){

  // Setup
  
  stamp = new UnixTime(timeConf.zone);
  
  String curTime = "ERR";
  String curDate = "ERR";
  String curWeekDay = "ERR";
  String curMonth = "ERR";
  String curHour = "ER";
  String curMin = "ER";
  String curSec = "ER";

  // Loop
  int loopDelay = 1000;
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
    epochTime = getTime();
    if (epochTime == 0){
      dma_display->clearScreen();
      dma_display->setCursor(1,1 + fontDelta);
      dma_display->setTextColor(dma_display->color444(15,15,15));
      dma_display->print("ERROR!\nCould not get time");
      delay(1000);
      return;
    }
    //Serial.println(getTime());
    //Serial.println(epochTime);
    stamp->getDateTime(epochTime);
    //Serial.print(stamp.dayOfWeek);
  
    switch(stamp->dayOfWeek) {
      case 1:
        curWeekDay = "Mon";
        break;
      case 2:
        curWeekDay = "Tue";
        break;
      case 3:
        curWeekDay = "Wed";
        break;
      case 4:
        curWeekDay = "Thu";
        break;
      case 5:
        curWeekDay = "Fri";
        break;
      case 6:
        curWeekDay = "Sat";
        break;
      case 7:
        curWeekDay = "Sun";
        break;
    }
  
    switch(stamp->month) {
      case 1:
        curMonth = "Jan";
        break;
      case 2:
        curMonth = "Feb";
        break;
      case 3:
        curMonth = "Mar";
        break;
      case 4:
        curMonth = "Apr";
        break;
      case 5:
        curMonth = "May";
        break;
      case 6:
        curMonth = "Jun";
        break;
      case 7:
        curMonth = "Jul";
        break;
      case 8:
        curMonth = "Aug";
        break;
      case 9:
        curMonth = "Sep";
        break;
      case 10:
        curMonth = "Oct";
        break;
      case 11:
        curMonth = "Nov";
        break;
      case 12:
        curMonth = "Dec";
        break;
    }
  
    curHour = String(stamp->hour);
    if (stamp->hour < 10) {curHour = "0" + curHour;}
    curMin = String(stamp->minute);
    if (stamp->minute < 10) {curMin = "0" + curMin;}
    curSec = String(stamp->second);
    if (stamp->second < 10) {curSec = "0" + curSec;}
  
    curDate = curWeekDay + " " + curMonth + " " + stamp->day;
    curTime = curHour + ":" + curMin + ":" + curSec;
    
    dma_display->clearScreen();
    
    dma_display->setCursor(1,1 + fontDelta);
    dma_display->setTextColor(dma_display->color444(random(16),random(16),random(16)));
    dma_display->print(curDate);
  
    dma_display->setCursor(1,12 + fontDelta);
    dma_display->setTextColor(dma_display->color444(random(16),random(16),random(16)));
    dma_display->print(curTime);
  }
}

#endif
