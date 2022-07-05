// Include the AccelStepper Library
#include <AccelStepper.h>

// Define pin connections
const int dirPin = 2;
const int stepPin = 3;


// Define motor interface type
#define motorInterfaceType 1
#define stepsPerRevolution 800
// Creates an instance
AccelStepper myStepper(motorInterfaceType, stepPin, dirPin);

void setup() {

Serial.begin(9600); // Default communication rate of the Bluetooth module
  Serial.println("serial initialised...");
  // set the maximum speed, acceleration factor,
  // initial speed and the target position
  myStepper.setMaxSpeed(500);
  myStepper.setAcceleration(500);
  myStepper.setSpeed(400);
  myStepper.setCurrentPosition(0);
  //myStepper.moveTo(800);
}
signed int stepp=stepsPerRevolution;
int i=0;

char serData;
String btData = ""; 
signed int medVol = 0;
void loop() {


if(Serial.available() > 0){ // Checks whether data is comming from the serial port


   
   btData = Serial.readString(); 
   medVol = btData.toInt();
  Serial.println(medVol);
  //} 
myStepper.setCurrentPosition(0);
myStepper.moveTo(medVol);
}

//

//
//  // Move the motor one step
  myStepper.run();


}
