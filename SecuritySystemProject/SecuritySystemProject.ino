#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>

RTC_DS1307 rtc;
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  


int ldrPin = A0;
int trigPin = 34;    
int echoPin = 35;
int soundPin = 37;
int tempPin = A1;
int flamePin = 43;  
int gasPin = A2;  
int buzzerPin = 51;

int ldrServer = 2;
int ultrasonicServer = 3;
int soundServer = 4;
int tempServer = 5;
int flameServer = 6;
int gasServer = 7;

int ldrVal = 0;
int ultrasonicVal = 0;
int soundVal = 0;
int tempVal = 0;
int flameVal = 1;
int gasVal = 0;

int buzzerState = LOW;

long duration, cm, inches;
float mv,cel,far;

void setup(){
  pinMode(ldrPin,INPUT);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(soundPin,INPUT);
  pinMode(tempPin,INPUT);
  pinMode(flamePin,INPUT);
  pinMode(gasPin,INPUT);
  pinMode(buzzerPin,OUTPUT);

  pinMode(ldrServer,OUTPUT);
  pinMode(ultrasonicServer,OUTPUT);
  pinMode(soundServer,OUTPUT);
  pinMode(tempServer,OUTPUT);
  pinMode(flameServer,OUTPUT);
  pinMode(gasServer,OUTPUT);
  
  Wire.begin();
  rtc.begin();
  lcd.begin(16,2);
  Serial.begin(9600);
}

void loop(){
  digitalWrite(ldrServer,LOW);
  digitalWrite(ultrasonicServer,LOW);
  digitalWrite(soundServer,LOW);
  digitalWrite(tempServer,LOW);
  digitalWrite(flameServer,LOW);
  digitalWrite(gasServer,LOW);


  

  //RTC
  DateTime now = rtc.now(); 

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Time: ");
  lcd.print(now.hour(), DEC);
  lcd.print(':');
  lcd.print(now.minute(), DEC);
  lcd.print(':');
  lcd.print(now.second(), DEC);
  lcd.print(' ');
  lcd.setCursor(0,1);
  lcd.print("SONAR: ");
  lcd.print(inches);
  lcd.print("in,");
  lcd.print(cm);
  lcd.print("cm");

  
  /*
  
  if(now.hour() >= 1 && now.hour() <= 6){
  }
   */


  //Read
  ldrVal = analogRead(ldrPin);
  soundVal = digitalRead(soundPin);
  tempVal = analogRead(tempPin);
  flameVal = digitalRead(flamePin);
  gasVal = analogRead(gasPin);


  buzzerState = LOW;

  //LDR
  if(ldrVal < 800){
    if(buzzerState == LOW){
        tone(buzzerPin,1000,400);
        delay(400);
        tone(buzzerPin,2500,200);
        delay(200);
        tone(buzzerPin,1000,200);
        delay(200);
        tone(buzzerPin,2500,200);
        delay(200);
        tone(buzzerPin,1000,200);
        delay(200);
        buzzerState = HIGH;
     }
    digitalWrite(ldrServer,HIGH);
    Serial.println("ALERT! WALKING DETECTED.");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("LASER CROSSED!");
    delay(2000);
  }






  //ULTRASONIC
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
 

  cm = (duration/2) / 29.1;     
  inches = (duration/2) / 74;
  ultrasonicVal = cm; 

  if(ultrasonicVal <= 30){
      if(buzzerState == LOW){
        
        tone(buzzerPin,3000,300);
        delay(200);
        tone(buzzerPin,1000,200);
        delay(200);
        tone(buzzerPin,1500,200);
        delay(200);
        tone(buzzerPin,1000,200);
        delay(200);
        buzzerState = HIGH;
        
     }
    digitalWrite(ultrasonicServer,HIGH);
    Serial.println("ALERT! BUGGLER IS CLOSE.");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("MOTION DETECTED!");
    lcd.setCursor(0,1);
    lcd.print("SONAR: ");
    lcd.print(inches);
    lcd.print("in,");
    lcd.print(cm);
    lcd.print("cm");
    delay(2000);
  }
  else if(ultrasonicVal > 30){
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  lcd.setCursor(0,1);
  lcd.print("SONAR: ");
  lcd.print(inches);
  lcd.print("in,");
  lcd.print(cm);
  lcd.print("cm");
  }





  //SOUND
  if(soundVal == 1){
    
      if(buzzerState == LOW){
       tone(buzzerPin,1000,200);
        delay(400);
        tone(buzzerPin,1500,200);
        delay(200);
        tone(buzzerPin,2500,200);
        delay(200);
        tone(buzzerPin,1500,200);
        delay(200);
        buzzerState = HIGH;
     }
    digitalWrite(soundServer,HIGH);
    Serial.println("ALERT! SOUND DETECTED.");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("SOUND DETECTED!");
    delay(2000);
  }
  else if(soundVal == 0){
    
  }



  //TEMP

  mv = ( tempVal/1024.0)*5000; 
  cel = mv/10;
  far = (cel*9)/5 + 32;
  
  if(cel >= 90.0){
      if(buzzerState == LOW){
        tone(buzzerPin,3000,200);
        delay(200);
        tone(buzzerPin,2000,200);
        delay(200);
        tone(buzzerPin,1000,200);
        delay(200);
        buzzerState = HIGH;
     }
    digitalWrite(tempServer,HIGH);
    Serial.println("ALERT! HIGH-TEMPERATURE DETECTED.");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("HIGH TEMP!");
    lcd.setCursor(0,1);
    lcd.print(cel);
    lcd.print(" C");
    delay(2000);
    }
  else if(cel < 30.0){

    }


  //FIRE
  if(flameVal == 1){
    
  }
  else if(flameVal == 0){
       if(buzzerState == LOW){
        tone(buzzerPin,1500,200);
        delay(200);
        tone(buzzerPin,2000,200);
        delay(200);
        tone(buzzerPin,2500,200);
        delay(200);
        tone(buzzerPin,3000,200);
        delay(200);
        buzzerState = HIGH;
     }
    digitalWrite(flameServer,HIGH);
    Serial.println("ALERT! FIRE DETECTED.");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("FIRE DETECTED!");
    delay(2000);
  }


  
   //GAS
  if(gasVal >= 500){
       if(buzzerState == LOW){
         tone(buzzerPin,3000,200);
        delay(200);
        tone(buzzerPin,2500,200);
        delay(200);
        tone(buzzerPin,2000,200);
        delay(200);
        tone(buzzerPin,1500,200);
        delay(200);
        buzzerState = HIGH;
     }
    digitalWrite(gasServer,HIGH);
    Serial.println("ALERT! GAS LEAKAGE DETECTED.");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("GAS LEAKAGE!");
    delay(2000);
  }
  else if(gasVal < 500){
    
  }


  Serial.print("LDR: ");
  Serial.println(ldrVal);
  Serial.print("ULTRASONIC: ");
  Serial.println(ultrasonicVal);
  Serial.print("SOUND: ");
  Serial.println(soundVal);
  Serial.print("TEMP: ");
  Serial.println(cel);
  Serial.print("FLAME: ");
  Serial.println(flameVal);
  Serial.print("GAS: ");
  Serial.println(gasVal);

  if(buzzerState == LOW){
    delay(250);
 
 }



  

  
  

}
