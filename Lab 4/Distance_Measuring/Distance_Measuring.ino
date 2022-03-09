/*
Intelligent Machines Lab 4 Distance Measuring and The Screams of the Damned
Ryan Colon & Nick Morse
02.24.22
 */

#include <LiquidCrystal.h>
#include <stdlib.h>

const int AREF = 5;
const int NumLevel = 1023;

const int rs = 8, en = 9, LCDd4 = 7, LCDd5 = 6, LCDd6 = 5, LCDd7 = 4;
LiquidCrystal lcd(rs, en, LCDd4, LCDd5, LCDd6, LCDd7);
 
void setup() {
  //Setup the LCD
  lcd.begin(16,2);
  lcd.clear();
  Serial.begin(9600);

  //Setup the ADC
  ADMUX = 0x47; //Select ADC channel 7, right justified, AREF = 5V @ AVCC
  ADCSRA = 0x94; //Dont Convert, Don't Autotrigger, Clear flag, Interrupt Disabled
  ADCSRB = 0;
}

void loop() {
  //Acquire Voltage
  ADCSRA |= 0x40; //Start reading
  while(!(ADCSRA & 0x10));//wait for read to finish
  int adcRead = ADC; //read value

  float cm = 4800 / (float)(adcRead - 20);
  
  //Print to LCD
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Distense:");
  lcd.setCursor(0,1);
  lcd.print(cm, 0);
  lcd.print(" cm");
  delay(500);
}
