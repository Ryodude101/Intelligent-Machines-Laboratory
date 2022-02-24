
/*
Intelligent Machines Lab 3 LCD-7S Button Recipe
Ryan Colon & Nick Morse
02.11.22
 */

#include <LiquidCrystal.h>

const int rs = 8, en = 9, LCDd4 = 7, LCDd5 = 6, LCDd6 = 5, LCDd7 = 4;
LiquidCrystal lcd(rs, en, LCDd4, LCDd5, LCDd6, LCDd7);

const int upperCPMBound = 800, lowerCPMBound = 700;

int upperCPms, lowerCPms;

String currLowerMessage;

/* 7 Segments stuff
 *    PA0      PA2      PA4      PA6
 *  D1 = 22, D2 = 24, D3 = 26, D4 = 28
 *    PB0     PB1     PB2     PB3     PB4     PB5     PB6    
 *  a = 53, b = 52, c = 51, d = 50, e = 10, f = 11, g = 12
 */

//Address for each 7-segment of the 47S display
const int SSD1 = 0b1111110, SSD2 = 0b1111011, SSD3 = 0b1101111, SSD4 = 0b0111111; //The devices are active low, no I don't feel like fixing that
//OPCodes for displaying integer N in SSN on 7-segment display
const int SS9 = 0b1101111, SS8 = 0b1111111, SS7 = 0b0000111, SS6 = 0b1111101, SS5 = 0b1101101, SS4 = 0b1100110, SS3 = 0b1001111, SS2 = 0b1011011, SS1 = 0b0000110, SS0 = 0b0111111, SSN = 0b0000000; 
const int rotateDelay = 1; //delay in ms between changing 7 segments
const int SSC[11] = {SS0, SS1, SS2, SS3, SS4, SS5, SS6, SS7, SS8, SS9, SSN};

//Stuff needed to implement the button lock
int lock[4];
int lockIn[4];
int buttonOutput[15] = {0,0,0,0,0,0,0,4,0,0,0,3,0,2,1};

void setup() {
  DDRB = 0b11111111; // set all PORTB as outputs
  DDRA = 0b11111111; // set PA0, PA2, PA4, PA6 as outputs
  DDRC = 0;
  
  lcd.begin(16,2);
  lcd.clear();
  Serial.begin(9600);

  upperCPms = ceil((60.0 * 1000.0) / (float) upperCPMBound);
  lowerCPms = ceil((60.0 * 1000.0) / (float) lowerCPMBound);

  Serial.print("upper bound:\t");
  Serial.println(upperCPms);
  Serial.print("lower  bound:\t");
  Serial.println(lowerCPms);

  lcd.clear();
  lcd.setCursor(0,0);
  typeToLCD("Create Keycode:");
  lcd.setCursor(0,1);

  char buff[3];

  int count = 0;
  while(count < 4){
    if(PINC < 15){
      lock[count] = PINC;
      ++count;
      lcd.print(itoa(buttonOutput[lock[count-1]], buff, 10));
      delay(500); 
    }
  }

  delay(1000);

  lcd.clear();
  lcd.setCursor(0,0);
  typeToLCD("  Keylock code  ");
  lcd.setCursor(0,1);
  typeToLCD("     set!       ");
  delay(2000);
}

void loop() {
  lcd.clear();
  lcd.setCursor(0,0);
  typeToLCD("Unlock Recipe:");
  lcd.setCursor(0,1);
  char buff[3];

  //Get user to enter code
  int count = 0;
  while(count < 4){
    if(PINC < 15){
      lockIn[count] = PINC;
      ++count;
      lcd.print(itoa(buttonOutput[lockIn[count-1]], buff, 10));
      delay(500); 
    }
  }

  delay(1000);

  //Check user input matches set code
  bool test = true;
  for(int i = 0; i < 4; i++){
    if(lockIn[i] != lock[i])
      test = false;
  }
  
  if(test){
    lcd.clear();
    lcd.setCursor(0,0);
    typeToLCD("Keycode correct!");
    lcd.setCursor(0,1);
    lcd.print("Unlocking...");
    delay(3000);
    lcd.clear();
    typeToLCD("DMPTRKS Recipe:");
    lcd.setCursor(0,1);
    typeToLCD("Cinnamon Toast!");
    delay(2500);
    lcd.clear();
    typeToLCD("You'll need:");
    lcd.setCursor(0,1);
    typeToLCD("  A toaster");
    currLowerMessage = "  A toaster";
    delay(1500);
    vertScrollLCD("  1 slice bread");
    delay(1500);
    vertScrollLCD("  Some butter");
    delay(1500);
    vertScrollLCD("  Some cinnamon");
    delay(2500);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   Let's get    ");
    lcd.setCursor(0,1);
    lcd.print("   toasting!    ");
    delay(2000);
    LCDStepFormatting(1, "  get bread");
    delay(2500);
    LCDStepFormatting(2, "bread in toaster");
    delay(2500);
    LCDStepFormatting(3, "  toast bread");
    delay(2500);
    LCDStepFormatting(4, "  wait for toast");
    timerLoop(90);
    PORTB = SSC[10];
    delay(1000);
    LCDStepFormatting(5, "  butter time");
    delay(2500);
    LCDStepFormatting(6, "butter the toast");
    delay(2500);
    LCDStepFormatting(7, "  spray cinnamon");
    delay(2500);
    LCDStepFormatting(8, "  feed \"mother\"");
    delay(5000);
  }
  else{
    lcd.clear();
    lcd.setCursor(0,0);
    typeToLCD(" Incorrect code ");
    lcd.setCursor(0,1);
    typeToLCD("    entered     ");
    delay(3000);
  }
}

//Function to display to 7-seg a timer and countdown, takes number of seconds as an integer input
void timerLoop(int numSec){

  unsigned long int currTime = millis();
  bool startBool = true;
  int nums[4];
  
  while(numSec != 0){
    if(millis() - currTime >= 1000 || startBool){
      startBool = false;
      int* digits = intToTime(numSec);
      
      for(int i = 0; i < 4; i++)
        nums[i] = digits[i];
        
      delete [] digits;
      --numSec;
      currTime = millis();
    }
    PORTA = SSD1;
    PORTB = SSC[nums[0]];
    delay(rotateDelay);
    PORTA = SSD2;
    PORTB = SSC[nums[1]];
    delay(rotateDelay);
    PORTA = SSD3;
    PORTB = SSC[nums[2]];
    delay(rotateDelay);
    PORTA = SSD4;
    PORTB = SSC[nums[3]];
    delay(rotateDelay);
  }
  delay(1000);
}

//Function to convert integer to time digits, returns an integer array of size 4
int* intToTime(int seconds){
  int* digits = new int[4];
  
  digits[1] = floor(seconds/60);
  digits[0] = floor(digits[1]/10);
  digits[1] = digits[1]%10;

  digits[3] = seconds%60;
  digits[2] = floor(digits[3]/10);
  digits[3] = digits[3]%10;

  return digits;
}

/*
Function to display text to lcd using a vertical scrolling effect
You need to initialize currLowerMessage before using
If you see the lower text before scrolling not mention the top text after scrolling
then you need to double check and make sure currLowerMessage is being used properly
*/
void vertScrollLCD(String textToPrint){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(currLowerMessage);
  lcd.setCursor(0,1);
  typeToLCD(textToPrint);
  currLowerMessage = textToPrint;
}

//Function that takes a string and writes it to the LCD in a typing style
void typeToLCD(String toType){
  for(int i = 0; i < toType.length(); i++){
    lcd.print(toType[i]);
    delay(random(lowerCPms, upperCPms));
  }
}

//Function to print string in text formatting
//can not accept a stepNum value > 99
void LCDStepFormatting(int stepNum, String toPrint){
  String stepString = "Step ";
  char temp[2];
  itoa(stepNum, temp, 10);
  stepString += temp;
  stepString += ':';
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(stepString);
  lcd.setCursor(0,1);
  typeToLCD(toPrint);
}
