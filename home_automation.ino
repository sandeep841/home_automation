#include <LiquidCrystal.h>
LiquidCrystal lcd(11,10,9,8,7,6);

//for buzzer tone
int buz=13;
int i = 0;
int numOfLoops = 0;
int noteDuration = 1000/8;
int pauseBetweenNotes = noteDuration*0.2;
//==========================================================
int relay1=5;
int relay2=4;
int relay3=3;
int relay4=2;

//==========================================================

int mod=12;
float distance,duration;

int temp =A5;
int ldr = A4;
int pir = A3;
int trig =A2;
int echo =A1;
int gas = A0;
//==========================================================


void setup()
{
  lcd.begin(16,2);
  Serial.begin(9600);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(buz,OUTPUT);
  
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(relay3,OUTPUT);
  pinMode(relay4,OUTPUT);
}


//==========================================================



void loop()
{
  //ldr
  float x= analogRead(ldr);
  Serial.println(x);
  if(x<900 /*&& (digitalRead(pir))==HIGH*/){
        digitalWrite(relay1,HIGH);
      }
      else{
        digitalWrite(relay1,LOW);
      }
  
  //====================================================
  
  //temp
  int value=analogRead(temp);
  float T = map(((value - 20) * 3.04), 0, 1023, -40, 125);
  lcd.setCursor(0,0);
  lcd.print("temp. : ");
  lcd.print(T);
  lcd.print(" c");
  Serial.println(T);
  delay(500);
  lcd.clear();
        if((T>15) && (T<=200)/*&&(digitalRead(pir))==HIGH */){
          digitalWrite(relay2,HIGH);
          digitalWrite(relay3,LOW);
        }
      else if(T>200/* && (digitalRead(pir))==HIGH */)
        {
          digitalWrite(relay2,LOW);
          
          digitalWrite(relay3,HIGH);
        }
        else
        {
          digitalWrite(relay3,LOW);
          digitalWrite(relay2,LOW);
        }

  
  //====================================================
//ultrasonic

          digitalWrite(trig,LOW);
          delayMicroseconds(2);
          digitalWrite(trig,HIGH);
          delayMicroseconds(10);
          digitalWrite(trig,LOW);
          duration = pulseIn(echo,HIGH);
          distance = duration * 0.0344 / 2;
            
                  if(distance<=10)
                  {
                            lcd.setCursor(0, 0);
                            lcd.print("Door: Person   ");
                            lcd.setCursor(0, 1);
                            lcd.print("Detected   ");
                                      for(numOfLoops = 0; numOfLoops < 4; numOfLoops++)
                                          {
                                           for(i = 25; i < 120; i++) 
                                             {
                                              tone(buz, 20*i, noteDuration);
                                              delay(pauseBetweenNotes);
                                             }
                                           for(i = 120; i >=25; i--) 
                                             {
                                              tone(buz, 20*i, noteDuration); 
                                               
                                             }
                                          }
                                      
                            delay(2000);
                            lcd.clear();
                      }
                  else
                     digitalWrite(buz,LOW);

//======================================================================================================
 float sensorValue,gas;
  sensorValue = analogRead(gas);

  if(sensorValue >= 25){
    digitalWrite(relay4,HIGH);
    
  
  }
  else{
    digitalWrite(relay4,LOW);
   
  }   
   
}
