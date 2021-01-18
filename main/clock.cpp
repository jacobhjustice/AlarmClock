#include "time.h"
#include "RTClib.h"

RTC_DS3231 rtc;

Time getTime() {
  // Temp hardcode
  Time val;
  val.hour = "06";
    return (Time) { .hour="06", .minute = "40", .am_pm = "PM", .day = "18", .month = "01", .year ="21",    };
}

void setTime() {

}

bool isAlarmTriggered() {

}
