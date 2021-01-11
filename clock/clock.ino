#include <RTClib.h>
#include <Wire.h>
#include <LiquidCrystal.h>

#define PIN_LCD_RS 12
#define PIN_LCD_ENABLE 11
#define PIN_LCD_DATA_1 7
#define PIN_LCD_DATA_2 8
#define PIN_LCD_DATA_3 9
#define PIN_LCD_DATA_4 10

#define VIEW_TIME 1
#define VIEW_EDIT_ALARM_1 2
#define VIEW_EDIT_ALARM_2 3
#define VIEW_EDIT_ALARM_2 4
#define VIEW_EDIT_ALARM_2 5

bool _isEditingTime;
int _activeView;

RTC_DS3231 rtc;
LiquidCrystal lcd(PIN_LCD_RS, PIN_LCD_ENABLE, PIN_LCD_DATA_1, PIN_LCD_DATA_2, PIN_LCD_DATA_3, PIN_LCD_DATA_4);

void setup () {  
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();

  _isEditingTime = false;
  _activeView = VIEW_TIME;
}

void loop () {

}

void display () {

}

void displayEditAlarm (int alarmValue) {

}

void checkCurrentTime () {
  // Get Current Time
  // Check against all active alarms
}

struct Alarm {
    int hour;
    int minute;
    Day[] days;
    bool isActive;
}

enum Day {
    Monday = 1, 
    Tuesday = 2,
    Wednesday = 4,
    Thursday = 8,
    Friday = 16,
    Saturday = 32,
    Sunday = 64
};