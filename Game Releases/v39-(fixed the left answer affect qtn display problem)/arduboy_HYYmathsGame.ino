//HYY
//February 26th, 2019
//Maths Calculation Game

#include <Arduboy2.h>
#include <timer.h>

Arduboy2 arduboy;

#define EEPROM_HIGHESTSCORE                 EEPROM_STORAGE_SPACE_START


//variables for game play
int gameOver;
float HighestScoreHYY;
int stayInRulesScreen;
int stayInHighestScore;
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
  stayInRulesScreen = 1;
  stayInHighestScore = 1;
  showGameOver = 0;
  
}




//When the correct button is pressed ############################################################################################


void buttonCorrectAction() {
    
    timeOri = timeOri + timeReward;
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

void dummyQtnGeneration(){
    maxForDum = level + 9;
    
    arduboy.initRandomSeed();
    dummy1 = random(0, maxForDum);

    arduboy.initRandomSeed();
    dummy2 = random(0, maxForDum);
    
    if(randoper == 3){  //To get rid of divided by zero ##########
      while(dummy1 == 0) {
        arduboy.initRandomSeed();
        dummy1 = random(0, maxForDum);
      }
    }
    
    
    if (randoper == 0){
      dummy3 = dummy1 + dummy2;
    } else if (randoper == 1){
      dummy3 = dummy1 + dummy2;
    } else if (randoper == 2){
      dummy3 = dummy1 * dummy2;
    } else if (randoper == 3){
      dummy3 = dummy1 * dummy2;
    }
}


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

    dummyQtnGeneration();
    
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



    if (answer == 0){  //Start of up #####
      up = num3;
    } else {
      dummyQtnGeneration();
      if (randoper == 0 || randoper == 2){
        up = dummy3;
      } else if (randoper == 1 || randoper == 3){
        up = dummy2;
      }
      while(up == num3){
        dummyQtnGeneration();
        if (randoper == 0 || randoper == 2){
          up = dummy3;
        } else if (randoper == 1 || randoper == 3){
          up = dummy2;
        }
      }
    } //End of up #####
    
    
    
    if (answer == 1){  //Start of down #####
      down = num3;
    } else {
      dummyQtnGeneration();
      if (randoper == 0 || randoper == 2){
        down = dummy3;
      } else if (randoper == 1 || randoper == 3){
        down = dummy2;
      }
      while(down == num3 || down == up){
        dummyQtnGeneration();
        if (randoper == 0 || randoper == 2){
          down = dummy3;
        } else if (randoper == 1 || randoper == 3){
          down = dummy2;
        }
      }
    } //End of down #####
    
    
    
    if (answer == 2){  //Start of left #####
      left = num3;
    } else {
      dummyQtnGeneration();
      if (randoper == 0 || randoper == 2){
        left = dummy3;
      } else if (randoper == 1 || randoper == 3){
        left = dummy2;
      }
      while(left == num3 || left == up || left == down){
        dummyQtnGeneration();
        if (randoper == 0 || randoper == 2){
          left = dummy3;
        } else if (randoper == 1 || randoper == 3){
          left = dummy2;
        }
      }
    } //End of left #####
    
    
    
    if (answer == 3){  //Start of right #####
      right = num3;
    } else {
      dummyQtnGeneration();
      if (randoper == 0 || randoper == 2){
        right = dummy3;
      } else if (randoper == 1 || randoper == 3){
        right = dummy2;
      }
      while(right == num3 || right == up || right == down || right == left){
        dummyQtnGeneration();
        if (randoper == 0 || randoper == 2){
          right = dummy3;
        } else if (randoper == 1 || randoper == 3){
          right = dummy2;
        }
      }
    } //End of right #####
    
    
    
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
      rulesScreen();
    }

    arduboy.display();


}





//Rules screen ############################################################################################

void rulesScreen(){
  while(stayInRulesScreen == 1){
    arduboy.clear();
    arduboy.print("Rules:");
    arduboy.print("\n");
    arduboy.print("1.Press up down left ");
    arduboy.print("\n");
    arduboy.print("  right to answer.");
    arduboy.print("\n");
    arduboy.print("2. 10 questions for");
    arduboy.print("\n");
    arduboy.print("  each level.");
    arduboy.print("\n");
    arduboy.print("3. Score = lv*time");
    arduboy.print("\n");
    arduboy.print("\n");
    arduboy.print(" - Go To Next Page - ");

  
    arduboy.pollButtons();
    if (arduboy.justPressed(UP_BUTTON) == true || arduboy.justPressed(DOWN_BUTTON) == true || arduboy.justPressed(LEFT_BUTTON) == true || arduboy.justPressed(RIGHT_BUTTON) == true || arduboy.justPressed(A_BUTTON) == true || arduboy.justPressed(B_BUTTON) == true) {
      stayInRulesScreen = 0;
      HighestScoreScreen();
    }
  
    arduboy.display();
  }
}








//Highest score screen ############################################################################################


void HighestScoreScreen(){
  while (stayInHighestScore == 1){
    arduboy.clear();
    
    arduboy.print("4.Time reward (min=2)"); 
    arduboy.print("\n");
    arduboy.print("  = 4-(lv-1)*0.25 sec");
    arduboy.print("\n");
    arduboy.print("5.Time penalty"); 
    arduboy.print("\n");
    arduboy.print("  = 2+(lv-1)*0.1 sec");
    arduboy.print("\n");
    arduboy.print("---------------------");
    arduboy.print("\n");
    arduboy.print("    Highest Score:   ");
    arduboy.print("\n");
    
    float HighestScoreHYY = 0.00;
    HighestScoreHYY = EEPROM.get(EEPROM_HIGHESTSCORE, HighestScoreHYY);


    int iForHighScore = String(HighestScoreHYY).length();
    for(iForHighScore;iForHighScore<21;iForHighScore = iForHighScore+2){
      arduboy.print(" ");
    }
  
    arduboy.print(HighestScoreHYY);
    arduboy.print("\n");
    arduboy.print("   -Press Any Key-   ");

  
    arduboy.pollButtons();
    if (arduboy.justPressed(UP_BUTTON) == true || arduboy.justPressed(DOWN_BUTTON) == true || arduboy.justPressed(LEFT_BUTTON) == true || arduboy.justPressed(RIGHT_BUTTON) == true || arduboy.justPressed(A_BUTTON) == true || arduboy.justPressed(B_BUTTON) == true) {
      gameOver = 0;
      stayInHighestScore = 0;
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

timeRewardVar = 2000 - (level-1)* 250;
if(timeRewardVar < 0){
  timeRewardVar = 0;
}
timeReward = 2000 + timeRewardVar;

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
  arduboy.print("\n");
  
  int iForLeft = String(left).length();
  for(iForLeft;iForLeft<3;iForLeft++){
    arduboy.print(" ");
  }
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
    if(score > EEPROM.get(EEPROM_HIGHESTSCORE, HighestScoreHYY)){
      EEPROM.put(EEPROM_HIGHESTSCORE, score);
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
        arduboy.print(" ");
        arduboy.print("GAMEOVER @ Lv.");
        arduboy.print(level);
        arduboy.print(" ");
        arduboy.print("#");
        arduboy.print(qtnNum);
        
        
        
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
        
        float HighestScoreHYY = 0.00;
        HighestScoreHYY = EEPROM.get(EEPROM_HIGHESTSCORE, HighestScoreHYY);
        
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
    stayInRulesScreen = 1;
    stayInHighestScore = 1;
    qtnNum = 1;
    level = 1;
    ansGen = 0;
  }
  arduboy.display();
}
