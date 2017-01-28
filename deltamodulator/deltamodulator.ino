// Author: Mrinmoy Sarkar
// email: mrinmoy.pol@gmail.com 

#define F_CPU 8000000L
#include <LiquidCrystal.h>
LiquidCrystal lcd(1, 0, 8, 9, 10, 11);
int previus_value = 0;
int delta_pin = 5;
int sampling_frequency = 1;
int sampling_ = 1;
int map_data[31]={32,33,34,35,37,38,40,41,43,45,47,50,52,55,58,62,66,71,76,83,90,100,111,125,142,166,200,250,333,500,1000};
void setup()
{
  delay(1000);
  lcd.begin(16, 2);
  lcd.print("Delta Modulator");
  lcd.setCursor(0,1);
  lcd.print("  Designed By  ");
  delay(2000);
  lcd.setCursor(0,0);
  lcd.print(" EEE SEC:A2 Group:02 2010 BATCH       ");
  lcd.setCursor(0,1);
  lcd.print(" ROLL:1006042,43,44,45,46,47,48,49    ");
  delay(2000);
  for(int i = 0;i<25;i++)
  {
    lcd.scrollDisplayLeft();
    delay(570);
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Fs in Kilo hertz");
  lcd.setCursor(0,1);
  lcd.print("                ");
  lcd.setCursor(5,1);
  lcd.print("KHz");
  lcd.setCursor(0,1);
  lcd.print(1000);
  pinMode(delta_pin,OUTPUT);
  attachInterrupt(0,increase,FALLING);
  attachInterrupt(1,decrease,FALLING);
  pinMode(7,OUTPUT);
  digitalWrite(7,HIGH);
  //tone(7,1000*1000);
}
void loop()
{
  int present_value = analogRead(0);
  if((present_value - previus_value)>0)
  {
    digitalWrite(delta_pin,HIGH);
  }
  else
  {
    digitalWrite(delta_pin,LOW);
  }
  delayMicroseconds(sampling_);
  previus_value = present_value;
}
void increase()
{
  sampling_frequency++;
  sampling_frequency = constrain(sampling_frequency,1,63);
  if(sampling_frequency >= 33)
  {
    sampling_ = map_data[sampling_frequency - 33];
  }
  else 
  {
    sampling_ = sampling_frequency;
  }
  sampling_ = constrain(sampling_,1,1000);
  lcd.setCursor(0,1);
  lcd.print("    ");
  lcd.setCursor(0,1);
  int fs = (1000/sampling_);
  //tone(7,fs*1000);
  lcd.print(fs);
  for(int i = 0;i<5000;i++);
}
void decrease()
{
  sampling_frequency--;
  sampling_frequency = constrain(sampling_frequency,1,63);
  if(sampling_frequency >= 33)
  {
    sampling_ = map_data[sampling_frequency - 33];
  }
  else 
  {
    sampling_ = sampling_frequency;
  }
  sampling_ = constrain(sampling_,1,1000);
  lcd.setCursor(0,1);
  lcd.print("    ");
  lcd.setCursor(0,1);
  int fs = (1000/sampling_);
  //tone(7,fs*1000);
  lcd.print(fs);
  for(int i = 0;i<5000;i++);
}
