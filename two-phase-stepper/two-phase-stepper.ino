/* 
 *  Simple code for runng an EM-483 bipolar stepper.
 *  Coil A is connectid to pin 4 and 6
 *  Coil B is connected to pin 5 and 7
 *  
 *  Coil resistance: ~3.7Ohms 
 *  Supply: 5-6V 
 *  Max speed: 150RPM
 *  The motor moves at 1.8 degrees per step.
 *  The 8 half-steps move the motor 4 steps, or 7.2 degrees.
 *  
 *  http://fablabegypt.com/arduinostepper-withoutlibrary/
 *  http://domoticx.com/pinout-stappenmotor-shinano-kenshi-em-483/
 *  http://www.mauroalfieri.it/elettronica/motori-passo-passo-bipolari-con-arduino-controlla-la-velocita.html
 *  http://42bots.com/tutorials/bipolar-stepper-motor-control-with-arduino-and-an-h-bridge/
 *  http://www.instructables.com/id/EM-483-Specifications/
 */
 
#define MAX_SPEED 5000
#define MAX_STEPS 8
#define FULL_ROTATION 200 //

const byte steps[] = { 0x10, 0x50, 0x40, 0x60, 0x20, 0xA0, 0x80, 0x90 };

int spd = 0;
int i = 0; 
int count = 0;
int dir = 0;

void setup() {
  // Set Port D 4-7 high
  DDRD = DDRD | 0xF0;
  // Set all of port D low
  PORTD = 0x00;
  //Serial.begin(115200);
}



// Simple forward rotation
void loop() {
  for (int n = 0; n < sizeof(steps); n++)
  {
    PORTD = steps[n];
    delayMicroseconds(MAX_SPEED);
  }
}

// Sweep one direction then the other using
// Half stepping (Coils A and B), coil A, then coil B
void doItAll() {
  halfStepping(MAX_SPEED);
  delay(2500);
  phase1FullStepping(MAX_SPEED);
  delay(2500);
  phase2FullStepping(MAX_SPEED);
  delay(2500);
}

void halfStepping(int _delay)
{
  int done = 0;
  count = 0;
  do {
    PORTD = steps[count % MAX_STEPS];
    dir == 0 ? count++ : count--;
    // change direction after full rotation
    if (count >= (FULL_ROTATION * 2) || count <= 0) {
      dir = !dir;
      done++;
    }
    delayMicroseconds(_delay);
  } while (done != 2);
}

void phase1FullStepping(int _delay)
{
  int done = 0;
  count = 0;
  do {
    PORTD = steps[2 * (count % (MAX_STEPS/2))];
    dir == 0 ? count++ : count--;
    // change direction after full rotation
    if (count >= FULL_ROTATION || count <= 0) 
    {
      dir = !dir;
      done++;
    }
    delayMicroseconds(_delay);
  } while (done != 2);
}

void phase2FullStepping(int _delay)
{
  int done = 0;
  count = 0;
  do {
    PORTD = steps[(2 * (count % (MAX_STEPS/2))) + 1];
    dir == 0 ? count++ : count--;
    // change direction after full rotation
    if (count >= FULL_ROTATION || count <= 0) 
    {
      dir = !dir;
      done++;
    }
    delayMicroseconds(_delay);
  } while(done != 2);
}

// This gets wonky because the mapped speed 
// jumps around a lot needs to be smoothed out.
void anotherMethod() {
  int pos = analogRead(A0);
  spd = map(pos, 0, 1023, -1000, 1000);
  if ((spd >= -MAX_SPEED) && (spd <= MAX_SPEED)) 
  {
    // Stop the motor. It will run too fast
  }
  else if (spd > MAX_SPEED)
  {
    // go forward
    i = i > MAX_STEPS ? 0 : i;
    PORTD = steps[i];
    i++;
  }
  else {
    // go backward
    i = i < 0 ? MAX_STEPS : i;
    PORTD = steps[i];
    i--;
  }
  // rectify the speed if negative
  spd = spd < 0 ? (-1)*spd : spd;
  delay(spd);
}
