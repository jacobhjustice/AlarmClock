#ifndef ALARM_H
#define ALARM_H

typedef struct 
{
  int id;
  int hour;
  int minute;
  int second;
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

#endif /* ALARM_H */
