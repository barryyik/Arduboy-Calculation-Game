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
unsigned long timeReward;
unsigned long timePenalty;

int timeRewardVar;
int timePenaltyVar;
float timeleft;


//variables for level & score
float score;
int level;

//variables for setting questions
int qtnNum;
int answer; // 1,2,3,4 ==> up, down, left, right
int num1;
int num2;
int num3;
String oper;
String qtn;

String operAll;
int randoper;

String UDLR;
String randCtrl;
String randUDLR;
int randNumForUDLR;

int ansGen;

String buttons;


//variables for answer options
int up;
int down;
int left;
int right;


void setup() {
  arduboy.begin();
  arduboy.clear();
  timeOri = millis();
  
  timeOri = 0;
  timeNow = 0;
  timeDiff = 0;
  
  level = 1;
  score = 0.00;
  up = 0;
  down = 0;
  left = 0;
  right = 0;

  qtnNum = 1;

  operAll = "+-*/";
  arduboy.initRandomSeed();
  randoper = random(0, 4);
  oper = operAll[randoper];
  qtn = (String)num1+" "+oper+" "+(String)num2;

  arduboy.initRandomSeed();
  answer = random(0, 4);

  ansGen = 0;


}




//Reserved for a new function when the correct button is pressed


void buttonCorrectAction() {
  
    arduboy.initRandomSeed();
    randoper = random(0, 4);
    oper = operAll[randoper];
    qtn = (String)num1+" "+oper+" "+(String)num2;
    
    timeOri = timeOri + timeRewardVar;
    if(timeOri>timeNow){
      timeOri = timeNow;
      }

    score = score + (level*timeleft);
    ansGen = 0;
    
}

//Reserved for a new function when the wrong button is pressed

void buttonWrongAction() {
  

    timeOri = timeOri - timePenaltyVar;
    if(timeOri>timeNow){
      timeOri = timeNow;
      }

    score = score + (level*timeleft);
    ansGen = 0;
    
}






void loop() {


//Reserved for question variables generation

if(ansGen == 0){

    arduboy.initRandomSeed();
    answer = random(0, 4);

    UDLR = "UDLR";

    randCtrl = "0000";
    randUDLR = (String)UDLR[answer];
    randCtrl[answer] = '1';
    while (randCtrl != "1111"){
      arduboy.initRandomSeed();
      randNumForUDLR = random(0, 4);
      if(randCtrl[randNumForUDLR] == '0'){
        randCtrl[randNumForUDLR] = '1';
        randUDLR = randUDLR + (String)UDLR[randNumForUDLR];
      }
    }
   

    ansGen = 1;
  
  }

  //Generate random UDLR pattern during initialisation

  
//  while (randCtrl != "1111"){
//    arduboy.initRandomSeed();
//    int randNumForUDLR = random(0, 4);
//    if(randCtrl[randNumForUDLR] = 0){
//      
//    }
//  }


  

  arduboy.clear();
  arduboy.setCursor(0, 0);
  arduboy.print("Time:   ");
  timeNow = millis();
  timeDiff = timeNow - timeOri;
  float timeIn100Sec = timeDiff/10;
  timeleft = 10 - timeIn100Sec/100;
  
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

  int i = String(score).length() + String(level).length();
  for(i;i<11;i++){
  arduboy.print(" ");
  }
  
  arduboy.print("Score: ");
  arduboy.print(score);
  arduboy.print("\n");


//Reserved for button handling



//Reserved for question generation (need to be unchanged for each question, i.e. keep inside the "answering loop", change until the end)

timeRewardVar = 3000 - (level-1)* 500;
timeReward = 1000 + timeRewardVar;

timePenaltyVar = (level-1)* 100;
timePenalty = 1000 + timePenaltyVar;


//Correct OR Wrong button is pressed

arduboy.pollButtons();

if (arduboy.justPressed(UP_BUTTON) == true || arduboy.justPressed(DOWN_BUTTON) == true || arduboy.justPressed(LEFT_BUTTON) == true || arduboy.justPressed(RIGHT_BUTTON) == true) {
  if(arduboy.justPressed(UP_BUTTON) == true && answer == 0 || arduboy.justPressed(DOWN_BUTTON) == true && answer == 1 || arduboy.justPressed(LEFT_BUTTON) == true && answer == 2 || arduboy.justPressed(RIGHT_BUTTON) == true && answer == 3){
    buttonCorrectAction();
    }else{
      buttonWrongAction();
      }

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
  arduboy.print(answer);              //For testingggggggggggggggggggggggggggggggggggggggggggggggggggggggg
  arduboy.print("_");              //For testingggggggggggggggggggggggggggggggggggggggggggggggggggggggg
  arduboy.print(randUDLR);              //For testingggggggggggggggggggggggggggggggggggggggggggggggggggggggg
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
