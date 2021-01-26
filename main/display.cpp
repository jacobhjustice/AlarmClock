#include "LiquidCrystal.h"
#include "alarm.h"
#include "clock.h"
#include "clock_value.h"
#include "view.h"
#include "mode.h"
#include "memory_access.h"
#include "string.h"

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
char* getWhitespace(int length)
{
    char buffer [length];
  for(int i = 0; i < length; i++)
  {
    strcat(buffer, " ");
  }
  return buffer;
}

char* getText(char* text, bool isEditMode, ClockValue time)
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

  return getWhitespace(strlen(text));
}

char* getAlarmNumberText(int alarmNum, bool isEditMode, ClockValue time)
{
  char buffer[1];
  if(_alarms[alarmNum - 1].isEnabled)
  {
    itoa(alarmNum, buffer, 10);
    return getText(buffer, isEditMode, time);
  }
  
  return getWhitespace(strlen(buffer));
}

char* getTextIfVisibleOrEditing(char text, bool isVisible, bool isEditMode, ClockValue time)
{
  if(isEditMode)
  {
    return getText(text, isEditMode, time);
  }
  if(isVisible)
  {
    return text;
  }
  return getWhitespace(strlen(text));
}

char* getAlarmOnOffText(bool isEnabled, bool isEditMode, ClockValue time)
{
  if(isEnabled)
  {
    return strcat(getText("ON", isEditMode, time), " ");
  }
  else
  {
    return getText("OFF", isEditMode, time);
  }
}

char* getMainText(ClockValue time, bool isTopRow) 
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

  return text;
}

char* getEditAlarmText(int alarmNum, ClockValue time, bool isTopRow) 
{
  char text[16];
  Alarm a = _alarms[alarmNum - 1];
  if(isTopRow)
  {
    strcat(text, "ALARM ");
    char buffer[1];
    itoa(alarmNum, buffer, 10);
    strcat(text, buffer);
    strcat(text, ": ");
    strcat(text, "");
  }
  else
  {
    
  }
  return text;
}

char* getRow(ClockValue time, bool isTopRow) 
{
  int alarmNum = 0;
  switch(_activeView)
  {
    case Main:
      return getMainText(time, isTopRow);
    case EditAlarm1:
      alarmNum = 1;
      break;
    case EditAlarm2:
      alarmNum = 2;
      break;
    case EditAlarm3:
      alarmNum = 3;
      break;
    case EditAlarm4:
      alarmNum = 4;
      break;
  }
  return getEditAlarmText(alarmNum, time, isTopRow);
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
}
