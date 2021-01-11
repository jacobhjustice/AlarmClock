#include <RTClib.h>
#include <Wire.h>
#include <LiquidCrystal.h>

#define PIN_LCD_RS 12
#define PIN_LCD_ENABLE 11
#define PIN_LCD_DATA_1 7
#define PIN_LCD_DATA_2 8
#define PIN_LCD_DATA_3 9
#define PIN_LCD_DATA_4 10

bool _isEnabled = false;
RTC_DS3231 rtc;
LiquidCrystal lcd(PIN_LCD_RS, PIN_LCD_ENABLE, PIN_LCD_DATA_1, PIN_LCD_DATA_2, PIN_LCD_DATA_3, PIN_LCD_DATA_4);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  
    // Clears the LCD screen
    lcd.clear();
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print(" Hello world!");
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // Print a message to the LCD.
  lcd.print(" LCD Tutorial");

}
