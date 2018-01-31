const int controlPin1 = 2;
const int controlPin2 = 3;
const int enablePin = 9;
const int directionSwitchPin = 4;
const int onOffSwitchPin = 5;
const int potPin = A0;

int onOffState = 0;
int onOffStatePrev = 0;
int directionState = 0;
int directionStatePrev = 0;

int motorSpeed = 0;
int motorEnable = 0;
int motorDirection = 1;

void setup() {
  pinMode(directionSwitchPin, INPUT);
  pinMode(onOffSwitchPin, INPUT);
  pinMode(controlPin1, OUTPUT);
  pinMode(controlPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);
}

void loop() {
  onOffState = digitalRead(onOffSwitchPin);
  delay(1);
  directionState = digitalRead(directionSwitchPin);
  motorSpeed = analogRead(potPin)/4;

  if (onOffState != onOffStatePrev){
    if(onOffState == HIGH) {
      motorEnable = !motorEnable;
    }
  }

  if (directionState != directionStatePrev){
    if(directionState == HIGH) {
      motorDirection = !motorDirection;
    }
  }

  if (motorDirection == 1) {
    digitalWrite(controlPin1, HIGH);
    digitalWrite(controlPin2, LOW);
  }
  else {
    digitalWrite(controlPin1, LOW);
    digitalWrite(controlPin2, HIGH);
  }

  if (motorEnable == 1) {
    analogWrite(enablePin, motorSpeed);
  }
  else 
  {
    analogWrite(enablePin, 0);
  }

  directionStatePrev = directionState;
  onOffStatePrev = onOffState;
}
