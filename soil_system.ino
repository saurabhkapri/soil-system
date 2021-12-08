#include <LiquidCrystal.h>
#include<Servo.h>

LiquidCrystal lcd(12,11,5,4,3,2);
Servo Lservo;

int LDR1=A1;
int LDR2=A2;
int data_LDR1=0;
int data_LDR2=0;
int moisture=0;

void setup() {
 lcd.begin(16, 2);
 lcd.print("Starting");
 Lservo.attach(13);
 pinMode(10,OUTPUT);
 
 delay(2000);
}

void loop() {
  data_LDR1=analogRead(LDR1);
  data_LDR2=analogRead(LDR2);
  Lservo.detach();
  while(data_LDR1!=data_LDR2)
  { 
    if(data_LDR1<data_LDR2)
    {
      Lservo.attach(13);
      Lservo.write(0);
      lcd.clear();
      lcd.print("going left");
      delay(50);
    }
    else if(data_LDR1>data_LDR2)
    {
      Lservo.attach(13);
      Lservo.write(180);
      lcd.clear();
      lcd.print("going right");
      delay(50);
    }
    data_LDR1=analogRead(LDR1);
    data_LDR2=analogRead(LDR2);
  }
  Lservo.detach();
  lcd.clear();
  lcd.print("stopped");
  delay(50);

  moisture=0;
  for(int i=0;i<=100;i++)
  {
    moisture=moisture+analogRead(A0);
    delay(1);
  }
  moisture=moisture/100.0;
  moisture=map(moisture,550,0,0,100);
  if(moisture<30)
  {
    lcd.clear();
    lcd.print("moisture low");
    digitalWrite(10,HIGH);
    delay(700);                   // time you want motor to run
  }
  lcd.clear();
  lcd.print("level normal");
  digitalWrite(10,LOW);
  
  delay(50000);                  //time we want system to wait before next measurement
}
