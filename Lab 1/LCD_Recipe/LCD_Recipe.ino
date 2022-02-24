
/*
Intelligent Machines Lab 1 LCD Recipe
Ryan Colon
01.16.22
 */

#include <LiquidCrystal.h>

const int rs = 8, en = 9, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int upperCPMBound = 800, lowerCPMBound = 700;

int upperCPms, lowerCPms;

String currLowerMessage;

void setup() {
  lcd.begin(16,2);
  lcd.clear();
  Serial.begin(9600);

  upperCPms = ceil((60.0 * 1000.0) / (float) upperCPMBound);
  lowerCPms = ceil((60.0 * 1000.0) / (float) lowerCPMBound);

  Serial.print("upper bound:\t");
  Serial.println(upperCPms);
  Serial.print("lower  bound:\t");
  Serial.println(lowerCPms);

  typeToLCD("Ryan's Recipe:");
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
  delay(2500);
  LCDStepFormatting(5, "  butter time");
  delay(2500);
  LCDStepFormatting(6, "butter the toast");
  delay(2500);
  LCDStepFormatting(7, "  spray cinnamon");
  delay(2500);
  LCDStepFormatting(8, "  feed \"mother\"");
}

void loop() {

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
