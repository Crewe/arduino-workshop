#include <LCD.h>
#include <Wire.h>

LCD *screen = NULL;
int red = 3;
int grn = 2;
int red_button = 8;
int grn_button = 9;
int red_state = 0;
int grn_state = 0;
int photo = 0;
int oldLvl = 0;

void setup() {
  screen = getSainDisplay();
  screen->clear();
  Wire.begin();

  pinMode(red, OUTPUT);
  pinMode(grn, OUTPUT);
  pinMode(red_button, INPUT);
  pinMode(grn_button, INPUT);
  screen->clear();
}

void loop() {
  if (digitalRead(red_button) != red_state) {
    if (digitalRead(red_button) == 1) {
      red_state = 1;
      digitalWrite(red, HIGH);
      screen->setCursor(0,0);
      screen->write("         ");
      screen->setCursor(0,0);
      screen->write("Red: ON");
    }
    else {
      red_state = 0;
      digitalWrite(red, LOW);
      screen->setCursor(0,0);
      screen->write("         ");
      screen->setCursor(0,0);
      screen->write("Red: OFF");
    }
  }

  if (digitalRead(grn_button) != grn_state) {
    if (digitalRead(grn_button) == 1) {
      grn_state = 1;
      digitalWrite(grn, HIGH);
      screen->setCursor(0,1);
      screen->write("           ");
      screen->setCursor(0,1);
      screen->write("Green: ON");
    }
    else {
      grn_state = 0;
      digitalWrite(grn, LOW);
      screen->setCursor(0,1);
      screen->write("           ");
      screen->setCursor(0,1);
      screen->write("Green: OFF");
    }
  }

  photo = analogRead(A0);
  int level = map(photo, 0, 1023, 0, 7);
  //screen->setCursor(8, 0);
  //screen->clear();
  //screen->print(level);
  
  if (oldLvl != level) {
    level = oldLvl;
    screen->setCursor(9, 0);
    screen->write("       ");
    screen->setCursor(9, 0);
    for(int i=0;i <= level; i++)
    {
      screen->print("*");
    }
  }
  delay(50);
}
