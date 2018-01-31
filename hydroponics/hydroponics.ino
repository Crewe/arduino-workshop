#include <LCD.h>
#include <Wire.h>

#define BUFFER 20
#define BAUD 9600
#define PH_PROBE_ADDR 0x63

byte code = 0;                   //used to hold the I2C response code.
byte in_char = 0;                //used as a 1 byte buffer to store inbound bytes from the pH Circuit.
float ph_float;                  //float var used to hold the float value of the pH.
byte sleeping = 0;
char i = 0;

LCD *screen = NULL;

char* getPhData()
{
  char ph_data[BUFFER];
  while (Wire.available()) {         //are there bytes to receive.
    in_char = Wire.read();           //receive a byte.
    ph_data[i] = in_char;            //load this byte into our array.
    i += 1;                          //incur the counter for the array element.
    if (in_char == 0) {              //if we see that we have been sent a null command.
      i = 0;                         //reset the counter i to 0.
      Wire.endTransmission();        //end the I2C data transmission.
      break;                         //exit the while loop.
    }
  }
  return ph_data;
}

char* calibrate()
{
  if (sendCommand("c", PH_PROBE_ADDR) == 1)
  {
    // do things to calibrate...
  }
}

char* codeToString(int code) {
  switch (code) {                  //switch case based on what the response code is.
    case 0:
      return "Sleeping";
      break;
      
    case 1:                        //decimal 1.
      return "Success";   //means the command was successful.
      break;                       //exits the switch case.

    case 2:                        //decimal 2.
      return "Failed";    //means the command has failed.
      break;                       //exits the switch case.

    case 254:                      //decimal 254.
      return "Pending";   //means the command has not yet been finished calculating.
      break;                       //exits the switch case.

    case 255:                      //decimal 255.
      return "No Data";   //means there is no further data to send.
      break;                       //exits the switch case.
  }
}

// r - read value
// c - calibrate
// sleep - sleeps the device
int sendCommand(char *command, int addr)
{
  // Send the command to the device
  Wire.beginTransmission(addr);  //call the circuit by its ID number.
  Wire.write(command);                        //transmit the command that was sent through the serial port.
  Wire.endTransmission();                 //end the I2C data transmission.
  
  // Wait required time for command to execute
  if (command == "c" || command == "r") delay(900); else delay (300);

  if (command != "sleep") {
    sleeping = 0; // device will wake if other command is sent
    // Read the data from the device
    Wire.requestFrom(PH_PROBE_ADDR, 20, 1); //call the circuit and request 20 bytes (this may be more than we need)
    code = Wire.read();               //the first byte is the response code, we read this separately.
  } 
  else {
    sleeping = 1;
    code = 0;
  }
  return code;
}

void setup() {
  // put your setup code here, to run once:
  screen = getSainDisplay();
  screen->clear();
  Wire.begin();
  delay(2000);
  //scan();
}

void loop() {
  char *val;
  int res = sendCommand("r", PH_PROBE_ADDR);
  if (res == 1) val = getPhData(); else val = "0.000";
  screen->clear();
  screen->print(codeToString(res));
  screen->setCursor(0, 1);
  screen->print("PH: ");
  screen->print(val);
  delay(5000);
  res = sendCommand("sleep", PH_PROBE_ADDR);
  screen->clear();
  screen->print(codeToString(res));
  delay(5000);
}
