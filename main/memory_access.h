#include "alarm.h"
#ifndef MEMORY_ACCESS_H
#define MEMORY_ACCESS_H

Alarms& getAlarmsFromMemory();

Alarm getAlarm(int baseLocation);

void writeAlarmToMemory(Alarm a);

#endif /* MEMORY_ACCESS_H */

