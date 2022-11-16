##########################
# Name: Ahnaf Abrar Kabir
# Date: February 2020
##########################


#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
#include <EEPROM.h>

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

//COLORS
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

//BUTTONS
#define UP 8
#define DOWN 4
#define LEFT 16
#define RIGHT 2

//CUSTOM DIRECTION CHARACTERS
#define UP_ARROW 0
#define DOWN_ARROW 1
#define RIGHT_ARROW 2
#define LEFT_ARROW 3

//ALL THE STATES FOR VOID LOOP()
#define MAIN_MENU_MODE 50
#define PRACTICE_MODE 51
#define VIEW_LEADERBOARD_MODE 52
#define CAREER_MODE 53

//ALL THE STATES OF PREFERENCE FOR SETTING CUSTOMIZATION IN PRACTISE MODE
#define LENGTH 60
#define DIFFICULTY 61

//USED FOR millis() FUNCTION CALLS
#define ONE_SECOND 1000UL




//CUSTOM CHARACTERS
byte upArrow[8] =
{
  B00100,
  B01110,
  B11111,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100
};


byte downArrow[8] =
{
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B11111,
  B01110,
  B00100
};


byte rightArrow[8]
{
  B00100,
  B00110,
  B11111,
  B10110,
  B10100,
  B10000,
  B10000,
  B10000
};


byte leftArrow[8]
{
  B00100,
  B01100,
  B11111,
  B01101,
  B00101,
  B00001,
  B00001,
  B00001
};

//CUSTOM CHARACTERS FOR MENU AND RESTART SCREEN
byte up_left[8]
{
  B11000,
  B10010,
  B10010,
  B10010,
  B10010,
  B10010,
  B10001,
  B11000,
};

byte up_right[8]
{
  B00011,
  B01001,
  B01001,
  B01001,
  B01001,
  B01001,
  B10001,
  B00011,
};

byte down_left[8]
{
  B11000,
  B10001,
  B10001,
  B10001,
  B10001,
  B10001,
  B10001,
  B11000
};

byte down_right[8]
{
  B00011,
  B11001,
  B00101,
  B00101,
  B00101,
  B00101,
  B11001,
  B00011
};

byte left_left[8]
{
  B11000,
  B10010,
  B10010,
  B10010,
  B10010,
  B10010,
  B10011,
  B11000
};

byte left_right[8]
{
  B00011,
  B00001,
  B00001,
  B00001,
  B00001,
  B00001,
  B11001,
  B00011
};

byte right_left[8] =
{
  B11000,
  B10011,
  B10010,
  B10010,
  B10011,
  B10011,
  B10010,
  B11010
};

byte right_right[8] =
{
  B00011,
  B10001,
  B01001,
  B01001,
  B10001,
  B00001,
  B10001,
  B01011
};

//CUSTOM CHARACTERS FOR MAKING THE INTERFACE FOR USER FRIENDLY
byte right_sign[8] = {
  B01000,
  B01100,
  B01110,
  B01111,
  B01110,
  B01100,
  B01000,
  B00000
};


byte left_sign[8] = {
  B00010,
  B00110,
  B01110,
  B11110,
  B01110,
  B00110,
  B00010,
  B00000
};

byte up_and_down_sign[8] = {
  B00100,
  B01110,
  B11111,
  B00000,
  B00000,
  B11111,
  B01110,
  B00100
};

//CUSTOM CHARACTERS FOR THE GAME OVER DISPLAY
byte skull_top_left[8] =
{
  B00100,
  B01010,
  B01111,
  B01100,
  B01000,
  B11010,
  B10101,
  B10101
};

byte skull_top_right[8] =
{
  B00100,
  B01010,
  B11110,
  B00110,
  B00010,
  B01011,
  B10101,
  B10101
};


byte skull_bottom_left[8] =
{
  B10101,
  B10010,
  B11000,
  B11001,
  B01000,
  B01010,
  B01010,
  B00111
};

byte skull_bottom_right[8] =
{
  B10101,
  B01001,
  B00011,
  B10011,
  B00010,
  B01010,
  B01010,
  B11100
};

//CUSTOM CHRACTER FOR THE LEADERBOARD DISPLAY
byte medal[8] =
{
  B11111,
  B01010,
  B00100,
  B00100,
  B01110,
  B11111,
  B01110,
  B00100
};





/*///////////////////////////////////////////////////////////////////////////////////
                  STRUCTS FOR HIGH SCORE
  ///////////////////////////////////////////////////////////////////////////////////*/

struct HIGHSCORER_DETAILS_EASY
{
  char initials[4];
  uint8_t highscore;
};

struct HIGHSCORER_DETAILS_MEDIUM
{
  char initials[4];
  uint8_t highscore;
};

struct HIGHSCORER_DETAILS_HARD
{
  char initials[4];
  uint8_t highscore;
};

/*///////////////////////////////////////////////////////////////////////////////////
                  GLOBAL VARIABLES
  ///////////////////////////////////////////////////////////////////////////////////*/

uint8_t turn = 4;                               //turn counter
uint8_t currentIndexOfInitials = 0;
uint8_t sequenceLength;
uint8_t buttonState = 0;                        //button state checker
uint8_t arrayForRandomCharacters[16];           //large so that it can store upto 14 characters
uint8_t arrayForInputCharacters[16];                         //large so that it can store upto 14 characters
uint8_t highScoreEasy ;                         //storing current high score for EASY from EEPROM
uint8_t highScoreMedium ;                       //storing current high score for MEDIUM from EEPROM
uint8_t highScoreHard ;                         //storing current high score for HARD from EEPROM
char initialsEasy [4];
char initialsMedium [4];
char initialsHard [4];
uint8_t myScore = (turn - 4);                   //current score of user
uint8_t randomNumber;

//variables to check for button presses
boolean up_was_pressed = false;
boolean down_was_pressed = false;
boolean left_was_pressed = false;
boolean right_was_pressed = false;
boolean select_was_pressed = false;
int proceed = 0;
unsigned long previousTime = 0;
char timeBuffer[5];
int state;
char menu[10][30];                              //for storing the contents of main menu's display
boolean getInitials = false;                    //to check if it is required to call the getInitialsForHighscore() function
char initials[4];
boolean Restart = false;

uint8_t stateOfPreference = LENGTH;
char difficultyLevels [3][7] = {"EASY", "MEDIUM", "HARD"};
char difficultyLevel[7];
uint8_t Length = 4;
uint8_t old_buttons = 0;
char buffer[12];                                // Declaring this here is more efficient on memory
int index = 0;                                  //storing current difficulty level

//variables used for displaying the custom character, skull, in the game over screen
int row = 0;
int column = 0;

//GLOBAL STRCUTS USED FOR READING AND WRITING HIGHSCORE TO AND FROM THE EEPROM
HIGHSCORER_DETAILS_EASY playerEasy;
HIGHSCORER_DETAILS_MEDIUM playerMedium;
HIGHSCORER_DETAILS_HARD playerHard;




/*///////////////////////////////////////////////////////////////////////////////////
                  FUNCTION PROTOTYPES
  ///////////////////////////////////////////////////////////////////////////////////*/
void displayWelcomeScreen();
void displayMainMenuScreen();

void playCareerMode();
void getCustomizationForCareerMode();
void displayCustomizationForCareerMode();
void getInputForCareerMode();
void perFormActionsOnWinningTheGame();
void displayMessageForCompletingGame();


void playPracticeMode();
void getCustomizationForPracticeMode();
void displayCustomizationForPracticeMode();
void getInputForPracticeMode();
void displayFirstInstructionOnLcd();
void displaySecondInstructionOnLcd();


int fail();
void displayGameOver();
void getRestartCommand();


void countDownTimer(int timeCounter);
void writeRandomCharactersToLcd();
void updateScore();


void displayLeaderboard();
void getInitialsForHighscore();
void displayInitialsOnLcd();
void displayKeyboardForEnteringInitials();
void checkForNewHighscore();
void displayNewHighScoreScreen();


void makeCustomDirectionCharacters();
void clearBottomLineOfLcd();
void clearTopLineOfLcd();
void clearArrayForRandomCharacters();
void clearArrayForInputCharacters();
void resetButtons();




void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();

  //UNCOMMENT THIS CODE TO RESET THE HIGHSCORES TO 0
  //Resetting the highscore from the EEPROM
  //  playerEasy.highscore = 0;
  //  EEPROM.put(1, playerEasy);
  //  playerMedium.highscore = 0;
  //  EEPROM.put(10, playerMedium);
  //  playerHard.highscore = 0;
  //  EEPROM.put(20, playerHard);


  //Reading the highscores for Easy, Medium & Hard diffifulty levels from the EEPROM
  //and setting them to global variables
  EEPROM.get(1, playerEasy);
  highScoreEasy = playerEasy.highscore;
  strcpy(initialsEasy, playerEasy.initials);
  playerEasy.initials[3] = '\0';

  EEPROM.get(10, playerMedium);
  highScoreMedium = playerMedium.highscore;
  strcpy(initialsMedium, playerMedium.initials);
  playerMedium.initials[3] = '\0';

  EEPROM.get(20, playerHard);
  highScoreHard = playerHard.highscore;
  strcpy(initialsHard, playerHard.initials);
  playerHard.initials[3] = '\0';

  //Added to generate "more randomness" for the output function
  randomSeed(analogRead(0));
  makeCustomDirectionCharacters();
  displayWelcomeScreen();
  state = MAIN_MENU_MODE;
  delay(100);

}//end of void setup()





////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop()
{
  switch (state)
  {
    case MAIN_MENU_MODE:
      resetButtons();
      turn = 4;
      displayMainMenuScreen();
      break;

    case PRACTICE_MODE:
      stateOfPreference = LENGTH;
      getCustomizationForPracticeMode();
      playPracticeMode();
      break;

    case CAREER_MODE:
      playCareerMode();
      break;

    case VIEW_LEADERBOARD_MODE:
      displayLeaderboard();
      break;
  }
}//end of void loop()
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////




/*////////////////////////////////////////////////////////////////////////////////////////////////////
                    ALL FUNCTIONS
  ////////////////////////////////////////////////////////////////////////////////////////////////////*/
void displayWelcomeScreen()
{
  /*
     This function is called in the void setup() function
  */
  clearTopLineOfLcd();
  clearBottomLineOfLcd();
  lcd.setBacklight(WHITE);
  lcd.setCursor(0, 0);
  lcd.print(" Welcome To The");
  lcd.setCursor(0, 1);
  lcd.print("  Memory Game");
  delay(1500);
}//end of displayWelcomeScreen()


void displayMainMenuScreen()
{
  lcd.clear();
  lcd.setBacklight(YELLOW);

  //CREATING CUSTOM CHARACTERS FOR [U],[L],[D] FOR THE MAIN MENU
  lcd.createChar(0, up_left);
  lcd.createChar(1, up_right);
  lcd.createChar(2, down_left);
  lcd.createChar(3, down_right);
  lcd.createChar(4, left_left);
  lcd.createChar(5, left_right);


  char headerLine[17] = "------MENU------";
  char firstLine[12] = "Career Mode";
  char secondLine[14] = "Practice Mode";
  char thirdLine[12] = "LeaderBoard";

  //menu is a global variable of type char
  strcpy(menu[0], headerLine);
  strcpy(menu[1], firstLine);
  strcpy(menu[2], secondLine);
  strcpy(menu[3], thirdLine);

  lcd.setCursor(0, 0);
  lcd.print(menu[0]);

  //DEFINING VARIABLES
  boolean proceed = false;//used to decide when to break out of the loop. it is changed upon pressing either up, down or left button
  int buttonState;//used for reading button State
  previousTime = millis();//global variable

  while (!proceed)
  {
    for (uint8_t currentIndex = 1  ; currentIndex < 4 ;)
    {
      buttonState = lcd.readButtons();

      if (millis() - previousTime >= ONE_SECOND)//THE DISPLAY ON THE BOTTOM LINE OF LCD CHANGES EVERY SECOND
      {
        if (currentIndex == 1)
        {
          clearBottomLineOfLcd();
          lcd.setCursor(0, 1);
          lcd.write(0);
          lcd.setCursor(1, 1);
          lcd.write(1);
          lcd.setCursor(3, 1);
          lcd.print(menu[1]);
          previousTime = millis();
          currentIndex++;
          continue;
        }

        if (currentIndex == 2)
        {
          clearBottomLineOfLcd();
          lcd.setCursor(0, 1);
          lcd.write(2);
          lcd.setCursor(1, 1);
          lcd.write(3);
          lcd.setCursor(3, 1);
          lcd.print(menu[2]);
          previousTime = millis();
          currentIndex++;
          continue;
        }
        if (currentIndex == 3)
        {
          clearBottomLineOfLcd();
          lcd.setCursor(0, 1);
          lcd.write(4);
          lcd.setCursor(1, 1);
          lcd.write(5);
          lcd.setCursor(3, 1);
          lcd.print(menu[3]);
          previousTime = millis();
          currentIndex++;
          continue;
        }
      }//end of if statement

      ///////////////////////////////////////////////////////////
      //IF DOWN BUTTON IS PRESSED, STATE CHANGES TO PRACTICE MODE
      if (buttonState & BUTTON_DOWN)
      {
        down_was_pressed = true;
      }
      else
      {
        if (down_was_pressed)
        {
          proceed = true;//used to break out of the loop
          state = PRACTICE_MODE;
          down_was_pressed = false;
          break;
        }
        down_was_pressed = false;
      }


      //IF UP BUTTON IS PRESSED, STATE CHANGES TO CAREER MODE
      if (buttonState & BUTTON_UP)
      {
        up_was_pressed = true;
      }
      else
      {
        if (up_was_pressed)
        {
          proceed = true;//used to break out of the loop
          state = CAREER_MODE;
          up_was_pressed = false;
          break;
        }
        up_was_pressed = false;
      }


      //IF LEFT BUTTON IS PRESSED, STATE CHANGES TO LEADERBOARD MODE
      if (buttonState & BUTTON_LEFT)
      {
        left_was_pressed = true;
      }
      else
      {
        if (left_was_pressed)
        {
          proceed = true;//used to break out of the loop
          state = VIEW_LEADERBOARD_MODE;
          left_was_pressed = false;
          break;
        }
        left_was_pressed = false;
      }

    }//end of for loop
  }//end of while loop

}//end of displayMainMenuScreen()

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
//                    FUNCTIONS FOR CAREER MODE                                      //
/////////////////////////////////////////////////////////////////////////////////////////

void playCareerMode()
{
  //RESETTING ALL VARIABLES
  clearArrayForRandomCharacters();
  clearArrayForInputCharacters();
  resetButtons();
  makeCustomDirectionCharacters();
  myScore = 0;
  proceed = 0;
  lcd.setBacklight(TEAL);

  //GETTING THE DIFFICULTY LEVEL
  getCustomizationForCareerMode();

  //SETTING THE STARTING VALUE FOR N BASED ON DIFFICULTY LEVEL
  if (index == 0)//easy
  {
    turn = 2;
  }
  else if (index == 1)//medium
  {
    turn = 3;
  }
  else if (index == 2)//hard
  {
    turn = 4;
  }

  //STARTING THE MAIN GAME
  for (uint8_t z = turn ; z <= turn; z++)
  {
    if ((proceed == 0 ) || (proceed == 1))//THE VALUE OF proceed IS 0 WHEN A NEW GAME IS STARTING AND IT IS 1 WHEN THE GAME IS GOING TO THE NEXT ROUND
    {
      //DISPLAYING QUESTION ON THE BOTTOM LINE OF LCD
      lcd.clear();
      updateScore();
      writeRandomCharactersToLcd();
      countDownTimer(5);
      clearBottomLineOfLcd();

      //GETTING INPUT FROM USER
      getInputForCareerMode();
    }
  }//end of for loop

}//end of playCareerMode()



void getCustomizationForCareerMode()
{
  /*
     THIS FUNCTION IS CALLED IN playCareerMode() FUNCTION.
  */

  //DISPLAYING INSTRUCTIONS ON LCD REGARDING HOW TO START PLAYING AFTER SETTING CUSTOMIZATION PREFERENCES
  lcd.setBacklight(WHITE);
  clearTopLineOfLcd();
  clearBottomLineOfLcd();
  lcd.setCursor(0, 0);
  lcd.print("Press Select To");
  lcd.setCursor(0, 1);
  lcd.print("Proceed");
  delay(1980);

  //RESETTING VARIABLES
  index = 0;//set to EASY
  buttonState = lcd.readButtons();
  proceed = -1;//used to decide when to break out of the loop

  //DEFINING VARIABLE FOR READING BUTTON PRESS
  uint8_t  changes;
  changes = old_buttons & (~buttonState);

  while (proceed != 1)
  {
    lcd.setBacklight(TEAL);
    displayCustomizationForCareerMode();

    //READING STATE OF BUTTON IN EVERY TURN OF THE LOOP
    buttonState = lcd.readButtons();
    changes = old_buttons & (~buttonState);

    //DEFINNING ACTIONS ON PRESSING UP AND DOWN BUTTONS
    if (changes & BUTTON_UP)
    {
      clearTopLineOfLcd();
      if (index == 2)
      {
        index = 0;
      }
      else if (index == 1)
      {
        index = 2;
      }
      else if (index == 0)
      {
        index = 1;
      }
    }
    if (changes & BUTTON_DOWN)
    {
      clearTopLineOfLcd();
      if (index == 2)
      {
        index = 1;
      }
      else if (index == 1)
      {
        index = 0;
      }
      else if (index == 0)
      {
        index = 2;
      }
    }

    //PRESSING SELECT BUTTON BREAKS OUT OF THE LOOP AND REMEMBERS THE VALUE OF GLOBAL VARIABLE "index"
    if (changes & BUTTON_SELECT)
    {
      proceed = 1;
      strcpy(difficultyLevel, difficultyLevels[index]);
    }

    old_buttons = buttonState;
  }//end of while

}//end of getCustomizationForCareerMode()




void displayCustomizationForCareerMode()
{
  //DISPLAYING THE CONTENT ON LCD
  lcd.setCursor(0, 1);
  lcd.print("Difficulty Level");
  lcd.setCursor(strlen(difficultyLevels[index] ), 0);
  lcd.print("           ");
  lcd.setCursor(0, 0);
  lcd.print(difficultyLevels[index]);

  //CREATING AND DISPLAYING THE UP AND DOWN OPTION ON LCD
  lcd.createChar(6, up_and_down_sign);
  lcd.setCursor(strlen(difficultyLevels[index] ) + 1, 0);
  lcd.write(6);

}//end of displayCustomizationForCareerMode()





void getInputForCareerMode()
{
  lcd.setBacklight(WHITE);

  //SETTING DIFFERENT TIME LIMITS DEPENDING ON THE DIFFIULTY LEVEL FOR INPUTTING THE CHARACTERS
  uint8_t timeCounter;
  if (index == 0)//EASY
  {
    timeCounter = 10;
  }
  if (index == 1)//MEDIUM
  {
    timeCounter = 8;
  }
  if (index == 2)//HARD
  {
    timeCounter = 6;
  }

  previousTime = millis();
  for (uint8_t x = 0; x < turn;)
  {

    //DISPLAYING TIMER COUNTDOWN ON TOP RIGHT CORNER OF THE LCD
    if (millis() - previousTime >= ONE_SECOND)
    {
      lcd.setCursor(14, 0);
      sprintf(timeBuffer, "%02d", timeCounter);
      lcd.print(timeBuffer);
      previousTime = millis();

      //CALLING THE fail() FUNCTION  IF THE USER FAILS TO ENTER THE SEQUENCE BEFORE THE TIMER RUNS DOWN TO 0
      if ( (x != turn) && (timeCounter == 0) )
      {
        proceed = fail();
        break;
      }
      timeCounter--;
    }

    //CHECKING FOR BUTTON PRESSES
    uint8_t buttons = lcd.readButtons();
    if (buttons & BUTTON_UP)
    {
      up_was_pressed = true;
    }
    else
    {
      if (up_was_pressed)
      {
        lcd.setCursor(x, 1);
        lcd.write(UP_ARROW);

        arrayForInputCharacters[x] = UP;
        if (arrayForInputCharacters[x] != arrayForRandomCharacters[x])//THIS CODE RUNS IF INCORRECT ANSWER IS INPUTTED
        {
          proceed = fail();//PROCEED BECOMES -1
          break;
        }
        else
        {
          proceed = 1;
        }
        x++;
      }
      up_was_pressed = false;
    }


    if (buttons & BUTTON_DOWN)
    {
      down_was_pressed = true;
    }
    else
    {
      if (down_was_pressed)
      {
        lcd.setCursor(x, 1);
        lcd.write(DOWN_ARROW);

        arrayForInputCharacters[x] = DOWN;
        if (arrayForInputCharacters[x] != arrayForRandomCharacters[x])//THIS CODE RUNS IF INCORRECT ANSWER IS INPUTTED
        {
          proceed = fail();//PROCEED BECOMES -1
          break;
        }
        else
        {
          proceed = 1;
        }
        x++;
      }
      down_was_pressed = false;
    }


    if (buttons & BUTTON_LEFT)
    {
      left_was_pressed = true;
    }
    else
    {
      if (left_was_pressed)
      {
        lcd.setCursor(x, 1);
        lcd.write(LEFT_ARROW);
        arrayForInputCharacters[x] = LEFT;
        if (arrayForInputCharacters[x] != arrayForRandomCharacters[x])//THIS CODE RUNS IF INCORRECT ANSWER IS INPUTTED
        {
          proceed = fail();//PROCEED BECOMES -1
          break;
        }
        else
        {
          proceed = 1;
        }
        x++;
      }
      left_was_pressed = false;
    }


    if (buttons & BUTTON_RIGHT)
    {
      right_was_pressed = true;
    }
    else
    {
      if (right_was_pressed)
      {
        lcd.setCursor(x, 1);
        lcd.write(RIGHT_ARROW);
        arrayForInputCharacters[x] = RIGHT;

        if (arrayForInputCharacters[x] != arrayForRandomCharacters[x])//THIS CODE RUNS IF INCORRECT ANSWER IS INPUTTED
        {
          proceed = fail();//PROCEED BECOMES -1
          break;
        }
        else
        {
          proceed = 1;
        }
        x++;
      }
      right_was_pressed = false;
    }
  }//end of for loop

  //INCREMENTING THE SCORE AND TURN
  myScore++;
  if (turn != 14)
  {
    turn++;
  }
  else
  { //This code is for when the game is completed
    perFormActionsOnWinningTheGame();
  }

  //THIS CODE IS RUN IF THE fail() FUNCTION IS CALLED OR perFormActionsOnWinningTheGame() FUNCTION IS CALLED
  if (proceed == -1)
  {
    if (Restart)//THIS IS SET IN THE getRestartCommand() FUNCTION
    {
      state == CAREER_MODE;
    }
    else
    {
      state = MAIN_MENU_MODE;
    }
  }

  //THIS CODE IS RUN IF THE fail() OR perFormActionsOnWinningTheGame() FUNCTION IS NOT CALLED i.e. A CORRECT ANSWER IS ENTERED
  if (proceed == 1)
  {
    checkForNewHighscore();//CHECKING FOR NEW HIGHSCORE
    //BACKLIGHT FLASHES ONCE TO LET THE USER KNOW A CORRECT ANSWER HAS BEEN ENTERED
    lcd.setBacklight(GREEN);
    delay(150);
    clearBottomLineOfLcd();
    lcd.setBacklight(TEAL);//SETTING BACKLIGHT COLOR BACK TO THE COLOR OF THE CAREER MODE
  }
}//end of getInputForCareerMode()



void perFormActionsOnWinningTheGame()
{
  //DISPLAYING MESSAGE FOR WINNING THE GAME ON LCD
  displayMessageForCompletingGame();

  //GETTING INITIALS FOR HIGHSCORE TO BE WRITTEN TO THE EEPROM
  getInitialsForHighscore();


  //SAVING THE SCORE TO BE WRITTEN TO THE EEPROM BASED ON THE DIFFICULTY LEVEL CURRENTLY BEING PLAYED AT
  //OVERWRITNG THE HIGHSCORE SAVED IN THE getInitialsForHighscore() FUNCTION
  if (index == 0) //EASY
  {
    playerEasy.highscore = myScore;
  }
  else if (index == 1) //MEDIUM
  {
    playerMedium.highscore = myScore;
  }
  else if (index == 2) //HARD
  {
    playerHard.highscore = myScore;
  }


  //WRITTING THE STRUCTS TO THE EEPROM BASED ON THE CURRENT DIFFICULTY LEVEL
  if (index == 0) //EASY
  {
    playerEasy.highscore = myScore;
    EEPROM.put(1, playerEasy);
  }
  else if (index == 1) //MEDIUM
  {
    playerMedium.highscore = myScore;
    EEPROM.put(10, playerMedium);
  }
  else if (index == 2) //HARD
  {
    playerHard.highscore = myScore;
    EEPROM.put(20, playerHard);
  }

  //RESETTING VARIABLES
  proceed = -1;//THIS IS SET TO BE USED IN THE getInputForCareerMode() FUNCTION
  Restart = false;//THIS IS SET TO FALSE SO THE GAME RETURNS TO THE MAIN MENU INSTEAD OF RESTARTING FROM THE getInputForCareerMode() FUNCTION

}//end of  perFormActionsOnWinningTheGame()



void displayMessageForCompletingGame()
{
  clearTopLineOfLcd();
  clearBottomLineOfLcd();

  //FLASHING THE BACKLIGHT OF THE LCD TO DIFFERENT COLORS AND DISPLAYING THE FIRST SCREEN ON LCD
  lcd.setCursor(0, 0);
  lcd.print(" CONGRATULATIONS");
  lcd.setCursor(0, 1);
  lcd.print("    Master!!");
  lcd.setBacklight(GREEN);
  delay(250);
  lcd.setBacklight(VIOLET);
  delay(250);
  lcd.setBacklight(TEAL);
  delay(250);
  lcd.setBacklight(WHITE);
  delay(350);

  //FLASHING THE BACKLIGHT OF THE LCD TO DIFFERENT COLORS AND DISPLAYING THE SECOND SCREEN ON LCD
  clearTopLineOfLcd();
  clearBottomLineOfLcd();
  lcd.setCursor(0, 0);
  lcd.print("Your Brain Is");
  lcd.setCursor(0, 1);
  lcd.print("The Real Deal!!!");
  lcd.setBacklight(GREEN);
  delay(250);
  lcd.setBacklight(YELLOW);
  delay(250);
  lcd.setBacklight(TEAL);
  delay(250);
  lcd.setBacklight(WHITE);
  delay(250);
  lcd.setBacklight(GREEN);
  delay(250);
  lcd.setBacklight(BLUE);
  delay(250);
  lcd.setBacklight(TEAL);
  delay(250);
  lcd.setBacklight(VIOLET);
  delay(250);
}//end of displayMessageForCompletingGame()
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////
//                    FUNCTIONS FOR PRACTICE MODE                                      //
/////////////////////////////////////////////////////////////////////////////////////////


void playPracticeMode()
{

  //RESETTING VARIABLES
  clearArrayForRandomCharacters();
  clearArrayForInputCharacters();
  resetButtons();
  turn = 4;
  myScore = 0;
  proceed = 0;
  makeCustomDirectionCharacters();
  lcd.setBacklight(VIOLET);

  for (uint8_t z = turn ; z <= turn; z++)
  {
    if ((proceed == 0 ) || (proceed == 1))//THE VALUE OF proceed IS 0 WHEN A NEW GAME IS STARTING AND IT IS 1 WHEN THE GAME IS GOING TO THE NEXT ROUND
    {
      lcd.clear();
      turn = sequenceLength ;//SETTING THE INITIAL VALUE OF turn FROM THE getCustomizationForPracticeMode() FUNCTION
      displayFirstInstructionOnLcd();
      lcd.setBacklight(VIOLET);
      writeRandomCharactersToLcd();
      countDownTimer(5);
      clearBottomLineOfLcd();

      displaySecondInstructionOnLcd();
      getInputForPracticeMode();
      break;
    }

  }//end of for loop
}//end of playPracticeMode()





void getCustomizationForPracticeMode()
{
  lcd.createChar(5, up_and_down_sign);
  index = 0;//SETTING THE STARTING VALUE OF DIFFICULTY LEVEL TO EASY
  sequenceLength = 2;//SETTING THE STARTING VALUE OF SEQUENCE LENGTH
  proceed = -1;//THIS VARIABLE IS USED TO BREAK OUT OF THE LOOP
  stateOfPreference = LENGTH;

  //CREATING AND RESETTING VARIABLES TO READ BUTTON PRESS
  uint8_t  changes;
  buttonState = lcd.readButtons();
  changes = old_buttons & (~buttonState);

  //DISPLAYING INFORMATION ON HOW TO PROCEED AFTER SETTING THE PREFERENCES
  lcd.setBacklight(WHITE);
  clearTopLineOfLcd();
  clearBottomLineOfLcd();
  lcd.setCursor(0, 0);
  lcd.print("Press Select To");
  lcd.setCursor(0, 1);
  lcd.print("Proceed");
  delay(2000);
  clearTopLineOfLcd();
  clearBottomLineOfLcd();

  while (proceed != 1)
  {
    lcd.setBacklight(VIOLET);

    //DISPLAYING THE CUSTOMIZATION SCREEN ON THE LCD
    displayCustomizationForPracticeMode();

    //RESETTING THE VARIABLES ON EVERY LOOP
    buttonState = lcd.readButtons();
    changes = old_buttons & (~buttonState);



    switch (stateOfPreference)
    {
      case LENGTH:// VALUE OF sequenceLength VARIES FROM 2 TO 10

        //INCREMENTING THE VALUE OF sequenceLength
        if (changes & BUTTON_UP)
        {
          if (sequenceLength == 10)
          {
            sequenceLength = 2;
          }
          else
          {
            sequenceLength++;
          }
        }

        //DECREMENTING THE VALUE OF sequenceLength
        if (changes & BUTTON_DOWN)
        {

          if (sequenceLength == 2)
          {
            sequenceLength = 10;
          }
          else
          {
            sequenceLength--;
          }
        }

        //CHANGING STATE OF PREFERENCE TO difficultylevel
        if (changes & BUTTON_RIGHT)
        {
          stateOfPreference = DIFFICULTY;
        }

        //REMEMBERING THE PREFERENCES SET AND BREAKAING OUT OF THE LOOP
        if (changes & BUTTON_SELECT)
        {
          proceed = 1;//BREAKS OUT OF THE LOOP
          strcpy(difficultyLevel, difficultyLevels[index]);

        }
        break;

      case DIFFICULTY:

        //INCREMENTING THE VALUE OF DIFFICULLTY
        if (changes & BUTTON_UP)
        {
          clearTopLineOfLcd();
          if (index == 2)
          {
            index = 0;
          }
          else if (index == 1)
          {
            index = 2;
          }
          else if (index == 0)
          {
            index = 1;
          }
        }

        //DECCREMENTING THE VALUE OF DIFFICULLTY
        if (changes & BUTTON_DOWN)
        {
          clearTopLineOfLcd();
          if (index == 2)
          {
            index = 1;
          }
          else if (index == 1)
          {
            index = 0;
          }
          else if (index == 0)
          {
            index = 2;
          }
        }

        //CHANGING STATE OF PREFERENCE TO sequenceLength
        if (changes & BUTTON_LEFT)
        {
          stateOfPreference = LENGTH;
        }

        //REMEMBERING THE PREFERENCES SET AND BREAKAING OUT OF THE LOOP
        if (changes & BUTTON_SELECT)
        {
          proceed = 1;//BREAKS OUT OF THE LOOP
          strcpy(difficultyLevel, difficultyLevels[index]);
        }
        break;
    }
    old_buttons = buttonState;
  }//end of while

}//end of getCustomizationForPracticeMode()




void displayCustomizationForPracticeMode()
{
  if (stateOfPreference == DIFFICULTY)
  {
    lcd.setCursor(0, 1);
    lcd.print("Difficulty Level");

    //DISPLAYING THE OPTION OF GOING LEFT TO CHANGE FOCUS TO LENGTH
    //DISPLAYING ON TOP RIGHT CORNER OF LCD
    lcd.createChar(6, left_sign);
    lcd.setCursor(15, 0);
    lcd.write(6);

    //DISPLAYING THE CURRENT DIFFICULTY LEVEL
    lcd.setCursor(0, 0);
    lcd.print(difficultyLevels[index]);

    lcd.setCursor(strlen(difficultyLevels[index] ), 0);
    lcd.print("           ");
  }
  else if (stateOfPreference == LENGTH)
  {
    lcd.setCursor(0, 1);
    lcd.print("Length             ");

    //DISPLAYING THE OPTION OF GOING RIGHT TO CHANGE FOCUS TO DIFFICULTY
    //DISPLAYING ON TOP RIGHT CORNER OF LCD
    lcd.createChar(7, right_sign);
    lcd.setCursor(15, 0);
    lcd.write(7);

    //DISPALING THE CURRENT sequenceLength ON LCD
    lcd.setCursor(0, 0);
    sprintf(buffer, "%02d", sequenceLength);
    lcd.print(buffer);

    //DISPLAYING THE CUSTOM CHARACTER TO LET THE USER KNOW THERE IS AN OPTION TO INCREASE AND DECREASE THE sequenceLength
    lcd.setCursor(2, 0);
    lcd.write(5);//up and down sign

    lcd.setCursor(3, 0);
    lcd.print("            ");
  }

}//end of displayCustomizationForPracticeMode()



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void getInputForPracticeMode()
{

  lcd.setBacklight(VIOLET);
  resetButtons();
  uint8_t timeCounter;

  if (strcmp(difficultyLevel, difficultyLevels[0]) == 0) //EASY
  {
    timeCounter = 8;
  }
  if (strcmp(difficultyLevel, difficultyLevels[1]) == 0) //MEDIUM
  {
    timeCounter = 6;
  }
  if (strcmp(difficultyLevel, difficultyLevels[2]) == 0) //HARD
  {
    timeCounter = 4;
  }


  previousTime = millis();

  for (uint8_t x = 0; x < turn;)
  {
    //DISPLAYING TIMER COUNTDOWN ON TOP RIGHT CORNER OF THE LCD
    if (millis() - previousTime >= ONE_SECOND)
    {
      lcd.setCursor(14, 0);
      sprintf(timeBuffer, "%02d", timeCounter);
      lcd.print(timeBuffer);
      previousTime = millis();

      //CALLING THE fail() FUNCTION  IF THE USER FAILS TO ENTER THE SEQUENCE BEFORE THE TIMER RUNS DOWN TO 0
      if ( (x != turn) && (timeCounter == 0) )
      {
        proceed = fail();
        break;
      }
      timeCounter--;
    }

    //CHECKING FOR BUTTON PRESSES
    uint8_t buttons = lcd.readButtons();
    if (buttons & BUTTON_UP)
    {
      up_was_pressed = true;
    }
    else
    {
      if (up_was_pressed)
      {
        lcd.setCursor(x, 1);
        lcd.write(UP_ARROW);

        arrayForInputCharacters[x] = UP;
        if (arrayForInputCharacters[x] != arrayForRandomCharacters[x])//THIS CODE RUNS IF INCORRECT ANSWER IS INPUTTED
        {
          proceed = fail();
          break;
        }
        else
        {
          proceed = 1;
        }
        x++;
      }
      up_was_pressed = false;
    }


    if (buttons & BUTTON_DOWN)
    {
      down_was_pressed = true;
    }
    else
    {
      if (down_was_pressed)
      {
        lcd.setCursor(x, 1);
        lcd.write(DOWN_ARROW);
        arrayForInputCharacters[x] = DOWN;

        if (arrayForInputCharacters[x] != arrayForRandomCharacters[x])//THIS CODE RUNS IF INCORRECT ANSWER IS INPUTTED
        {
          proceed = fail();//PROCEED BECOMES -1
          break;
        }
        else
        {
          proceed = 1;
        }
        x++;
      }
      down_was_pressed = false;
    }


    if (buttons & BUTTON_LEFT)
    {
      left_was_pressed = true;
    }
    else
    {
      if (left_was_pressed)
      {
        lcd.setCursor(x, 1);
        lcd.write(LEFT_ARROW);
        arrayForInputCharacters[x] = LEFT;
        if (arrayForInputCharacters[x] != arrayForRandomCharacters[x])//THIS CODE RUNS IF INCORRECT ANSWER IS INPUTTED
        {
          proceed = fail();//PROCEED BECOMES -1
          break;
        }
        else
        {
          proceed = 1;
        }
        x++;
      }
      left_was_pressed = false;
    }


    if (buttons & BUTTON_RIGHT)
    {
      right_was_pressed = true;
    }
    else
    {
      if (right_was_pressed)
      {
        lcd.setCursor(x, 1);
        lcd.write(RIGHT_ARROW);
        arrayForInputCharacters[x] = RIGHT;

        if (arrayForInputCharacters[x] != arrayForRandomCharacters[x])//THIS CODE RUNS IF INCORRECT ANSWER IS INPUTTED
        {
          proceed = fail();//PROCEED BECOMES -1
          break;
        }
        else
        {
          proceed = 1;
        }
        x++;
      }
      right_was_pressed = false;
    }
  }

  //THIS CODE IS RUN IF THE fail() FUNCTION IS CALLED
  if (proceed == -1)
  {
    if (Restart)//THIS VALUE IS SET IN THE getRestartCommand() function
    {
      state == PRACTICE_MODE;
    }
    else
    {
      state = MAIN_MENU_MODE;
    }
  }

  //THIS CODE IS RUN IF THE fail() FUNCTION IS NOT CALLED
  if (proceed == 1)
  {
    //FLASHING THE BACKLIGHT ONCE TO LET THE USER KNOW A CORRECT ANSWER HAS BEEN INPUTTED
    lcd.setBacklight(GREEN);
    delay(150);

    clearBottomLineOfLcd();
    lcd.setBacklight(VIOLET);
    state = MAIN_MENU_MODE;//RETURN TO THE MAIN MENU
  }
}//end of getInputForPracticeMode()



void displayFirstInstructionOnLcd()
{
  clearBottomLineOfLcd();
  clearTopLineOfLcd();
  lcd.setBacklight(WHITE);
  lcd.setCursor(0, 0);
  lcd.print("Remember The ");
  lcd.setCursor(0, 1);
  lcd.print("Sequence........");
  delay(1390);
  clearBottomLineOfLcd();
  clearTopLineOfLcd();
}//end of displayFirstInstructionOnLcd()


void displaySecondInstructionOnLcd()
{
  clearBottomLineOfLcd();
  clearTopLineOfLcd();
  lcd.setBacklight(WHITE);
  lcd.setCursor(0, 0);
  lcd.print("Enter Sequence");
  lcd.setCursor(0, 1);
  lcd.print("From Your Memory");
  delay(1390);
  clearBottomLineOfLcd();
  clearTopLineOfLcd();
}//end of displaySecondInstructionOnLcd()
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
//              FUNCTIONS FOR ENTERING THE WRONG SEQUENCE                              //
/////////////////////////////////////////////////////////////////////////////////////////

int fail()//FUNCTION USED IF THE USER FAILS TO MATCH THE SEQUENCE
{
  //DISAPLYING GAME OVER SCREEN
  lcd.clear();
  lcd.setBacklight(RED);
  displayGameOver();
  delay(1500);
  lcd.clear();

  //DISPLAYING THE FINAL SCORE BEFORE RESETTING IT
  //ONLY APPLICABLE WHEN THE fail() FUNCTION IS CALLED FROM CAREER_MODE
  if (state == CAREER_MODE)
  {
    lcd.setCursor(0, 0);
    lcd.print("Your Score: ");
    lcd.setCursor(12, 0);
    lcd.print(myScore);
    delay(2000);

    //SAVING THE HIGHSCORE IN THE STRUCT TO BE SAVED TO THE EEPROM
    //IT IS ONLY SAVED LATER ON IF THE VALUE OF myScore GREATER THAN THE HIGHSCORE OF RESPECTIVE DIFFICULY LEVEL
    if (index == 0)//EASY
    {
      playerEasy.highscore = myScore;//to be written to the EEPROM
    }
    if (index == 1)//MEDIUM
    {
      playerMedium.highscore = myScore;//to be written to the EEPROM
    }
    if (index == 2)//HARD
    {
      playerHard.highscore = myScore;//to be written to the EEPROM
    }
  }

  //RESETTING turn AND myScore
  turn = 4;
  myScore = (turn - 4);

  //DISAPLYING GAME OVER SCREEN AGAIN
  clearBottomLineOfLcd();
  lcd.clear();
  displayGameOver();
  delay(1300);

  //GETTING THE INITIALS FOR SAVING HIGHSCORE TO EEPROM ONLY IN CAREER MODE IF THE CONDITION MEETS
  if (state == CAREER_MODE)
  {
    if (getInitials)//THIS VALUE IS SET IN THE checkForNewHighscore() FUNCTION
    {
      getInitialsForHighscore();
    }
  }

  //GET USER INPUT ON WHETHER TO RESTART OR NOT
  getRestartCommand();

  return -1;//THIS VALUE IS SAVED TO THE VARIABLE proceed WHENEVER THE fail() FUNCTION IS CALLED

}//end of fail();




void displayGameOver()
{
  lcd.setCursor(0, 0);
  lcd.print("GAME");

  lcd.createChar(0, skull_top_left);
  lcd.createChar(1, skull_top_right);
  lcd.createChar(2, skull_bottom_left);
  lcd.createChar(3, skull_bottom_right);

  for (uint8_t row = 0; row < 2; row++)
  {
    for (uint8_t column = 5; column < 10; column++)
    {
      if ( ( (column == 5) && (row == 0)  )  || ( (column == 8) && (row == 0) ) )
      {
        lcd.setCursor(column, row);
        lcd.write(0);
      }
      if ( (  (column == 6) && (row == 0) )  || ( (column == 9) && (row == 0) ) )
      {
        lcd.setCursor(column, row);
        lcd.write(1);
      }
      if ( ( (column == 5) && (row == 1)  )  || ( (column == 8) && (row == 1) ) )
      {
        lcd.setCursor(column, row);
        lcd.write(2);
      }
      if ( (  (column == 6) && (row == 1) )  || ( (column == 9) && (row == 1) ) )
      {
        lcd.setCursor(column, row);
        lcd.write(3);
      }
    }//END OF INNER FOR LOOP
  }//END OF OUTER FOR LOOP

  lcd.setCursor(11, 0);
  lcd.print("OVER");
}//end of displayGameOver();



void getRestartCommand()
{
  //RESETTING VARIABLES
  right_was_pressed = false;
  left_was_pressed = false;
  proceed = 0;//USED FOR BREAKING OUT OF THE WHILE LOOP

  //CREATING CUSTOM CHARACTERS [L] AND [R]
  lcd.createChar(0, left_left);
  lcd.createChar(1, left_right);
  lcd.createChar(2, right_left);
  lcd.createChar(3, right_right);

  lcd.setBacklight(BLUE);

  clearTopLineOfLcd();
  clearBottomLineOfLcd();


  //DISPLAYING INSTRUCTIONS ON LCD
  lcd.setCursor(4, 0);
  lcd.print("Restart?");

  lcd.setCursor(0, 1);
  lcd.write(0);
  lcd.setCursor(1, 1);
  lcd.write(1);
  lcd.setCursor(3, 1);
  lcd.print("NO");

  lcd.setCursor(10, 1);
  lcd.write(2);
  lcd.setCursor(11, 1);
  lcd.write(3);
  lcd.setCursor(13, 1);
  lcd.print("YES");

  while (proceed != 1)
  {
    //WAITING FOR BUTTON PRESS
    buttonState = lcd.readButtons();

    //PREFORMING ACTIONS ON PRESSING THE RIGHT BUTTON
    if (buttonState & BUTTON_RIGHT)
    {
      right_was_pressed = true;
    }
    else
    {
      if (right_was_pressed)
      {
        Restart = true;
        proceed = 1;//USED TO BREAK OUT OF THE LOOP
      }
      right_was_pressed = false;
    }

    //PREFORMING ACTIONS ON PRESSING THE LEFT BUTTON
    if (buttonState & BUTTON_LEFT)
    {
      left_was_pressed = true;
    }
    else
    {
      if (left_was_pressed)
      {
        Restart = false;
        proceed = 1;//USED TO BREAK OUT OF THE LOOP
      }
      left_was_pressed = false;
    }

  }//end of while loop
}//end of getRestartCommand()




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void countDownTimer(int timeCounter)
{
  /*
     THIS FUNCTION IS CALLED WHEN THE QUESTION HAS BEEN PRINTED ON THE SCREEN
     tHE QUESTION STAYS PRINTED ON THE SCREEN UNTIL THE timeCounter RUNS TO 0
  */
  while (timeCounter >= 0)
  {
    if (millis() - previousTime >= ONE_SECOND)
    {
      lcd.setCursor(14, 0);
      sprintf(timeBuffer, "%02d", timeCounter);//timeBuffer IS A GLOBAL VARIABLE

      lcd.print(timeBuffer);
      previousTime = millis();
      timeCounter--;
    }
  }
}//end of countDownTimer()



void writeRandomCharactersToLcd()
{
  makeCustomDirectionCharacters();

  uint8_t currentIndexOfRandomArray = 0; //this variable is used to decide how many characters will be put into arrayForRandomCharacters
  for (uint8_t i = 0; ; i++)
  {
    //THIS CODE RUNS IF THE GAME IS BEING PLAYED IN PRACTICE_MODE
    if (state == PRACTICE_MODE)
    {
      randomNumber = random(1, 17);
      if ((randomNumber == LEFT) || (randomNumber == RIGHT) || (randomNumber == DOWN) || (randomNumber == UP))
      {
        arrayForRandomCharacters[currentIndexOfRandomArray] = randomNumber;
        currentIndexOfRandomArray++;
      }

      if (currentIndexOfRandomArray == turn)//STOPS PUTTING NEW VALUES TO THE RANDOM ARRAY
      {
        break;
      }
    }//end of practice mode

    //THIS CODE RUNS IF THE GAME IS BEING PLAYED IN CAREER_MODE
    if (state == CAREER_MODE)
    {
      
      //THIS CODE RUNS IF THE GAME IS BEING PLAYED IN CAREER_MODE WITH DIFFICULTY LEVEL SET AT EASY
      if (index == 0)////////////////////////EASY
      {
        randomNumber = random(1, 17);
        if ((randomNumber == LEFT) || (randomNumber == RIGHT) )
        {
          arrayForRandomCharacters[currentIndexOfRandomArray] = randomNumber;
          currentIndexOfRandomArray++;
        }

        if (currentIndexOfRandomArray == turn)//STOPS PUTTING NEW VALUES TO THE RANDOM ARRAY
        {
          break;
        }
      }
      
      //THIS CODE RUNS IF THE GAME IS BEING PLAYED IN CAREER_MODE WITH DIFFICULTY LEVEL SET AT MEDIUM
      if (index == 1)////////////////////////MEDIUM
      {
        randomNumber = random(1, 17);
        if ((randomNumber == LEFT) || (randomNumber == RIGHT) ||  (randomNumber == UP))
        {
          arrayForRandomCharacters[currentIndexOfRandomArray] = randomNumber;
          currentIndexOfRandomArray++;
        }

        if (currentIndexOfRandomArray == turn)//STOPS PUTTING NEW VALUES TO THE RANDOM ARRAY
        {
          break;
        }
      }
      
      //THIS CODE RUNS IF THE GAME IS BEING PLAYED IN CAREER_MODE WITH DIFFICULTY LEVEL SET AT HARD
      if (index == 2)////////////////////////HARD
      {
        randomNumber = random(1, 17);
        if ((randomNumber == LEFT) || (randomNumber == RIGHT) || (randomNumber == DOWN) || (randomNumber == UP))
        {
          arrayForRandomCharacters[currentIndexOfRandomArray] = randomNumber;
          currentIndexOfRandomArray++;
        }

        if (currentIndexOfRandomArray == turn)//STOPS PUTTING NEW VALUES TO THE RANDOM ARRAY
        {
          break;
        }
      }
    }//END OF career mode
  }//END OF FOR LOOP


  //WRITING THE CHARACTERS OF THE RANDOM ARAAY TO THE LCD SCREEN
  for (uint8_t i = 0; i < turn; i++)
  {
    if (arrayForRandomCharacters[i] == UP)          //up arrow
    {
      lcd.setCursor(i, 1);
      lcd.write(0);
      delay(500);
    }
    if (arrayForRandomCharacters[i] == DOWN)          //down arrow
    {
      lcd.setCursor(i, 1);
      lcd.write(1);
      delay(500);

    }
    if (arrayForRandomCharacters[i] == RIGHT)          //Right arrow
    {
      lcd.setCursor(i, 1);
      lcd.write(2);
      delay(500);

    }
    if (arrayForRandomCharacters[i] == LEFT)          //Left arrow
    {
      lcd.setCursor(i, 1);
      lcd.write(3);
      delay(500);
    }
  }
}//end of writeRandomCharactersToLcd()




void updateScore()
{
  lcd.setCursor(0, 0);
  lcd.print("Score: ");
  lcd.setCursor(7, 0);
  lcd.print(myScore);
}//end of updateScore()


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
//                    FUNCTIONS RELATED TO HIGHSCORE                                   //
/////////////////////////////////////////////////////////////////////////////////////////


void displayLeaderboard()
{
  //CREATING CUSTOM CHARACTER TO BE PLACED IN THE TOP LINE OF THE LCD
  lcd.createChar(4, medal);

  //Instructions to go back to menu
  lcd.setBacklight(WHITE);
  clearTopLineOfLcd();
  clearBottomLineOfLcd();
  lcd.setCursor(0, 0);
  lcd.print("Press SELECT To");
  lcd.setCursor(0, 1);
  lcd.print("Go Back To Menu");
  delay(2500);
  clearTopLineOfLcd();
  clearBottomLineOfLcd();

  lcd.setBacklight(GREEN);
  //RESETTING VARIABLES
  index = 0;
  proceed = -1;
  resetButtons();
  clearTopLineOfLcd();
  clearBottomLineOfLcd();

  //GETTING THE STRUCTS DIRECTLY FROM THE EEPROM TO INCREASE ACCURACY OF RESULT
  EEPROM.get(1, playerEasy);
  EEPROM.get(10, playerMedium);
  EEPROM.get(20, playerHard);
  playerEasy.initials[3] = '\0';
  playerMedium.initials[3] = '\0';
  playerHard.initials[3] = '\0';
  previousTime = millis();

  while (proceed != 1)
  {
    //DISPLAYING CONTENT ON THE TOP LINE OF THE LCD
    lcd.setCursor(0, 0);
    lcd.write(4);
    lcd.setCursor(2, 0);
    lcd.print("LEADERBOARD");
    lcd.setCursor(15, 0);
    lcd.write(4);

    //DISPLAYING HIGHSCORE FOR DIFFICULTY LEVEL EASY
    if (index == 0)
    {
      lcd.setCursor(0, 1);
      lcd.print("Easy-");
      lcd.setCursor(5, 1);
      lcd.print(" ");
      lcd.setCursor(6, 1);
      lcd.print(playerEasy.initials);
      //lcd.print(initialsEasy);
      lcd.setCursor(9, 1);
      lcd.print(" ");
      lcd.setCursor(10, 1);
      lcd.print(playerEasy.highscore);
      lcd.setCursor(12, 1);
      lcd.print("            ");
    }

    //DISPLAYING HIGHSCORE FOR DIFFICULTY LEVEL MEDIUM
    if (index == 1)
    {
      HIGHSCORER_DETAILS_MEDIUM check1;
      lcd.setCursor(0, 1);
      lcd.print("Medium-");
      lcd.setCursor(7, 1);
      lcd.print(" ");
      lcd.setCursor(8, 1);
      lcd.print(playerMedium.initials);
      //lcd.print(initialsMedium);
      lcd.setCursor(11, 1);
      lcd.print(" ");
      lcd.setCursor(12, 1);
      lcd.print(playerMedium.highscore);
      lcd.setCursor(14, 1);
      lcd.print("   ");
    }

    //DISPLAYING HIGHSCORE FOR DIFFICULTY LEVEL HARD
    if (index == 2)
    {
      HIGHSCORER_DETAILS_HARD check2;
      //EEPROM.get(20, playerHard);
      lcd.setCursor(0, 1);
      lcd.print("Hard-");
      lcd.setCursor(5, 1);
      lcd.print(" ");
      lcd.setCursor(6, 1);
      lcd.print(playerHard.initials);
      //lcd.print(initialsHard);
      lcd.setCursor(9, 1);
      lcd.print(" ");
      lcd.setCursor(10, 1);
      lcd.print(playerHard.highscore);
      lcd.setCursor(12, 1);
      lcd.print("           ");
    }

    //UPDATING AND DISPLAYING HIGHSCORE OF THE NEXT DIFFICULTY LEVEL EVERY 2 SECONDS
    if (millis() - previousTime >= (ONE_SECOND * 2))
    {
      clearBottomLineOfLcd();
      //UPDATING THE INDEX EVERY 2 SECONDS
      if (index == 0)
      {
        index = 1;
      }
      else if (index == 1)
      {
        index = 2;
      }
      else if (index == 2)
      {
        index = 0;
      }
      previousTime = millis();//RESETTING THE previousTime VARIBALE
    }

    //ACTIONS OF PRESSING BUTTONS
    buttonState = lcd.readButtons();

    //ACTIONS ON PRESSING SELECT BUTTON
    if (buttonState & BUTTON_SELECT)
    {
      select_was_pressed = true;
    }
    else
    {
      if (select_was_pressed)
      {
        state = MAIN_MENU_MODE;
        proceed = 1;//THIS IS SET TO BREAK OUT OF THE LOOP
        select_was_pressed = false;
      }
      select_was_pressed = false;
    }
  }//end of while loop

}//end of displayLeaderboard()



void getInitialsForHighscore()
{
  resetButtons();
  lcd.setBacklight(WHITE);

  clearTopLineOfLcd();
  clearBottomLineOfLcd();

  //DISPLAYING INSTRUCTIONS ON THE LCD
  lcd.setCursor(0, 0);
  lcd.print("Enter 3 Initials");
  lcd.setCursor(0, 1);
  lcd.print("Of Your Name");
  delay(4000);

  //DISPLAYING KEYBOARD ON THE LCD
  clearTopLineOfLcd();
  clearBottomLineOfLcd();
  lcd.setCursor(0, 0);
  lcd.print("ABCDEFGHIJKLMNOP");
  lcd.setCursor(0, 1);
  lcd.print("QRSTUVWXYZ");

  row = 0;
  column = 0;
  lcd.setCursor(column, row);
  currentIndexOfInitials = 0;//USED TO BREAK OUT OF THE WHILE LOOP

  while (currentIndexOfInitials < 3)
  {
    buttonState = lcd.readButtons();

    //ACTIONS ON PRESSING UP BUTTON
    if (buttonState & BUTTON_UP)
    {
      up_was_pressed = true;
    }
    else
    {
      if (up_was_pressed)
      {
        if (row == 0)
        {
          row = 1;
          lcd.setCursor(column, row);

          if ((column == 15) || (column == 14) || (column == 13) || (column == 12) || (column == 11) || (column == 10) )
          {
            column = 9;
            lcd.setCursor(column, row);
          }
        }
        else if (row == 1)
        {
          row = 0;
          lcd.setCursor(column, row);
        }
      }
      up_was_pressed = false;
    }

    //ACTIONS ON PRESSING DOWN BUTTON
    if (buttonState & BUTTON_DOWN)
    {
      down_was_pressed = true;
    }
    else
    {
      if (down_was_pressed)
      {
        if (row == 0)
        {
          row = 1;
          lcd.setCursor(column, row);
          if ((column == 15) || (column == 14) || (column == 13) || (column == 12) || (column == 11) || (column == 10) )
          {
            column = 9;
            lcd.setCursor(column, row);
          }
        }
        else if (row == 1)
        {
          row = 0;
          lcd.setCursor(column, row);
        }
      }
      down_was_pressed = false;
    }

    //ACTIONS ON PRESSING LEFT BUTTON
    if (buttonState & BUTTON_LEFT)
    {
      left_was_pressed = true;
    }
    else
    {
      if (left_was_pressed)
      {
        if (row == 0)
        {
          if (column == 0)
          {
            column = 15;
            lcd.setCursor(column, row);
          }
          else
          {
            column--;
            lcd.setCursor(column, row);
          }
        }
        else if (row == 1)
        {
          if (column == 0)
          {
            column = 9;
            lcd.setCursor(column, row);
          }
          else
          {
            column--;
            lcd.setCursor(column, row);
          }
        }
      }
      left_was_pressed = false;
    }

    //ACTIONS ON PRESSING RIGHT BUTTON
    if (buttonState & BUTTON_RIGHT)
    {
      right_was_pressed = true;
    }
    else
    {
      if (right_was_pressed)
      {
        if (row == 0)
        {
          if (column == 15)
          {
            column = 0;
            lcd.setCursor(column, row);
          }
          else
          {
            column++;
            lcd.setCursor(column, row);
          }
        }
        else if (row == 1)
        {
          if (column == 9)
          {
            column = 0;
            lcd.setCursor(column, row);
          }
          else
          {
            column++;
            lcd.setCursor(column, row);
          }
        }
      }
      right_was_pressed = false;
    }

    //ACTIONS ON PRESSING SELECT BUTTON
    if (buttonState & BUTTON_SELECT)
    {
      select_was_pressed = true;
    }
    else
    {
      if (select_was_pressed)
      {
        displayKeyboardForEnteringInitials();//DISPLAYING THE TYPED INITIALS ON THE BOTTOM RIGHT CORNER OF THE LCD
      }
      select_was_pressed = false;
    }
    lcd.blink();
  }//END OF WHILE LOOP

  lcd.noBlink();
  initials[3] = (char)0;

  //COPYING INITIALS TO THE STRUCT AND PUTTING THEM INTO THE EEPROM
  if (index == 0)//DIFFICULTY LEVEL: EASY
  {
    strcpy(playerEasy.initials, initials);
    EEPROM.put(1, playerEasy);
  }
  else if (index == 1)//DIFFICULTY LEVEL: MEDIUM
  {
    strcpy(playerMedium.initials, initials);
    EEPROM.put(10, playerMedium);
  }
  else if (index == 2)//DIFFICULTY LEVEL: HARD
  {
    strcpy(playerHard.initials, initials);
    EEPROM.put(20, playerHard);
  }

  playerEasy.initials[3] = '\0'; playerMedium.initials[3] = '\0'; playerHard.initials[3] = '\0';

  //DISPLAYING THE HIGHSCORE AND INITIALS THAT ARE SAVED TO THE EEPROM ON THE LCD
  clearTopLineOfLcd();
  clearBottomLineOfLcd();
  lcd.setBacklight(GREEN);
  lcd.setCursor(0, 0);
  lcd.print("New High Score ");
  lcd.setCursor(0, 1);
  lcd.print("Saved:");

  if (index == 0)//DIFFICULTY LEVEL: EASY
  {
    lcd.setCursor(7, 1);
    lcd.print(playerEasy.initials);

    lcd.setCursor(11, 1);
    lcd.print(playerEasy.highscore);
  }

  else if (index == 1)//DIFFICULTY LEVEL: MEDIUM
  {
    lcd.setCursor(7, 1);
    lcd.print(playerMedium.initials);
    lcd.setCursor(11, 1);
    lcd.print(playerMedium.highscore);
  }
  else if (index == 2)//DIFFICULTY LEVEL: HARD
  {
    lcd.setCursor(7, 1);
    lcd.print(playerHard.initials);
    lcd.setCursor(11, 1);
    lcd.print(playerHard.highscore);
  }
  delay(3000);//KEEP THE DISPLAY ON SCREEN FOR 3 SECONDS

  getInitials = false;

}//end of getInitialsForHighscore()



void displayInitialsOnLcd()
{
  //DISPLAY THE BRACKETS ON THE BOTTOM RIGHT CORNER OF THE LCD
  lcd.setCursor(11, 1);
  lcd.print("[");
  lcd.setCursor(15, 1);
  lcd.print("]");

  //PRINTING THE 3 INITIALS INSIDE THE BRACKETS ON THE BOTTOM RIGHT CORNER OF THE LCD
  if (currentIndexOfInitials == 0)
  {
    lcd.setCursor(12, 1);
    lcd.print(initials[0]);
    lcd.setCursor(column, row);
  }
  if (currentIndexOfInitials == 1)
  {
    lcd.setCursor(13, 1);
    lcd.print(initials[1]);
    lcd.setCursor(column, row);
  }
  if (currentIndexOfInitials == 2)
  {
    lcd.setCursor(14, 1);
    lcd.print(initials[2]);
    lcd.setCursor(column, row);
    delay(500);
  }
}//end of displayInitialsOnLcd()



void displayKeyboardForEnteringInitials()
{
  switch (row)
  {
    case 0:
      switch (column)
      {
        case 0:
          initials[currentIndexOfInitials] = 'A';
          displayInitialsOnLcd();
          currentIndexOfInitials++;
          break;
        case 1:
          initials[currentIndexOfInitials] = 'B';
          displayInitialsOnLcd();
          currentIndexOfInitials++;
          break;
        case 2:
          initials[currentIndexOfInitials] = 'C';
          displayInitialsOnLcd();
          currentIndexOfInitials++;
          break;
        case 3:
          initials[currentIndexOfInitials] = 'D';
          displayInitialsOnLcd();
          currentIndexOfInitials++;
          break;
        case 4:
          initials[currentIndexOfInitials] = 'E';
          displayInitialsOnLcd();
          currentIndexOfInitials++;
          break;
        case 5:
          initials[currentIndexOfInitials] = 'F';
          displayInitialsOnLcd();
          currentIndexOfInitials++;
          break;
        case 6:
          initials[currentIndexOfInitials] = 'G';
          displayInitialsOnLcd();
          currentIndexOfInitials++;
          break;
        case 7:
          initials[currentIndexOfInitials] = 'H';
          displayInitialsOnLcd();
          currentIndexOfInitials++;
          break;
        case 8:
          initials[currentIndexOfInitials] = 'I';
          displayInitialsOnLcd();
          currentIndexOfInitials++;
          break;
        case 9:
          initials[currentIndexOfInitials] = 'J';
          displayInitialsOnLcd();
          currentIndexOfInitials++;
          break;
        case 10:
          initials[currentIndexOfInitials] = 'K';
          currentIndexOfInitials++;
          break;
        case 11:
          initials[currentIndexOfInitials] = 'L';
          displayInitialsOnLcd();
          currentIndexOfInitials++;
          break;
        case 12:
          initials[currentIndexOfInitials] = 'M';
          displayInitialsOnLcd();
          currentIndexOfInitials++;
          break;
        case 13:
          initials[currentIndexOfInitials] = 'N';
          displayInitialsOnLcd();
          currentIndexOfInitials++;
          break;
        case 14:
          initials[currentIndexOfInitials] = 'O';
          displayInitialsOnLcd();
          currentIndexOfInitials++;
          break;
        case 15:
          initials[currentIndexOfInitials] = 'P';
          displayInitialsOnLcd();
          currentIndexOfInitials++;
          break;

      }
      break;

    case 1:
      switch (column)
      {
        case 0:
          initials[currentIndexOfInitials] = 'Q';
          displayInitialsOnLcd();
          currentIndexOfInitials++;
          break;
        case 1:
          initials[currentIndexOfInitials] = 'R';
          displayInitialsOnLcd();
          currentIndexOfInitials++;
          break;
        case 2:
          initials[currentIndexOfInitials] = 'S';
          displayInitialsOnLcd();
          currentIndexOfInitials++;
          break;
        case 3:
          initials[currentIndexOfInitials] = 'T';
          displayInitialsOnLcd();
          currentIndexOfInitials++;
          break;
        case 4:
          initials[currentIndexOfInitials] = 'U';
          displayInitialsOnLcd();
          currentIndexOfInitials++;
          break;
        case 5:
          initials[currentIndexOfInitials] = 'V';
          displayInitialsOnLcd();
          currentIndexOfInitials++;
          break;
        case 6:
          initials[currentIndexOfInitials] = 'W';
          displayInitialsOnLcd();
          currentIndexOfInitials++;
          break;
        case 7:
          initials[currentIndexOfInitials] = 'X';
          displayInitialsOnLcd();
          currentIndexOfInitials++;
          break;
        case 8:
          initials[currentIndexOfInitials] = 'Y';
          displayInitialsOnLcd();
          currentIndexOfInitials++;
          break;
        case 9:
          initials[currentIndexOfInitials] = 'Z';
          displayInitialsOnLcd();
          currentIndexOfInitials++;
          break;
      }
      break;
  }
}//end of displayKeyboardForEnteringInitials()



void checkForNewHighscore()
{
  if (index == 0)//CHECKING HIGHSCORE FOR DIFFICULTY LEVEL: EASY
  {
    if (myScore > highScoreEasy)
    {
      highScoreEasy = myScore;
      getInitials = true;
      displayNewHighScoreScreen();
    }
    else
    {
      getInitials = false;
    }
  }

  else if (index == 1)//CHECKING HIGHSCORE FOR DIFFICULTY LEVEL: MEDIUM
  {
    if (myScore > highScoreMedium)
    {
      highScoreMedium = myScore;
      getInitials = true;
      displayNewHighScoreScreen();
    }
    else
    {
      getInitials = false;
    }
  }

  else if (index == 2)//CHECKING HIGHSCORE FOR DIFFICULTY LEVEL: HARD
  {
    if (myScore > highScoreHard)
    {
      highScoreHard = myScore;
      getInitials = true;
      displayNewHighScoreScreen();
    }
    else
    {
      getInitials = false;
    }
  }
}//end of  checkForNewHighscore()





void displayNewHighScoreScreen()
{
  clearTopLineOfLcd();
  clearBottomLineOfLcd();

  //DISPLAYING THE MESSAGE ON THE LCD
  lcd.setCursor(0, 0);
  lcd.print("CONGRATULATIONS");
  lcd.setCursor(0, 1);
  lcd.print("NEW HIGHSCORE!!!");

  //FLASHING THE BACKLIGHT 3 TIMES WITH DIFFERENT COLORS
  lcd.setBacklight(GREEN);
  delay(220);
  lcd.setBacklight(VIOLET);
  delay(220);
  lcd.setBacklight(WHITE);
  delay(220);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////
//                             HELPING FUNCTIONS                                       //
/////////////////////////////////////////////////////////////////////////////////////////
void makeCustomDirectionCharacters()
{
  lcd.createChar(0, upArrow);
  lcd.createChar(1, downArrow);
  lcd.createChar(2, rightArrow);
  lcd.createChar(3, leftArrow);
}


void clearBottomLineOfLcd()
{
  lcd.setCursor(0, 1);
  lcd.print("                  ");
}//end of clearBottomLineOfLcd()


void clearTopLineOfLcd()
{
  lcd.setCursor(0, 0);
  lcd.print("                  "); 
}//end of clearTopLineOfLcd()





void clearArrayForRandomCharacters()
{
  for (uint8_t x = 0; x < sizeof(arrayForRandomCharacters) / sizeof(arrayForRandomCharacters[0]); x++)
  {
    arrayForRandomCharacters[x] = (char)0;
  }
}//end of clearaArrayForRandomCharacters()



void clearArrayForInputCharacters()
{
  for (uint8_t x = 0; x < sizeof(arrayForInputCharacters) / sizeof(arrayForInputCharacters[0]); x++)
  {
    arrayForInputCharacters[x] = (char)0;
  }
}//end of clearArrayForInputCharacters()



void resetButtons()
{
  up_was_pressed = false;
  down_was_pressed = false;
  left_was_pressed = false;
  right_was_pressed = false;
  select_was_pressed = false;
}//end of resetButtons()
