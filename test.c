//#include <Servo.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tues", "Wednes", "Thurs", "Fri", "Satur"};
char monthsOfTheYear[12][12]={"Jan","Febr","Mars","Apr","Mai","June","July","Aug","Sept","Oct","Nov","Dec"};
 

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);

int trig = 2;
int echo = 3;
long lecture_echo;
long cm;
long perc;
int led1=13;
int led2=9;
int lim;
//int led_rouge=13;
//int led_jaune=12;
//Servo monServomoteur;

void setup(){
  Serial.begin(9600);
  Wire.begin();
  
// set up the LCD's number of columns and rows:
lcd.begin(20, 4);
//Centraliser le message
lcd.setCursor(5,0);
// Print a message to the LCD.
lcd.print("Trash is: ");
pinMode(trig, OUTPUT);
pinMode(echo, INPUT);
pinMode(led1, OUTPUT);
pinMode(led2, OUTPUT);
digitalWrite(trig, LOW);
Serial.begin(9600);

Serial.println ("Welcome To My Smart Trash Can ");
#ifndef ESP8266
  while (!Serial); // wait for serial port to connect. Needed for native USB
#endif

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}

void loop(){
//lcd.setCursor (0,0);
lcd.setCursor(5,1);
digitalWrite(trig, HIGH);
delayMicroseconds(5);
digitalWrite(trig, LOW);
lecture_echo = pulseIn(echo,HIGH);
cm = lecture_echo /58;

if (cm<=200){
  lim=cm;
}
//else if (cm>200){
 // Serial.print(">200");
//}

perc=(lim*100)/197;
lcd.println(perc);
lcd.setCursor(8,1);
lcd.println("% Full");
  
  if (perc>=80){
    
    // Allumer la led rouge
    digitalWrite(led1, LOW);
  	digitalWrite(led2, HIGH);
    
      delay(15);
    
  }
  else if (perc<80){
    
    digitalWrite(led2, LOW);
    digitalWrite(led1, HIGH);
  	
    delay(15);
  }
  lcd.setCursor(3,2);
  DateTime now = rtc.now();
  lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
  lcd.print(" ");
  lcd.print(now.day(), DEC);
  lcd.print(" ");
  lcd.print(monthsOfTheYear[now.month()]);
  lcd.print(" ");
  lcd.print(now.year(), DEC);
  //lcd.print('/');
  
  //lcd.print('/');
  
  //lcd.print(" (");
 
  //lcd.print(") ");
  lcd.setCursor(4,3);
  lcd.print(now.hour(), DEC);
  lcd.print(':');
  lcd.print(now.minute(), DEC);
  lcd.print(':');
  lcd.print(now.second(), DEC);
  lcd.println();

 

  
//delay(1500);

}
