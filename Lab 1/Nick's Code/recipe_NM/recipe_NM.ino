#include <LiquidCrystal.h>

// Each int corresponds with the given pin on the board.
const int rs = 34, en = 36, d4 = 38, d5 = 40, d6 = 42, d7 = 44;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

void setup () {
  lcd.begin(16,2);
  lcd.print("Roast Marshmallow");
  lcd.setCursor(0,1);
  lcd.print("1.Obtain mallow.");
  lcd.setCursor(18,0);
  lcd.print("2.Skewer mallow.");
  lcd.setCursor(18,1);
  lcd.print("3.Grill mallow.");
  delay(1000);
}

void loop () {
  for(int Count = 0; Count < 29; Count++)
  {
    lcd.scrollDisplayLeft();
    delay(800);
  }
}
