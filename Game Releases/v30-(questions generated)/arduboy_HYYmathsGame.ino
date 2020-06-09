//HYY
//February 26th, 2019
//Maths Calculation Game

#include <Arduboy2.h>
#include <timer.h>

Arduboy2 arduboy;

#define EEPROM_HIGHESTSCORE                 EEPROM_STORAGE_SPACE_START


//variables for game play
int gameOver;
long HighestScoreHYYx100;
int stayInHighestScoreScreen;
int showGameOver;
int delay0;
int delay1;
int delay2;
int delay3;


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
int qtnNum; //number of question
int answer; //1,2,3,4 ==> up, down, left, right
int dummy1; //for question formation (dummy)
int dummy2;
int dummy3;
int num1; //for question formation num1 ? num2 = num3
int num2;
int num3; //This the the answer for each question
String oper;
String qtn;
int maxForDum;

String operAll; //+-*/
int randoper;

String UDLR;
String randCtrl;
String randUDLR;
int randNumForUDLR;


int ansGen; //trigger number for qtn and ans generation


//variables for answer options
int up;
int down;
int left;
int right;


//Set up ############################################################################################

void setup() {
  arduboy.begin();
  arduboy.clear();
  
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

  arduboy.initRandomSeed();
  answer = random(0, 4);

  ansGen = 0;

  gameOver = 1;
  stayInHighestScoreScreen = 1;
  showGameOver = 0;
  
}




//When the correct button is pressed ############################################################################################


void buttonCorrectAction() {
    
    timeOri = timeOri + timeRewardVar;
    if(timeOri>timeNow){
      timeOri = timeNow;
      }

    score = score + (level*timeleft);
    ansGen = 0;
    qtnNum = qtnNum + 1;
    
}



//When the wrong button is pressed ############################################################################################


void buttonWrongAction() {
    timeOri = timeOri - timePenalty;
    if(timeDiff > 10000){
      timeOri = timeNow;     // time should change to 0, and game is over
      }
}



//Dummy question formation ############################################################################################




//Question & answer generation ############################################################################################

void qtnAndAnsGeneration() {
  
//Generation of up, down, left, right answer options ##########
  
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
    
//Generation of maths operaters ##########

    operAll = "+-*/";
    arduboy.initRandomSeed();
    randoper = random(0, 4);
    oper = operAll[randoper];
    
//Generation of dummies for question formation ##########
    
    maxForDum = level + 9;
    
    arduboy.initRandomSeed();
    dummy1 = random(0, maxForDum);
    
    arduboy.initRandomSeed();
    dummy2 = random(0, maxForDum);
    
    if (randoper == 0){
      dummy3 = dummy1 + dummy2;
    } else if (randoper == 1){
      dummy3 = dummy1 + dummy2;
    } else if (randoper == 2){
      dummy3 = dummy1 * dummy2;
    } else if (randoper == 3){
      dummy3 = dummy1 * dummy2;
    }
    
//Matching dummies and num123 ##########

    if (randoper == 0){
      num1 = dummy1;
      num2 = dummy2;
      num3 = dummy3;
    } else if (randoper == 1){
      num1 = dummy3;
      num2 = dummy1;
      num3 = dummy2;
    } else if (randoper == 2){
      num1 = dummy1;
      num2 = dummy2;
      num3 = dummy3;
    } else if (randoper == 3){
      num1 = dummy3;
      num2 = dummy1;
      num3 = dummy2;
    }
    
//Whole question formation ##########
    
    qtn = (String)num1+" "+oper+" "+(String)num2;
    
//Whole question formation ##########
    
    
    
    ansGen = 1; //End of qtn and ans generation ##########
}




//Game start screen ############################################################################################

void gameStartScreen(){

    arduboy.clear();
    
    delay1 = 0;
    delay2 = 0;
    delay3 = 0;
  
    arduboy.print("*********************");
    arduboy.print("\n");
    arduboy.print("*********************");
    arduboy.print("\n");
    arduboy.print("**                 **");
    arduboy.print("\n");
    arduboy.print("**  HYY MATH GAME  **");
    arduboy.print("\n");
    arduboy.print("** -Press Any Key- **");
    arduboy.print("\n");
    arduboy.print("**                 **");
    arduboy.print("\n");
    arduboy.print("*********************");
    arduboy.print("\n");
    arduboy.print("*********************");

    arduboy.pollButtons();
    if (arduboy.justPressed(UP_BUTTON) == true || arduboy.justPressed(DOWN_BUTTON) == true || arduboy.justPressed(LEFT_BUTTON) == true || arduboy.justPressed(RIGHT_BUTTON) == true || arduboy.justPressed(A_BUTTON) == true || arduboy.justPressed(B_BUTTON) == true) {
      rulesAndHighestScoreScreen();
    }

    arduboy.display();


}



//Rules and highest score screen ############################################################################################


void rulesAndHighestScoreScreen(){
  while (stayInHighestScoreScreen == 1){
    arduboy.clear();
    arduboy.print("\n");
    arduboy.print("\n");
    arduboy.print("     Highest Score:  ");
    arduboy.print("\n");
    arduboy.print("\n");
    arduboy.print("\n");

    HighestScoreHYYx100 = EEPROM.get(EEPROM_HIGHESTSCORE, HighestScoreHYYx100);
    float HighestScoreHYY = 0.00;
    HighestScoreHYY = (float)HighestScoreHYYx100 / 100;


    int iForHighScore = String(HighestScoreHYY).length();
    for(iForHighScore;iForHighScore<21;iForHighScore = iForHighScore+2){
      arduboy.print(" ");
    }
  
    arduboy.print(HighestScoreHYY);

  
    arduboy.pollButtons();
    if (arduboy.justPressed(UP_BUTTON) == true || arduboy.justPressed(DOWN_BUTTON) == true || arduboy.justPressed(LEFT_BUTTON) == true || arduboy.justPressed(RIGHT_BUTTON) == true || arduboy.justPressed(A_BUTTON) == true || arduboy.justPressed(B_BUTTON) == true) {
      gameOver = 0;
      stayInHighestScoreScreen = 0;
      timeOri = millis()+10000;
    }

  
  arduboy.display();
  }
}




//The loop ############################################################################################


void loop() {


//Trigger question and answer generation ####################

if(ansGen == 0){
  qtnAndAnsGeneration();
}

  

//Trigger game start screen ####################

  while (gameOver == 1) {
    delay0 = 0;
    delay1 = 0;
    delay2 = 0;
    delay3 = 0;
    gameStartScreen();
  }



//Create game interface ####################

  arduboy.clear();

  arduboy.setCursor(0, 0);
  arduboy.print("Time:   ");
  timeNow = millis() + 10000;
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
  
  if(qtnNum > 10){
    qtnNum = 1;
    level = level + 1;
  }
  
  arduboy.print(level);

  int i = String(score).length() + String(level).length();
  for(i;i<11;i++){
  arduboy.print(" ");
  }
  
  arduboy.print("Score: ");
  arduboy.print(score);
  arduboy.print("\n");



//Time reward AND Time penalty  ####################

timeRewardVar = 3000 - (level-1)* 500;
timeReward = 1000 + timeRewardVar;

timePenaltyVar = (level-1)* 100;
timePenalty = 2000 + timePenaltyVar;





//Correct OR Wrong button is pressed  ####################

arduboy.pollButtons();
if (arduboy.justPressed(UP_BUTTON) == true || arduboy.justPressed(DOWN_BUTTON) == true || arduboy.justPressed(LEFT_BUTTON) == true || arduboy.justPressed(RIGHT_BUTTON) == true) {
  if(arduboy.justPressed(UP_BUTTON) == true && answer == 0){
    buttonCorrectAction();
    }else if(arduboy.justPressed(DOWN_BUTTON) == true && answer == 1){
      buttonCorrectAction();
      }else if(arduboy.justPressed(LEFT_BUTTON) == true && answer == 2){
        buttonCorrectAction();
        }else if(arduboy.justPressed(RIGHT_BUTTON) == true && answer == 3){
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
  arduboy.print("/ Lv.");
  arduboy.print(level);
  arduboy.print(" #");
  arduboy.print(qtnNum);
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
    if(100*score > EEPROM.get(EEPROM_HIGHESTSCORE, HighestScoreHYYx100)){
      long scorex100 = 100*score;
      EEPROM.put(EEPROM_HIGHESTSCORE, scorex100);
    }


      showGameOver = 1;
      
      while (showGameOver == 1){
        
        arduboy.clear();
        while(delay0 == 0){
          delay0 = 1;
          arduboy.clear();
          arduboy.display();
          delay(1000);
        }    
        
        
        arduboy.print("\n");
        arduboy.print("      ");
        arduboy.print("GAME OVER");
        
        
        
        while(delay1 == 0){
          delay1 = 1;
          arduboy.display();
          delay(1000);
        }

        
        
        arduboy.print("      ");
        arduboy.print("\n");
        arduboy.print("\n");
        arduboy.print("Score: ");
        arduboy.print(score);
        

        
        while(delay2 == 0){
          delay2 = 1;
          arduboy.display();
          delay(1000);
        }

        
        
        arduboy.print("\n");
        arduboy.print("\n");
        arduboy.print("Highest: ");
      
        HighestScoreHYYx100 = EEPROM.get(EEPROM_HIGHESTSCORE, HighestScoreHYYx100);
        float HighestScoreHYY = 0.00;
        HighestScoreHYY = (float)HighestScoreHYYx100 / 100;
        
        arduboy.print(HighestScoreHYY);
        arduboy.print("\n");
        arduboy.print("\n");
        
        
        
        
        while(delay3 == 0){
          delay3 = 1;
          arduboy.display();
          delay(1000);
        }
        
        
        arduboy.print("   -Press Any Key-   ");
        arduboy.pollButtons();
        if (arduboy.justPressed(UP_BUTTON) == true || arduboy.justPressed(DOWN_BUTTON) == true || arduboy.justPressed(LEFT_BUTTON) == true || arduboy.justPressed(RIGHT_BUTTON) == true || arduboy.justPressed(A_BUTTON) == true || arduboy.justPressed(B_BUTTON) == true) {
          showGameOver = 0;
        }
        arduboy.display();
      }

        


    score = 0.00;
    gameOver = 1;
    stayInHighestScoreScreen = 1;
    qtnNum = 1;
    level = 1;
  }
  arduboy.display();
}
