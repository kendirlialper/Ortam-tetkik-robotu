#include <LiquidCrystal_I2C.h>
#include <dht11.h>
#define DHT11PIN 2
dht11 DHT11;

#include <MQ135.h>
#include <SimpleDHT.h>
int pinDHT11 = 2;
SimpleDHT11 dht11;
int sensorValue;
MQ135 gasSensor = MQ135(3);
int ppm = gasSensor.getPPM();

LiquidCrystal_I2C lcd(0x3f,20, 4);

int komut;
int in1=24;
int in2=26;
int in3=28;
int in4=30;
int ENA=22;
int ENB=32;
int HIZ=240;

int sesDurum = 0;
int Buzzer = 11;
int Htone = 800;
int Ltone = 200;

int Rled = 10;
int Bled = 8;

int sensormq135;


void sol() { //sola dönüş
  analogWrite(ENA,HIZ);     analogWrite(ENB,HIZ);    digitalWrite(in1,HIGH);   
  digitalWrite(in2,LOW);    digitalWrite(in3,HIGH);  digitalWrite(in4,LOW);
}
void sag() {//sağ
  analogWrite(ENA,HIZ);     analogWrite(ENB,HIZ);    digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);   digitalWrite(in3,LOW);   digitalWrite(in4,HIGH);
}
void geri()  {//geri
  analogWrite(ENA,HIZ);     analogWrite(ENB,HIZ);    digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);    digitalWrite(in3,LOW);   digitalWrite(in4,HIGH);
}
void ileri()  { //ileri
  analogWrite(ENA,HIZ);     analogWrite(ENB,HIZ);    digitalWrite(in1,LOW); 
  digitalWrite(in2,HIGH);   digitalWrite(in3,HIGH);  digitalWrite(in4,LOW);
}
void dur()  {
  digitalWrite(ENA,LOW);   digitalWrite(ENB,LOW);
}


void setup()
{ 
  Serial.begin(9600);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(3, INPUT);

  dur();
  int sesDurum=0;
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1,0);
}

void loop()
  {

  byte temp = 0;
  byte hum = 0;
  sensorValue = analogRead(0);
  float co2_ppm = gasSensor.getPPM();


  if(dht11.read(pinDHT11, &temp, &hum, NULL))
  {
    return;
  }
  Serial.print((int)temp);
  Serial.print(",");
  Serial.print((int)hum);
  Serial.print(",");
  Serial.print(sensorValue, DEC);
  Serial.print(",");
  Serial.print(co2_ppm);
    
  DHT11.read(DHT11PIN);  
     
  lcd.clear();
  lcd.setCursor(1,0); 
  lcd.print((int)hum); lcd.print("% nem, "); lcd.print((int)temp); lcd.print("'C");
  sensormq135= analogRead(0);
  if(sensormq135<400)
  {
    lcd.setCursor(0,1);
    lcd.print("Hava temiz");    
  }
  else if((sensormq135<800) && (sensormq135>399))
  {
    lcd.setCursor(0,1);
    lcd.print("Hava ortalama");    
  }
  else if(sensormq135>700)
  {
    lcd.setCursor(0,1);
    lcd.print("Hava riskli");    
  }
  
  lcd.setCursor(0,1);
  
  komut=Serial.read();


  
  if(komut==5)      {  
        ileri(); 
        delay(500); 
        dur(); 
       }              
  else if(komut==2) {  
        geri(); 
        delay(500); 
        dur();

       }
  else if(komut==3) {  
        sol();  
        delay(500);   
        dur();

       }
  else if(komut==4) { 
        sag(); 
        delay(500);   
        dur();

       }

   else if(komut==7) {    
        dur();

       }    
 else if(komut==6)  
       {  
         if(sesDurum==0)
         {
            sesDurum=1;
          }
    
        else if(sesDurum==1)
         {
           sesDurum=0;
           analogWrite(Buzzer,LOW); 
           analogWrite(Bled,LOW); 
           analogWrite(Rled,LOW); 
           
          }             
        }
 else if(komut==8)
 {
         
 }

 if(sesDurum==1)
{
            analogWrite(Buzzer,Htone); 
            analogWrite(Bled,LOW); 
            analogWrite(Rled,255);
            delay(150);
            analogWrite(Buzzer,Ltone); 
            analogWrite(Bled,255); 
            analogWrite(Rled,LOW);
            delay(150);
}
  
}



 

