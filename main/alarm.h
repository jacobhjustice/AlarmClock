#include "enable.h"
#ifndef ALARM_H
#define ALARM_H

struct Alarm {
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
};

typedef Alarm Alarms[4];

#endif /* ALARM_H */
