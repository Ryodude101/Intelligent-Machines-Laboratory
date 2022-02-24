
//                            0            1           2           3         
const int buttonPin[4] = {0b11111110, 0b11111101, 0b11111011, 0b11110111};
byte bP1 = 2, bP2 = 0, bP3 = 3, bP4 = 1;

/*    passcode_count will increment when the correct button is pressed.
   *  Then at the end, if passcode_count == 4, then we know that all 
   *  correct buttons were pressed.
   *  
   *  step_count will increment whether or not the correct button is pressed.
   *  This is only required to move to the next button press.
   */
int passcode_count = 0, step_count = 1;

void setup() {
  // put your setup code here, to run once:

  DDRC = 0b00000000; // Initialize port C as inputs
  PORTC = 0b11111111;
  Serial.begin(9600);

  //Serial.print("Create passcode.\n\n");
  
  

  
}

void loop() {

  /*  
   *  System is required to display the value of the button
   *  no matter what.
   *  
   */

  // 1st button press
  if ((PINC == buttonPin[bP1]) && (step_count == 1)){
    passcode_count++;
    step_count++;
    Serial.print("*");
    delay(250);
  }
  
/*
  if((PINC != buttonPin[3]) && (step_count == 1)){
    step_count++;
    Serial.print("*");
  }
*/
  // 2nd button press
  if ((PINC == buttonPin[bP2]) && (step_count == 2)){
    passcode_count++;
    step_count++;
    Serial.print("*");
    delay(250);
  }
  
/*
  if((PINC != buttonPin[0]) && (step_count == 2)){
    step_count++;
  }
*/
  // 3rd button press
  if ((PINC == buttonPin[bP3]) && (step_count == 3)){
    passcode_count++;
    step_count++;
    Serial.print("*");
    delay(250);
  }
  
/*
  if((PINC != buttonPin[1]) && (step_count == 3)){
    step_count++;
    Serial.print("*");
  }
*/
  // 4th button press
  if ((PINC == buttonPin[bP4]) && (step_count == 4) && (passcode_count == 3)){
    passcode_count = 0;
    step_count = 1;
    Serial.print("*\n");
    delay(1750);
    Serial.print("Passcode was correct, you may enter.\n\n");
    
     /*
      if (passcode_count == 4){
        // Tell user that pass code was correct,
        // unlock the system.
        Serial.print("Passcode was correct, you may enter.\n\n");
        passcode_count = 0;
        step_count = 1;
        
      }

      else {
       passcode_count = 0;
       step_count = 1;
       //Tell user that pass code was incorrect
       return(0); 
      }
      */
    delay(250);
  }
  
/*
  if((PINC != buttonPin[2]) && (step_count == 4)){
    passcode_count = 0;
    step_count = 1;
    Serial.print("*");
    // Tell user that pass code was incorrect
    Serial.print("*");
    Serial.print("Passcode was incorrect.");
    return(0);
  }
*/ 

}
