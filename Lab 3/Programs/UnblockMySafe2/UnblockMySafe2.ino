int lock[4];

int buttonOutput[15] = {0,0,0,0,0,0,0,4,0,0,0,3,0,2,1};

void setup() {
  Serial.begin(9600);
  DDRC = 0; // Set Port C to input

  Serial.print("Please enter lock code: ");

  int count = 0;
  while(count < 4){
    if(PINC < 15){
      lock[count] = PINC;
      ++count;
      Serial.print(buttonOutput[lock[count-1]]);
      delay(500);
    }
  }

  Serial.println(" ");

  for(int i = 0; i < 4; i++)
    Serial.print(buttonOutput[lock[i]]);
}

void loop() {
  // put your main code here, to run repeatedly:

}
