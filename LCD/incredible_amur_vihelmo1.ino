// C++ code
//

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int pm = A0;
void setup()
{
  lcd.init();
  lcd.backlight();
  pinMode(pm, INPUT);
}

void loop()
{
  int input = analogRead(pm);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(input);
  delay(5000);
}