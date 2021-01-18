#include "LiquidCrystal.h"
#include "clock.h"
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

void InitializeDisplay()
{
  lcd.begin(16, 2);
  lcd.clear();

  _isEditingTime = false;
  _activeView = Main;
  _activeMode = None;
}

void display()  {

}
