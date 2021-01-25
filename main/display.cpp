#include "LiquidCrystal.h"
#include "alarm.h"
#include "clock.h"
#include "clock_value.h"
#include "view.h"
#include "mode.h"
#include "memory_access.h"

#define PIN_LCD_RS 12
#define PIN_LCD_ENABLE 11
#define PIN_LCD_DATA_1 7
#define PIN_LCD_DATA_2 8
#define PIN_LCD_DATA_3 9
#define PIN_LCD_DATA_4 10

LiquidCrystal lcd(PIN_LCD_RS, PIN_LCD_ENABLE, PIN_LCD_DATA_1, PIN_LCD_DATA_2, PIN_LCD_DATA_3, PIN_LCD_DATA_4);
bool _isEditingTime;
Alarm* _alarms;
View _activeView;
Mode _activeMode;

// Internal Functions
char * getText(char* text, bool isEditMode, ClockValue time)
{
  if(!isEditMode)
  {
    return text;
  }
  
  int secs = atoi(time.second);
  if(secs % 2 == 0)
  {
    return text;
  }

  return " ";
}

char* getAlarmNumberText(int alarmNum, bool isEditMode, ClockValue time)
{
  char buffer[1];
  if(_alarms[alarmNum - 1].isEnabled)
  {
    itoa(alarmNum, buffer, 10);
    return getText(buffer, isEditMode, time);
  }
  
  return " ";
}
void getMainText(ClockValue time, bool isTopRow) 
{
  char text[16];
  if(isTopRow)
  {
    strcat(text, getText(time.hour, _activeMode == BlinkHours, time));
    strcat(text, ":");
    strcat(text, getText(time.minute, _activeMode == BlinkMinutes, time));
    strcat(text, " ");
    strcat(text, getText(time.am_pm, _activeMode == BlinkAMPM, time));
    strcat(text, " Alarms:"); // Double checck EXE for null char overflow
  }
  else
  {
    strcat(text, getText(time.month, _activeMode == BlinkMonth, time));
    strcat(text, "/");
    strcat(text, getText(time.day, _activeMode == BlinkDay, time));
    strcat(text, "/");
    strcat(text, getText(time.year, _activeMode == BlinkYear, time));
    strcat(text, " ");
    strcat(text, getAlarmNumberText(1, _activeMode == BlinkAlarm1, time));
    strcat(text, " ");
    strcat(text, getAlarmNumberText(2, _activeMode == BlinkAlarm2, time));
    strcat(text, " ");
    strcat(text, getAlarmNumberText(3, _activeMode == BlinkAlarm3, time));
    strcat(text, " ");
    strcat(text, getAlarmNumberText(4, _activeMode == BlinkAlarm4, time));
  }
}

char* getRow(ClockValue time, bool isTopRow) 
{
  getMainText(time, isTopRow);
}

void displayMain() {
  ClockValue val = getTime();
  lcd.setCursor(0, 0);
  //lcd.print(strcat
  //lcd.print(strcat(strcat(strcat(strcat(strcat(val.hour, ":"), val.minute), " "), val.am_pm), " Alarms:"));
  lcd.setCursor(0, 1);
  lcd.print(strcat(strcat(strcat(strcat(strcat(val.month, "/"), val.day), "/"), val.year),  " 1 2 3 4"));
}

// External Functions

void initializeDisplay()
{
  lcd.begin(16, 2);
  lcd.clear();

  _isEditingTime = false;
  _activeView = Main;
  _activeMode = None;
  _alarms = getAlarmsFromMemory();
}

void display()  
{
  ClockValue val = getTime();
  lcd.setCursor(0,0);
  lcd.print(getRow(val, true));
  lcd.setCursor(0,1);
  lcd.print(getRow(val, false));
  displayMain();
}
