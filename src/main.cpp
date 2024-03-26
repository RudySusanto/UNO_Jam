#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>

RTC_DS1307 rtc;
LiquidCrystal_I2C lcd(0x3F,16,2);

char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
void setup () {
 while (!Serial); 
 Serial.begin(9600);
 
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Experiment 7");
  lcd.setCursor(0, 1);
  lcd.print("CE-Lab 2024");
  delay(2000);
  lcd.clear();
 
 if (! rtc.begin()) {
   Serial.println("Couldn't find RTC");
   lcd.setCursor(0, 0);
   lcd.print("Couldn't find RTC");
   while (1);
 }
 if (! rtc.isrunning()) {
   Serial.println("RTC is NOT running!");
   lcd.setCursor(0, 1);
   lcd.print("RTC is NOT running!");
   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
 }
}
void loop () {
 DateTime now = rtc.now();
 lcd.clear();
 
 lcd.setCursor(1,0);
 lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
 lcd.print(", ");
 lcd.print(now.day(), DEC);
 lcd.print('/');
 lcd.print(now.month(), DEC);
 lcd.print('/');
 lcd.print(now.year(), DEC);
 lcd.setCursor(4,1);
 lcd.print(now.hour(), DEC);
 lcd.print(':');
 lcd.print(now.minute(), DEC);
 lcd.print(':');
 lcd.print(now.second(), DEC);
 delay(1000);
}