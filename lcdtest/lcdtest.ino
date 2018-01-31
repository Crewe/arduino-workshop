#include <Wire.h>
#include <LCD.h>

LCD *lcd = NULL;
int n = 1;

void setup() {
  // Set up the LCD
  lcd = getSainDisplay();
  lcd->setBacklight(HIGH);
  lcd->home();
  lcd->print(" Hello World!");
  lcd->setCursor(0,1);
  lcd->noBlink();
  lcd->print("   Arduino!");
  delay(3000);
  lcd->clear();
  scan();
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd->setCursor(10,1);
  lcd->print(n++, DEC);
  lcd->setBacklight(HIGH);
  delay(200);
}
