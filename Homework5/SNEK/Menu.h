// Menu

#ifndef SNEK_MENU_H
#define SNEK_MENU_H

#include "Constants.h"
#include "Matrix.h"
#include "Lcd.h"
#include "Memory.h"

const String menuText = "MENU";

const int menuItemCount = 5;
const String menuItemText[] = {"Start Game", "Highscores", "Settings", "About", "How To Play"};
const int menuItemState[] = {STATE_GAME, STATE_MENU_HIGHSCORE, STATE_MENU_SETTINGS, STATE_MENU_ABOUT, STATE_MENU_HOW_TO_PLAY};

const String greetingsText = "Welcome to SNEK!"; 
const long greetingsTime = 3000;
volatile long greetingsStart = 0;

const int aboutTextCount = 3;
const String aboutText[] = {"SNEK", "by Alex Enache", "github Alex18mai"};

const int howToPlayTextCount = 4;
const String howToPlayText[] = {"> u are SNEK", "> u eat fruit", "> u grow and", "change direction"};

volatile bool menuChanged = true;

volatile int currentItem;
volatile int currentHighscore;
volatile int currentAbout;
volatile int currentHowToPlay;

const int settingsItemCount = 5;
const String settingsItemText[] = {"Change Name", "Difficulty", "LCD Bright", "Matrix Bright", "Sound"};
const int settingsItemState[] = {STATE_SETTINGS_CHANGE_NAME, STATE_SETTINGS_DIFFICULTY, STATE_SETTINGS_LCD_BRIGHT, STATE_SETTINGS_MATRIX_BRIGHT, STATE_SETTINGS_SOUND};

volatile int currentSettings;

volatile int currentNameLetter;
volatile bool lockedNameLetter;

void menuSetup() {
  currentItem = 0;
  currentHighscore = 0;
  currentAbout = 0;
  currentHowToPlay = 0;  
  currentSettings = 0;
  currentNameLetter = 0;
  lockedNameLetter = false;
}

void displayGreetings() {
  if (greetingsStart == 0) {
    greetingsStart = millis();
    displayMatrixImage(matrixImageSmile);
    lcd.clear();
    lcd.setCursor(FIRST_ROW);
    lcd.print(greetingsText);
  }
}

void putArrows(int currentPos, int minPos, int maxPos) {
  if (currentPos > minPos) {  
      lcd.setCursor(ARROW_UP_POSITION);
      lcd.write(LCD_ARROW_UP);
    } 

    if (currentPos < maxPos) {
      lcd.setCursor(ARROW_DOWN_POSITION);
      lcd.write(LCD_ARROW_DOWN);            
    }  
}

void displayMenu() {
  if (menuChanged) {
    menuChanged = false;
    displayMatrixImage(matrixImageMenu);

    lcd.clear();
    lcd.setCursor(FIRST_ROW);
    lcd.print(menuText);  

    lcd.setCursor(SECOND_ROW);
    lcd.print(menuItemText[currentItem]);

    putArrows(currentItem, 0, menuItemCount - 1);
  }
}

void displayHighscore() {
  if (menuChanged) {
    menuChanged = false;
    displayMatrixImage(matrixImageTop);

    lcd.clear();
    lcd.setCursor(FIRST_ROW);
    lcd.print(menuItemText[currentItem]);

    lcd.setCursor(SECOND_ROW);    
    for (int i=0; i<nameSize; i++) {
      lcd.print(highscoreNames[currentHighscore][i]);
    }

    lcd.setCursor(SCORE_POSITION);
    lcd.print(highscorePoints[currentHighscore]);
  
    putArrows(currentHighscore, 0, highscoreCount - 1); 
  }
}

void displaySettings() {
  if (menuChanged) {
    menuChanged = false;
    displayMatrixImage(matrixImageSettings);

    lcd.clear();
    lcd.setCursor(FIRST_ROW);
    lcd.print(menuItemText[currentItem]);

    lcd.setCursor(SECOND_ROW);
    lcd.print(settingsItemText[currentSettings]);

    putArrows(currentSettings, 0, settingsItemCount - 1);
  }
}

void displayAbout() {
  if (menuChanged) {
    menuChanged = false;
    displayMatrixImage(matrixImageAbout);

    lcd.clear();
    lcd.setCursor(FIRST_ROW);
    lcd.print(menuItemText[currentItem]);

    lcd.setCursor(SECOND_ROW);
    lcd.print(aboutText[currentAbout]);

    putArrows(currentAbout, 0, aboutTextCount - 1);  
  }
}

void displayHowToPlay() {
  if (menuChanged) {
    menuChanged = false;
    displayMatrixImage(matrixImageHowToPlay);

    lcd.clear();
    lcd.setCursor(FIRST_ROW);
    lcd.print(menuItemText[currentItem]);

    lcd.setCursor(SECOND_ROW);
    lcd.print(howToPlayText[currentHowToPlay]);

    putArrows(currentHowToPlay, 0, howToPlayTextCount - 1);  
  }
}

void displaySettingsChangeName() {
  if (menuChanged) {
    menuChanged = false;

    lcd.clear();

    lcd.setCursor(FIRST_ROW);    
    for (int i=0; i<nameSize; i++) {
      lcd.print(currentName[i]);
    }

    lcd.setCursor(currentNameLetter, 1);
    if (!lockedNameLetter) {
      lcd.print('^');
    }    
    else{
      lcd.write(LCD_ARROW_UP); 
      putArrows(currentName[currentNameLetter], 'A', 'Z');       
    }

    saveSettings();
  }
}

void displaySettingsDifficulty() {
  if (menuChanged) {
    menuChanged = false;

    lcd.clear();
    lcd.setCursor(FIRST_ROW);
    lcd.print(settingsItemText[currentSettings]);

    lcd.setCursor(SECOND_ROW);
    lcd.print(difficulty);
    
    saveSettings();

    putArrows(difficulty, MIN_DIFFICULTY, MAX_DIFFICULTY);  
  }
}

void displaySettingsLcdBright() {
  if (menuChanged) {
    menuChanged = false;

    lcd.clear();
    lcd.setCursor(FIRST_ROW);
    lcd.print(settingsItemText[currentSettings]);

    lcd.setCursor(SECOND_ROW);
    lcd.print(lcdBrightness);

    analogWrite(lcdBacklight, lcdBrightness * LCD_BRIGHT_FACTOR);  
    saveSettings();

    putArrows(lcdBrightness, MIN_LCD_BRIGHT, MAX_LCD_BRIGHT); 
  }
}

void displaySettingsMatrixBright() {
  if (menuChanged) {
    menuChanged = false;

    lcd.clear();
    lcd.setCursor(FIRST_ROW);
    lcd.print(settingsItemText[currentSettings]);

    lcd.setCursor(SECOND_ROW);
    lcd.print(matrixBrightness);

    lc.setIntensity(0, matrixBrightness);
    saveSettings();

    putArrows(matrixBrightness, MIN_MATRIX_BRIGHT, MAX_MATRIX_BRIGHT); 
  }
}

void displaySettingsSound() {
  if (menuChanged) {
    menuChanged = false;

    lcd.clear();
    lcd.setCursor(FIRST_ROW);
    lcd.print(settingsItemText[currentSettings]);

    lcd.setCursor(SECOND_ROW);
    lcd.print(soundSetting);

    saveSettings();
    
    putArrows(soundSetting, NO_SOUND, WITH_SOUND); 
  }
}

#endif