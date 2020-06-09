//HYY
//February 26th, 2019
//Maths Calculation Game

#include <Arduboy.h>
#include <timer.h>
Arduboy arduboy;
unsigned long timeOri = 0;
unsigned long timeNow = 0;
unsigned long timeDiff = 0;
float timeRemainIn1000Sec = 10000;

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
}

void loop() {
if(timeOri = 0){
  timeOri = millis();
}
else{
  arduboy.clear();
  arduboy.setCursor(0, 0);
  arduboy.print("Time: ");
  if(timeRemainIn1000Sec > 0){
    timeNow = millis();
    timeDiff = timeNow - timeOri;
    float timeIn1000Sec = timeDiff/100;
    timeRemainIn1000Sec = timeRemainIn1000Sec - timeIn1000Sec;
    if(timeRemainIn1000Sec < 0){
      timeRemainIn1000Sec = 0;
      }
  }else{
    float timeRemainIn1000Sec = 10000;
    timeNow = 0;
    timeDiff = 0;
    timeOri = 0;
  }
  arduboy.print(timeRemainIn1000Sec/1000);
  arduboy.print(" / 10.00");
  arduboy.display();
}
}
