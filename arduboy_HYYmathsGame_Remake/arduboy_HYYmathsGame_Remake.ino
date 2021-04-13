/*
 * Maths Calculation Game
 * Made by HYY - February 26th, 2019
 * Remade on April 12th, 2021
 * 
 * GitHub Page:
 * https://github.com/barryyik/Arduboy-Calculation-Game
*/

#include <Arduboy2.h>
#include <timer.h>

#define EEPROM_HASRECORD   EEPROM_STORAGE_SPACE_START
#define EEPROM_HIGHESTSCORE   EEPROM_STORAGE_SPACE_START + 4

Arduboy2 arduboy;

// variables for game play
bool needInitializeGame;
bool needGenerateNewQuestion;
float HighestScoreHYY;

// variables for time
unsigned long referenceTimeInMillis;
unsigned long currentTimeInMillis;
unsigned long maxTimeDifferenceInMillis; // Constant, value = 10000
float timeLeft;

// variables for level & score
float score;
int level;

// variables for setting questions
int questionNumber;
int answerPosition;
int dummyVariable1;
int dummyVariable2;
int dummyVariable3;
int randomNumber;
String questionString;

// variables for answer options
int intForUp;
int intForDown;
int intForLeft;
int intForRight;

void setup() {
    arduboy.begin();
    arduboy.clear();

    needInitializeGame = true;

    // Constants
    maxTimeDifferenceInMillis = 10000;
}

void loop() {
    if (needInitializeGame) initializeGame();

    // Trigger question and answer generation
    if (needGenerateNewQuestion) generateNewQuestionAndAnswers();

    /* Create game interface */
    // UI - Time
    currentTimeInMillis = millis();
    unsigned long timePassedInMillis = currentTimeInMillis - referenceTimeInMillis;
    float timePassedIn10Millis = timePassedInMillis / 10;
    timeLeft = 10.00 - ((timePassedIn10Millis > 1000) ? 1000 : timePassedIn10Millis) /100;
    String timeLeftString = String(timeLeft);
    if (timeLeft < 10.00) timeLeftString = " " + timeLeftString;
    for (int i = timeLeftString.length(); i < 5; i++) timeLeftString += "";

    arduboy.clear();
    arduboy.print("Time:   " + timeLeftString + " / 10.00\n");

    // UI - Level & Question Number & Score
    arduboy.print("Lv." + String(level));
    for (int i = String(score).length() + String(level).length(); i < 11; i++) arduboy.print(" ");
    arduboy.print("Score: " + String(score) + "\n");

    // UI - Question & Answers
    arduboy.print("\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\n");

    arduboy.print("    " + String(intForUp));
    for (int i = String(intForUp).length(); i < 6; i++) { arduboy.print(" "); }
    arduboy.print("/ Lv." + String(level) + " #" + String(questionNumber) + "\n");

    arduboy.print("    |     \\\n");

    for (int i = String(intForLeft).length(); i < 3; i++) { arduboy.print(" "); }
    arduboy.print(String(intForLeft) + "-+-" + String(intForRight));
    for (int i = String(intForRight).length(); i < 4; i++){ arduboy.print(" "); }
    arduboy.print("/  " + String(questionString) + "\n");

    arduboy.print("    |     \\\n");
    
    arduboy.print("    " + String(intForDown));
    for (int i = String(intForDown).length(); i < 6; i++) { arduboy.print(" "); }
    arduboy.print("/  = ?");


    // Answer Determination
    arduboy.pollButtons();
    if (arduboy.justPressed(UP_BUTTON) || arduboy.justPressed(DOWN_BUTTON) || arduboy.justPressed(LEFT_BUTTON) || arduboy.justPressed(RIGHT_BUTTON) ) {
        if ( (arduboy.justPressed(UP_BUTTON) && answerPosition == 0) 
            || (arduboy.justPressed(DOWN_BUTTON) && answerPosition == 1) 
            || (arduboy.justPressed(LEFT_BUTTON) && answerPosition == 2)
            || (arduboy.justPressed(RIGHT_BUTTON) && answerPosition == 3)){
        actionWhenCorrectButtonPressed();
        }
        else {
            actionWhenWrongButtonPressed();
        }
    }
    
    // Game Over Case
    if (timeLeft <= 0) {
        if (score > EEPROM.get(EEPROM_HIGHESTSCORE, HighestScoreHYY)) EEPROM.put(EEPROM_HIGHESTSCORE, score);
        HighestScoreHYY = EEPROM.get(EEPROM_HIGHESTSCORE, HighestScoreHYY);

        // 1st delay
        arduboy.clear();
        arduboy.display();
        delay(1000);
        
        // 2nd delay
        arduboy.print("\n GAMEOVER @ Lv. " + String(level) + "#" + String(questionNumber));
        arduboy.display();
        delay(1000);

        // 3rd delay
        arduboy.print("\n\n");
        arduboy.print("Score: " + String(score));
        arduboy.display();
        delay(1000);
        
        // 4th delay
        arduboy.print("\n\n");
        arduboy.print("Highest: " + String(HighestScoreHYY));
        arduboy.display();
        delay(1000);
        
        arduboy.print("\n\n");
        arduboy.print("   -Press Any Key-   ");
        arduboy.display();

        freezeScreen();
        needInitializeGame = true;
    }

    arduboy.display();
}

/* Other Functions Goes Here */

void actionWhenCorrectButtonPressed() {
    unsigned long timeRewardInMillis = 4000 - (level - 1) * 250;
    referenceTimeInMillis += timeRewardInMillis;
    if (referenceTimeInMillis > currentTimeInMillis) referenceTimeInMillis = currentTimeInMillis;

    // Next Question
    score = score + (level * timeLeft);
    questionNumber += 1;
    if (questionNumber > 10) {
        questionNumber = 1;
        level += 1;
    }
    needGenerateNewQuestion = true;
}

void actionWhenWrongButtonPressed() {
    unsigned long timePenaltyInMillis = 2000 + (level - 1) * 100;
    referenceTimeInMillis -= timePenaltyInMillis;
    if (referenceTimeInMillis <= currentTimeInMillis - maxTimeDifferenceInMillis) referenceTimeInMillis = currentTimeInMillis - maxTimeDifferenceInMillis;
}

void freezeScreen() {
    bool isScreenFreezed = true;
    while (isScreenFreezed == true) {
        arduboy.pollButtons();
        if ( arduboy.justPressed(UP_BUTTON)
            || arduboy.justPressed(DOWN_BUTTON)
            || arduboy.justPressed(LEFT_BUTTON)
            || arduboy.justPressed(RIGHT_BUTTON)
            || arduboy.justPressed(A_BUTTON)
            || arduboy.justPressed(B_BUTTON) ) {
            isScreenFreezed = false;
        }
    }
}

void generateRandomNumber(int maxInt) {
    arduboy.initRandomSeed();
    randomNumber = random(0, maxInt);
}

void initializeGame() {
    needInitializeGame = false;

    // Get Highest Score (and set to 0.00 if there isn't any)
    float hasSetHighestScore = EEPROM.get(EEPROM_HASRECORD, hasSetHighestScore);
    if (hasSetHighestScore != 20210412.1958) {
        EEPROM.put(EEPROM_HASRECORD, 20210412.1958);
        EEPROM.put(EEPROM_HIGHESTSCORE, 0.00);
    }
    HighestScoreHYY = EEPROM.get(EEPROM_HIGHESTSCORE, HighestScoreHYY);

    showGameStartScreen();

    // Reset variables
    referenceTimeInMillis = millis();
    level = 1;
    questionNumber = 1;
    score = 0.00;
    needGenerateNewQuestion = true;
}

void showGameStartScreen() {
    // 1st Page
    arduboy.clear();
    arduboy.print("*********************\n");
    arduboy.print("*********************\n");
    arduboy.print("**                 **\n");
    arduboy.print("**  HYY MATH GAME  **\n");
    arduboy.print("** -Press Any Key- **\n");
    arduboy.print("**                 **\n");
    arduboy.print("*********************\n");
    arduboy.print("*********************");
    arduboy.display();
    freezeScreen();

    // 2nd Page
    arduboy.clear();
    arduboy.print(" ~~~~~~ Rules ~~~~~~ \n");
    arduboy.print("1. Press up down left\n");
    arduboy.print("   right to answer.  \n");
    arduboy.print("2. 10 questions for  \n");
    arduboy.print("   each level.       \n");
    arduboy.print("3. Score = lv * time \n");
    arduboy.print("                     \n");
    arduboy.print(" - Go To Next Page - ");
    arduboy.display();
    freezeScreen();

    // 3rd Page
    arduboy.clear();
    arduboy.print("4.Time reward (min=2)\n");
    arduboy.print("  = 4-(lv-1)*0.25 sec\n");
    arduboy.print("5.Time penalty       \n");
    arduboy.print("  = 2+(lv-1)*0.1 sec \n");
    arduboy.print("---------------------\n");
    arduboy.print("    Highest Score:   \n");
    for (int i = String(HighestScoreHYY).length(); i < 21; i += 2) arduboy.print(" ");
    arduboy.print(String(HighestScoreHYY) + "\n");
    arduboy.print("   -Press Any Key-   ");
    arduboy.display();
    freezeScreen();
}

void generateNewDummyVariables(int operatorInt) {
    generateRandomNumber((level + 9));
    dummyVariable1 = randomNumber;
    generateRandomNumber((level + 9));
    dummyVariable2 = randomNumber;

    // Get rid of "divided by zero" error
    if (operatorInt == 3) {
        while (dummyVariable1 == 0) {
            generateRandomNumber((level + 9));
            dummyVariable1 = randomNumber;
        }
    }

    if (operatorInt <= 1)
        dummyVariable3 = dummyVariable1 + dummyVariable2;
    else
        dummyVariable3 = dummyVariable1 * dummyVariable2;
}

void generateNewQuestionAndAnswers() {
    needGenerateNewQuestion = false;

    int firstNumber;
    int secondNumber;
    int thirdNumber;
    int answerPositionArray[] = {0,1,2,3};

    // shuffle the array
    for (int i = 0; i < 4; i++) {
        generateRandomNumber(4);
        int n = randomNumber;
        int temp = answerPositionArray[n];
        answerPositionArray[n] = answerPositionArray[i];
        answerPositionArray[i] = temp;
    }
    answerPosition = answerPositionArray[0];

    String allOperators = "+-*/";
    generateRandomNumber(4);
    String operatorString = String(allOperators[randomNumber]);
    int operatorInt = allOperators.indexOf(operatorString);

    // Generate variables
    generateNewDummyVariables(operatorInt);

    // Generate the question
    if (operatorInt % 2 == 0) {
        firstNumber = dummyVariable1;
        secondNumber = dummyVariable2;
        thirdNumber = dummyVariable3;
    }
    else {
        firstNumber = dummyVariable3;
        secondNumber = dummyVariable1;
        thirdNumber = dummyVariable2;
    }
    questionString = String(firstNumber) + " " + operatorString + " " + String(secondNumber);

    // Generate the choices
    int otherChoice1;
    int otherChoice2;
    int otherChoice3;
    bool needCheckDuplicatedChoices = true;
    while (needCheckDuplicatedChoices) {
        if (operatorInt % 2 == 0) {
            generateNewDummyVariables(operatorInt);
            otherChoice1 =  dummyVariable3;
            generateNewDummyVariables(operatorInt);
            otherChoice2 =  dummyVariable3;
            generateNewDummyVariables(operatorInt);
            otherChoice3 =  dummyVariable3;
        }
        else {
            generateNewDummyVariables(operatorInt);
            otherChoice1 =  dummyVariable2;
            generateNewDummyVariables(operatorInt);
            otherChoice2 =  dummyVariable2;
            generateNewDummyVariables(operatorInt);
            otherChoice3 =  dummyVariable2;
        }
        // Check if choices are unique
        if (thirdNumber != otherChoice1
            && thirdNumber != otherChoice2
            && thirdNumber != otherChoice3
            && otherChoice1 != otherChoice2
            && otherChoice1 != otherChoice3
            && otherChoice2 != otherChoice3)
            needCheckDuplicatedChoices = false;
    }
    
    int choicesArray[4];
    choicesArray[answerPositionArray[0]] = thirdNumber;
    choicesArray[answerPositionArray[1]] = otherChoice1;
    choicesArray[answerPositionArray[2]] = otherChoice2;
    choicesArray[answerPositionArray[3]] = otherChoice3;

    intForUp = choicesArray[0];
    intForDown = choicesArray[1];
    intForLeft = choicesArray[2];
    intForRight = choicesArray[3];
}
