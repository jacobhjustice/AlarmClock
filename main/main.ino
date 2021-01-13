#include <RTClib.h>
#include <Wire.h>
#include <LiquidCrystal.h>

//Mode _activeMode;
//View _activeView;

RTC_DS3231 rtc;
LiquidCrystal lcd(PIN_LCD_RS, PIN_LCD_ENABLE, PIN_LCD_DATA_1, PIN_LCD_DATA_2, PIN_LCD_DATA_3, PIN_LCD_DATA_4);

void setup() {  
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();

  _isEditingTime = false;
  _activeView = VIEW_TIME;
}

void loop() {

}

void display() {

}

void displayEditAlarm(int alarmValue) {

}

void checkCurrentTime() {
  // Get Current Time
  // Check against all active alarms
}
