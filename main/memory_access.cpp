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
#include "alarm.h"

#define BASE_A1 1
#define BASE_A2 6
#define BASE_A3 11
#define BASE_A4 16

#define OFFSET_HOURS 0
#define OFFSET_MINUTES 1
#define OFFSET_PM 2
#define OFFSET_ENABLE 3

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

Alarm getAlarm(int baseLocation)
{
  int hrs = EEPROM.read(baseLocation + OFFSET_HOURS);
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

  return Alarm
  {
    
  };
}

Alarms& getAlarmsFromMemory() 
{
  Alarms arr;
  for(int i = 1; i <= 4; i++)
  {
    int pos = getBaseLocation(i);
    arr[i-1] = getAlarm(pos);
  }
  return arr;
}

void writeAlarmToMemory(Alarm a)
{
  
}