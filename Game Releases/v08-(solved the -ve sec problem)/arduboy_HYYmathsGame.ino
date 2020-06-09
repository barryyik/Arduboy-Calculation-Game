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

int up;
int down;
int left;
int right;


void setup() {
  arduboy.begin();
  arduboy.clear();
  timeOri = millis();
  level = 1;
  up = 0;
  down = 0;
  left = 0;
  right = 0;
}

void loop() {
  arduboy.clear();
  arduboy.setCursor(0, 0);
  arduboy.print("Time: ");
  timeNow = millis();
  timeDiff = timeNow - timeOri;
  float timeIn100Sec = timeDiff/10;
  float mygoal = 10 - timeIn100Sec/100;
  
  if(mygoal<0){ // to fix the -ve seconds problem
    mygoal = 0;
    }
    
  if(String(mygoal).length()<5){    //to make sure the time will not "jump"
    arduboy.print(" ");
    }
  arduboy.print(mygoal);
  arduboy.print(" / 10.00");

  arduboy.print("\n");
  arduboy.print("Level =");
  arduboy.print(level);

  arduboy.print("\n");
  arduboy.print("Score =");
  arduboy.print(score);

  arduboy.print("\n");
  arduboy.print("          ");
  arduboy.print(up);
  arduboy.print("\n");
  arduboy.print("          v");
  arduboy.print("\n");
  arduboy.print("         > <");
  arduboy.print("\n");
  arduboy.print("          ^");
  arduboy.print("\n");
  arduboy.print("          ");
  arduboy.print(down);




  
  
  if(timeIn100Sec > 1000){
    timeOri = millis();
  }
  arduboy.display();
}
