// Lcd

#ifndef SNEK_LCD_H
#define SNEK_LCD_H

#include <LiquidCrystal.h>

#define FIRST_ROW 0,0
#define SECOND_ROW 0,1

#define LCD_ARROW_UP int(0)
#define LCD_ARROW_DOWN int(1)

const byte rs = 9;
const byte en = 8;
const byte d4 = 7;
const byte d5 = 13;
const byte d6 = 5;
const byte d7 = 4;
const byte lcdBacklight = 6;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

byte lcdMaskArrowUp[] = {
  B00000,
  B00100,
  B01110,
  B11111,
  B00000,
  B00000,
  B00000,
  B00000
};

byte lcdMaskArrowDown[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B01110,
  B00100,
  B00000
};


void lcdSetup(){
  analogWrite(lcdBacklight, lcdBrightness * LCD_BRIGHT_FACTOR);  
  lcd.begin(16, 2);
  lcd.clear();

  lcd.createChar(LCD_ARROW_UP, lcdMaskArrowUp);
  lcd.createChar(LCD_ARROW_DOWN, lcdMaskArrowDown);
}


#endif