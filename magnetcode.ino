#include <LiquidCrystal.h>

const int hallSensorPin = 8;                      // connect the hall effect sensor on pin 2
const unsigned long sampleTime = 1000;
const int maxRPM = 1260;                  // maximum RPM for LCD Bar
int rpmMaximum = 0;

const int 
backLight = 13,
rs = 12,
en = 11, 
d4 = 5, 
d5 = 4, 
d6 = 3, 
d7 = 2;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  pinMode(hallSensorPin,INPUT);
  lcd.begin(16, 2);
  lcd.print("Initializing");
  delay(1000);
  lcd.clear();
}

void loop() 
{
  delay(100);
  int rpm = getRPM();
  if (rpm > rpmMaximum) rpmMaximum = rpm;
  lcd.clear();
  displayRPM(rpm);
  displayBar(rpm);
  
}

int getRPM()
{
  int count = 0;
  boolean countFlag = LOW;
  unsigned long currentTime = 0;
  unsigned long startTime = millis();
  while (currentTime <= sampleTime)
  {
    if (digitalRead(hallSensorPin) == HIGH)
    {
      countFlag = HIGH;
    }
    if (digitalRead(hallSensorPin) == LOW && countFlag == HIGH)
    {
      count++;
      countFlag=LOW;
    }
    currentTime = millis() - startTime;
  }
  int countRpm = int(60000/float(sampleTime))*count;
  return countRpm;
}

void displayRPM(int rpm) 
{
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print(rpm,DEC);
  lcd.setCursor(7,0);
  lcd.print(rpmMaximum, DEC);
  lcd.setCursor(13,0);
  lcd.print("MAX");
  Serial.print("RPM = ");
  Serial.print(rpm);
  Serial.print("  MAX RPM = ");
  Serial.println(rpmMaximum);
}

void displayBar(int rpm)
{
  int numOfBars=map(rpm,0,maxRPM,0,15);
  lcd.setCursor(0,1);
  if (rpm!=0)
  {
  for (int i=0; i<=numOfBars; i++)
   {
        lcd.setCursor(i,1);
        lcd.write(1023);
      }
  }
} 

