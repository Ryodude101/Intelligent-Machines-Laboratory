
#include <LiquidCrystal.h>

/* This program will present a recipe on an LCD.
 * The user must complete this recipe within the
 * given time period.
 * 
 * The defined pins below are assigned to digital pins
 * on the arduino.
 * 
 */

const int rs = 8, en = 9, d4 = 7, d5 = 6, d6 = 5, d7 = 4;

/* Digital pins for 7-segment display.
 * D# designates which display is selected.
 * 
 */
const int D1 = 22, D2 = 24, D3 = 26, D4 = 28;


LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

/*
 *  Each segment will be assigned to a unique pin on PORTB.
 *  
 *  PB0     PB1     PB2     PB3     PB4     PB5     PB6     PB7
 *  a = 53, b = 52, c = 51, d = 50, e = 10, f = 11, g = 12, dp = 13
 *  
 */

void setup() {
  // put your setup code here, to run once:

  DDRB = 0b11111111; // set all PORTB as outputs
  DDRA = 0b11111111; // set PA0, PA2, PA4, PA6 as outputs

}

void loop() {
  // put your main code here, to run repeatedly:

  // Array containing values to display 
  int digit_array[10] = {0b00111111,0b00000110,0b01011011,0b01001111,0b01100110,0b01101101,0b01111101,0b00000111,0b01111111,0b01101111};

  PORTA = 0b0111111;

  while(1){
  /*
  digitalWrite(display_array[0],HIGH);
  digitalWrite(display_array[1],HIGH);
  digitalWrite(display_array[2],HIGH);
  */

  for (int i=0; i<10; i++){
  PORTB = digit_array[i]; // send digit value to PORTB
  delay(1000); // delay 1 second
  } 
  }
  
}
