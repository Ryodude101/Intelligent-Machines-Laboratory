/* Intelligent Machines Lab 5 Rework
 * 03.03.22
 * Nick Morse and Ryan Colon
 */

void distToAng(unsigned long dist);
int currAng = 270;

void setup() {
  // Use OC1A - PB5: Enable as an output
  DDRB = 0x20;

  // Enable Trig:PH5:output, Echo:PH6:input
  DDRH = 0x20;

  // Use TCNT1
  TCCR1A = 0b10000011; // non-inverted mode, 10bit fast PWM
  TCCR1B = 0b00001100;
  OCR1A = 94;

  Serial.begin(9600);
}

void loop() {
  PORTH = PINH & 0xDF;
  delayMicroseconds(5);
  PORTH = PINH | 0x20;
  delayMicroseconds(10);
  PORTH = PINH & 0xDF;
  PORTH = PINH & 0xBF;
  unsigned long tim = micros();
  while((PINH & 0x40)^0x40);
  while(PINH & 0x40);
  tim = micros() - tim;

  // Calculate distance
  unsigned long cm = (tim * 0.034) / 2;

  Serial.print(cm);
  Serial.print(" cm");
  Serial.println();
  delay(100);

  distToAng(cm);
}

void distToAng(unsigned long dist){
  int newAng;
  if((dist > 50) | (dist < 10))
    newAng = 270;
  else
    newAng = (21/4)*dist+(15/2);

  Serial.print("Ang ");
  Serial.println(newAng);

  if(newAng > currAng){
    for(int i = currAng; i < newAng; i++) {
      OCR1A = i;
      delay(10);
    }
  }
  else{
    for(int i = currAng; i > newAng; i--){
      OCR1A = i;
      delay(10);
    }
  }
  currAng = newAng;
}
