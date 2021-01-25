/* This file is responsible for interacting with EEPROM memory
 * Usage exists to store/retrieve Alarms 1, 2, 3, and 4 in case of power loss.
 * Please see example below depicting how data is stored below:
 * 
 * Location | Content/Value
 *    1     |    A1 Hrs
 *    2     |    A1 Mins
 *    3     |    A1 PM (Note - 1 indicates time set is in the PM)
 *    4     |    A1 Enable Flags (Note - Unique binary value indicates which days are set)
 *    5     |    A2 Hrs
 *    ...
 *    16    |    A4 Enabled
 *    
 * These values are calculated using BASE + OFFSET values
*/ 

#include <EEPROM.h>
#include <math.h>
#include "enable.h"
#include "alarm.h"

#define BASE_A1 1
#define BASE_A2 6
#define BASE_A3 11
#define BASE_A4 16

#define OFFSET_HOURS 0
#define OFFSET_MINUTES 1
#define OFFSET_PM 2
#define OFFSET_ENABLE 3

// Internal Functions
int getBaseLocation(int alarmNum)
{
  switch(alarmNum) 
  {
    case 1:
      return BASE_A1;
    case 2:
      return BASE_A2;
    case 3:
      return BASE_A3;
    case 4:
      return BASE_A4;
  }
}

Alarm getAlarm(int alarmNum)
{
  int baseLocation = getBaseLocation(alarmNum);
  int hrs = EEPROM.read(baseLocation + OFFSET_HOURS);
  // HANDLE DEFAULT VALUE AND SHORT CIRCUIT TO DEFAULT FUNCTION
  
  int mins = EEPROM.read(baseLocation + OFFSET_MINUTES);
  
  int isPMFlag = EEPROM.read(baseLocation + OFFSET_PM);
  bool isPM = isPMFlag == 1;

  bool isEnabled = false;
  bool isSetSunday = false;
  bool isSetMonday = false;
  bool isSetTuesday = false;
  bool isSetWednesday = false;
  bool isSetThursday = false;
  bool isSetFriday = false;
  bool isSetSaturday = false;
    
  int enableFlags = EEPROM.read(baseLocation + OFFSET_ENABLE);
  for(int i = 0; i < 8; i++)
  {
    int testNum = pow(2, i);
    bool flagEnabled = testNum & (1<<i);
    if(flagEnabled)
    {
      Enable value =  static_cast<Enable>(testNum);
      switch(value) 
      {
        case Base:
          isEnabled = true;
          break;
        case Sunday:
          isSetSunday = true;
          break;
        case Monday:
          isSetMonday = true;
          break;
        case Tuesday:
          isSetTuesday = true;
          break;
        case Wednesday:
          isSetWednesday = true;
          break;
        case Thursday:
          isSetThursday = true;
          break;
        case Friday:
          isSetFriday = true;
          break;
        case Saturday:
          isSetSaturday = true;
          break;      
        default:
          break; 
      }
    }
  }

  Alarm a;
  a.id = alarmNum;
  a.hour = hrs;
  a.minute = mins;
  a.isPM = isPM;
  a.isEnabled = isEnabled;
  a.isSetSunday = isSetSunday;
  a.isSetMonday = isSetMonday;
  a.isSetTuesday = isSetTuesday;
  a.isSetWednesday = isSetWednesday;
  a.isSetThursday = isSetThursday;
  a.isSetFriday = isSetFriday;
  a.isSetSaturday = isSetSaturday;
  return a;
}

// External Functions
Alarm* getAlarmsFromMemory() 
{
  Alarm arr[4];
  for(int i = 1; i <= 4; i++)
  {
    arr[i-1] = getAlarm(i);
  }
  return arr;
}

void writeAlarmToMemory(Alarm a)
{
  int baseAddr = getBaseLocation(a.id);
  EEPROM.write(baseAddr + OFFSET_HOURS, a.hour);
  EEPROM.write(baseAddr + OFFSET_MINUTES, a.minute);
  EEPROM.write(baseAddr + OFFSET_PM, a.isPM);
  int enableValue = 0;
  if(a.isEnabled)
  {
    enableValue += (int)Base;
  }
  if(a.isSetSunday)
  {
    enableValue += (int)Sunday;
  }
  if(a.isSetMonday)
  {
    enableValue += (int)Monday;
  }
  if(a.isSetTuesday)
  {
    enableValue += (int)Tuesday;
  }
  if(a.isSetWednesday)
  {
    enableValue += (int)Wednesday;
  }
  if(a.isSetThursday)
  {
    enableValue += (int)Thursday;
  }
  if(a.isSetFriday)
  {
    enableValue += (int)Friday;
  }
  if(a.isSetSaturday)
  {
    enableValue += (int)Saturday;
  }
  EEPROM.write(baseAddr + OFFSET_ENABLE, enableValue);
}
