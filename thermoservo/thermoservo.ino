#include <LCD.h>
#include <Servo.h>

#define SERVO_PIN 9
#define KNOB_PIN A0
#define THERMO_PIN A1
#define THERMOSTAT_OUT_PIN 12

LCD *screen = NULL;
Servo servo;
int knobVal;
//float temp;
int oldPos=0;
int oldTemp=0;
int thermostat[2] = {25, 26}; 

void checkTemperature(int temp)
{
  // turn on led if temp is > set trigger value;
  if (temp < thermostat[0])
  {
    digitalWrite(THERMOSTAT_OUT_PIN, HIGH);
  }
  else 
  {
    digitalWrite(THERMOSTAT_OUT_PIN, LOW);
  }
}

void setup() {
  screen = getSainDisplay();
  screen->clear();
  servo.attach(SERVO_PIN);
  pinMode(THERMOSTAT_OUT_PIN, OUTPUT);
}

void loop() {
  knobVal = analogRead(KNOB_PIN);
  int tempVoltage = analogRead(THERMO_PIN);
  float temp = (((tempVoltage /1024.0) * 5.0) - 0.5) * 100;
  int pos = map(knobVal, 0, 1023, 0, 179);
  if (oldPos != pos || oldTemp != temp) {
    servo.write(pos);
    screen->clear();
    screen->print("Angle: ");
    screen->print(pos);
    screen->setCursor(0,1);
    screen->print("Temp: ");
    screen->print(temp);
    screen->print("C");

    checkTemperature((int)temp);
    
    oldPos = pos;
    oldTemp = temp;
  }
  delay(10);
}
