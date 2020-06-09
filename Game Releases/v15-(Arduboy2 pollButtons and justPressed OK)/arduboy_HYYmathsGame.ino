//HYY
//February 26th, 2019
//Maths Calculation Game

#include <Arduboy2.h>
#include <timer.h>

Arduboy2 arduboy;

//variables for time
unsigned long timeOri; //if ans is correct, add time to timeOri
unsigned long timeNow;
unsigned long timeDiff;
int timeRemain;

//variables for level & score
int score;
int level;

//variables for setting questions
int qtnNum;
int answer;
int num1;
int num2;
int num3;
String oper;
String qtn;

//variables for answer options
int up;
int down;
int left;
int right;


void setup() {
  arduboy.begin();
  arduboy.clear();
  timeOri = millis();
  unsigned long timeOri = 0;
  unsigned long timeNow = 0;
  unsigned long timeDiff = 0;
  level = 1;
  up = 0;
  down = 0;
  left = 0;
  right = 0;
}

void loop() {

  arduboy.clear();
  arduboy.setCursor(0, 0);
  arduboy.print("Time:   ");
  timeNow = millis();
  timeDiff = timeNow - timeOri;
  float timeIn100Sec = timeDiff/10;
  float timeleft = 10 - timeIn100Sec/100;
  
  if(timeleft<0){ // to fix the -ve seconds problem
    timeleft = 0;
    }
    
  if(String(timeleft).length()<5){    //to make sure the time will not "jump"
    arduboy.print(" ");
    }
  arduboy.print(timeleft);
  arduboy.print(" / 10.00");

  arduboy.print("\n");
  arduboy.print("Lv.");
  arduboy.print(level);

  int i = String(level*timeleft).length();
  for(i;i<10;i++){
  arduboy.print(" ");
  }
  
  arduboy.print("Score: ");
  arduboy.print(level*timeleft);
  arduboy.print("\n");


//Reserved for button handling



//Reserved for question generation (need to be unchanged for each question, i.e. keep inside the "answering loop", change until the end)

arduboy.pollButtons();
if (arduboy.justPressed(UP_BUTTON) == true) {


    char operAll[4] = {"+-*/"};
    arduboy.initRandomSeed();
    int randoper = random(0, 4);
    oper = operAll[randoper];
    qtn = (String)num1+" "+oper+" "+(String)num2;

  
}


//Here are the question & answer section

  int i0 = 0;
  for(i0;i0<11;i0++){
    arduboy.print("\\");
    arduboy.print("/");
    }
  arduboy.print("\n");
  
  arduboy.print("    ");
  arduboy.print(up);
  int i2 = String(up).length();
  for(i2;i2<6;i2++){
    arduboy.print(" ");
    }
  arduboy.print("/ Question:");
  arduboy.print("\n");
  
  arduboy.print("    |     \\");
  arduboy.print("\n");
  
  if(String(left).length() == 1){
  arduboy.print(" ");
  }
  arduboy.print(" ");
  arduboy.print(left);
  arduboy.print("-+-");
  arduboy.print(right);
  int i3 = String(right).length();
  for(i3;i3<4;i3++){
    arduboy.print(" ");
    }
  arduboy.print("/  ");
  arduboy.print(qtn);
  arduboy.print("\n");
  
  arduboy.print("    |     \\");
  arduboy.print("\n");
  
  arduboy.print("    ");
  arduboy.print(down);
  int i4 = String(down).length();
  for(i4;i4<6;i4++){
    arduboy.print(" ");
    }
  arduboy.print("/  = ?");


//Reserved for correct/wrong ans determination
  
  
  
  if(timeIn100Sec > 1000){
    timeOri = millis();
  }
  arduboy.display();
}
