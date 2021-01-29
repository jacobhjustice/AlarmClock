#ifndef CLOCK_H
#define CLOCK_H

typedef struct 
{
  int id;
  int hour;
  int minute;
  bool isPM;

  bool isEnabled;
  bool isSetSunday;
  bool isSetMonday;
  bool isSetTuesday;
  bool isSetWednesday;
  bool isSetThursday;
  bool isSetFriday;
  bool isSetSaturday;
} Alarm;

typedef struct 
{
    int hour;
    int minute;
    int second;
    bool isPM;
    int day;
    int month;
    int year;
} ClockValue;

char* getFormattedHour(int value);

char* getFormattedMinute(int value);

char* getFormattedAMPM(bool isPM);

char* getFormattedDay(int value);

char* getFormattedMonth(int value);

char* getFormattedYear(int value);

ClockValue getTime();

void setTime();

#endif /* CLOCK_H */
