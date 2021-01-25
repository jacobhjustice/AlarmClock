#include "clock_value.h"
#include "alarm.h"
#include "RTClib.h"

#define OFFSET_YEARS_RTC 2000

RTC_DS3231 rtc;

bool initializeTime() 
{
  // If no RTC connection, return failure
  if(! rtc.begin()) 
  {
    Serial.println("RTC Not found.");
    return false;
  }
  
  // If RTC lost power, default to system time (note: user may have to adjust)
  if(rtc.lostPower())
  {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

ClockValue getTime() 
{
  // Read DateTime fields
  DateTime current = rtc.now();
  int second = current.second();
  int minute = current.minute();
  int hour = current.hour();
  int year = current.year();
  int month = current.month();
  int day = current.day();
  bool isPM = false;

  // Transform fields to readable form
  month++;
  if(hour == 0)
  {
    isPM = false;
    hour = 12;
  }
  else if (hour <= 11) 
  {
    isPM = hour == 11;
    hour++;
  }
  else 
  {
    hour -= 11;
    isPM = true;
  }

  year = (year + OFFSET_YEARS_RTC) % 100;

  ClockValue value;
  char buffer[2];
  itoa(second, buffer, 10);
  value.second = buffer;
  itoa(minute, buffer, 10);
  value.minute = buffer;
  itoa(hour, buffer, 10);
  value.hour = buffer;
  itoa(year, buffer, 10);
  value.year = buffer;
  itoa(month, buffer, 10);
  value.month = buffer;
  itoa(day, buffer, 10);
  value.day = buffer;
  value.am_pm = isPM ? "PM" : "AM";
  return value;
}

void setTime(ClockValue input) 
{
  int year = OFFSET_YEARS_RTC + atoi(input.year); // Might need to tweak
  int month = atoi(input.month) - 1;
  int day = atoi(input.year);
  int hour = atoi(input.year);
  int minute = atoi(input.minute);
  int second = 0;
  
  rtc.adjust(DateTime(year, month, day, hour, minute, 0));
}

bool isAlarmTriggered(ClockValue time, Alarm* alarms) 
{
  for(int i = 0; i < 4; i++)
  {
    // Compare time == alarms[i]
  }
}
