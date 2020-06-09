//HYY
//February 26th, 2019
//Maths Calculation Game

#include <Arduboy.h>
#include <timer.h>
Arduboy arduboy;
unsigned long timeOri;
unsigned long timeNow;
unsigned long timeDiff;
unsigned long timeRemain;
int reset;

int answer;
int num1;
int num2;
int num3;
int oper;
int score;
int level;

void setup() {
  arduboy.begin();
  arduboy.clear();
  timeOri = 0;
  timeNow = 0;
  timeDiff = 0;
  timeRemain = 10000;
  reset = 0;
}

void loop() {
if(reset = 0){
  timeOri = millis();
  timeRemain = 10000;
  timeNow = 0;
  timeDiff = 0;
  timeOri = 0;
  reset = 1;
}
  arduboy.clear();
  arduboy.setCursor(0, 0);
  arduboy.print("Time: ");
  if(timeRemain > 0){
    timeNow = millis();
    timeDiff = timeNow - timeOri;
    timeRemain = timeRemain - timeDiff;
    if(timeRemain < 0){
      timeRemain = 0;
      reset = 0;
      }
  }else{
    reset = 0;
    }
  float timeRemainIn100Sec = timeRemain/10;
  arduboy.print(timeRemainIn100Sec/100);
  arduboy.print(" / 10.00");
  arduboy.display();
}
