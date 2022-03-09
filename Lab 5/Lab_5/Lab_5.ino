/* Intelligent Machines Lab 5
 * 03.03.22
 * Nick Morse and Ryan Colon
 */


unsigned long duration, cm;

void setup() {
  // put your setup code here, to run once:

  // Use OC1A - PB5: Enable as an output
  DDRB = 0b00100000;

  // Enable Trig:PH5:output, Echo:PH6:input
  DDRH = 0b00100000;

  // Use TCNT1
  TCCR1A = 0b10000011; // non-inverted mode, 10bit fast PWM
  TCCR1B = 0b00001100;
  OCR1A = 94;

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  PORTH = 0b00000000;
  delayMicroseconds(5);
  PORTH = 0b00100000;
  delayMicroseconds(10);
  PORTH = 0b00000000;

  duration = pulseIn(9, HIGH);

  // Calculate distance
  cm = (duration/2)/29.1;

  Serial.print(duration);
  //Serial.print(" cm");
  Serial.println();
  delay(100);

  if(cm < 30){
    // Opens door
    for(int i = 85; i < 185; i++){
      OCR1A = i;
      delay(10);
    }
    // Wait 5 sec. for person to enter
    delay(5000);
    // Closes door
    for(int j = 185; j > 85; j--){
      OCR1A = j;
      delay(10);
    }
  }

  
  

}
