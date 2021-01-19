#include "LiquidCrystal.h"
#include "clock.h"
#include "time.h"
#include "view.h"
#include "mode.h"

#define PIN_LCD_RS 12
#define PIN_LCD_ENABLE 11
#define PIN_LCD_DATA_1 7
#define PIN_LCD_DATA_2 8
#define PIN_LCD_DATA_3 9
#define PIN_LCD_DATA_4 10

LiquidCrystal lcd(PIN_LCD_RS, PIN_LCD_ENABLE, PIN_LCD_DATA_1, PIN_LCD_DATA_2, PIN_LCD_DATA_3, PIN_LCD_DATA_4);
bool _isEditingTime;
View _activeView;
Mode _activeMode;

void initializeDisplay()
{
  lcd.begin(16, 2);
  lcd.clear();

  _isEditingTime = false;
  _activeView = Main;
  _activeMode = None;
}


void displayMain() {
  Time val = getTime();
  lcd.setCursor(0, 0);
  lcd.print(strcat(strcat(strcat(strcat(strcat(val.hour, ":"), val.minute), " "), val.am_pm), " Alarms:"));
  lcd.setCursor(0, 1);
  lcd.print(strcat(strcat(strcat(strcat(strcat(val.month, "/"), val.day), "/"), val.year),  " 1 2 3 4"));
}


void display()  {
  lcd.clear();
  displayMain();
}
