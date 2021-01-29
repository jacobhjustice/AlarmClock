#include "LiquidCrystal.h"
#include "clock.h"
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

char* getAlarmNumberText(int alarmNum)
{
  char buffer[1];
  if(_alarms[alarmNum - 1].isEnabled)
  {
    itoa(alarmNum, buffer, 10);
    return buffer;
  }
  
  return getWhitespace(1);
}

char* getAlarmOnOffText(bool isEnabled)
{
  if(isEnabled)
  {
    return "ON ";
  }
  else
  {
    return "OFF";
  }
}

char* getCharIfEnabled(char text, bool isEnabled)
{
  if(isEnabled)
  {
    return text;
  }
  return " ";
}

char* getMainText(ClockValue time, bool isTopRow) 
{
  char text[16];
  if(isTopRow)
  {
    strcat(text, getFormattedHour(time.hour));
    strcat(text, ":");
    strcat(text, getFormattedMinute(time.minute));
    strcat(text, " ");
    strcat(text, getFormattedAMPM(time.isPM));
    strcat(text, " Alarms:"); // Double checck EXE for null char overflow
  }
  else
  {
    strcat(text, getFormattedMonth(time.month));
    strcat(text, "/");
    strcat(text, getFormattedDay(time.day));
    strcat(text, "/");
    strcat(text, getFormattedYear(time.year));
    strcat(text, " ");
    strcat(text, getAlarmNumberText(1));
    strcat(text, " ");
    strcat(text, getAlarmNumberText(2));
    strcat(text, " ");
    strcat(text, getAlarmNumberText(3));
    strcat(text, " ");
    strcat(text, getAlarmNumberText(4));
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
    strcat(text, getAlarmOnOffText(a.isEnabled));
    strcat(text, "    ");
  }
  else
  {
    strcat(text, getFormattedHour(a.hour));
    strcat(text, ":");
    strcat(text, getFormattedMinute(a.minute));
    strcat(text, " ");
    strcat(text, getFormattedAMPM(a.isPM));
    strcat(text, " ");
    strcat(text, getCharIfEnabled("S", a.isSetSunday));
    strcat(text, getCharIfEnabled("M", a.isSetMonday));
    strcat(text, getCharIfEnabled("T", a.isSetTuesday));
    strcat(text, getCharIfEnabled("W", a.isSetWednesday));
    strcat(text, getCharIfEnabled("T", a.isSetThursday));
    strcat(text, getCharIfEnabled("F", a.isSetFriday));
    strcat(text, getCharIfEnabled("S", a.isSetSaturday));
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
