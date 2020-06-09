//HYY
//February 26th, 2019
//Maths Calculation Game

#include <Arduboy.h>
#include <timer.h>
Arduboy arduboy;
unsigned long timeOri = 0;
unsigned long timeNow = 0;
unsigned long timeDiff = 0;

int answer;
int num1;
int num2;
int num3;
int oper;
int score;
int level;
int timeRemain;

void setup() {
  arduboy.begin();
  arduboy.clear();
  timeOri = millis();
}

void loop() {
  arduboy.clear();
  arduboy.setCursor(0, 0);
  arduboy.print("Time: ");
  timeNow = millis();
  timeDiff = timeNow - timeOri;
  arduboy.print(timeDiff);
  arduboy.display();
}
