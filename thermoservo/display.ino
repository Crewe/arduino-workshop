#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR 0x27
#define BACKLIGHT_PIN 3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

LCD* getSainDisplay() {
  LiquidCrystal_I2C lcd1602(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);
  LCD *lcd = &lcd1602;
  lcd->setBacklightPin(BACKLIGHT_PIN, POSITIVE);
  lcd->begin(16,2);
  return lcd;
}
