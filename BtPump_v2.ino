#include <Stepper.h>
const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 10,11,12,13);

#define ledPin 7
int i;
//int state = 0;
String btData = ""; 
int medVol = 0;
//====================================================
void runStepper(int rotation, signed int dir) {
int i;
//==============init stepper
if(dir==1)
{

myStepper.step(-1);
myStepper.step(1);
}else if(dir== -1){
  
myStepper.step(1);
myStepper.step(-1);
}
delay(200);
//==============
  for(i=0;i<rotation;i++){
  myStepper.step(dir);
     
  }
    myStepper.step(0);  
////==
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);

  
}

//
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(57600); // Default communication rate of the Bluetooth module
  myStepper.setSpeed(60);

  
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
}

char serData;
int inData=0;
void loop() {

  //medVol=0;
  //inData=0;
  if(Serial.available() > 0){ // Checks whether data is comming from the serial port
   // state = Serial.read(); // Reads the data from the serial port
   serData=Serial.peek();
   if (isDigit(serData)){

   
   btData = Serial.readString(); 
   medVol = btData.toInt();
  } else {
   btData = Serial.readString();
    
  }

 inData=1;
 }

//================================================
if(inData==1){
if((medVol>0 && medVol<1000)){

   Serial.println(medVol);
   runStepper(medVol,1);
  btData = ""; 
  medVol=0;
  inData=0;
//==    
    }else if(btData=="reverse"){
     Serial.println("reverse");
     runStepper(15,-1);
     btData = "";
     inData=0; 
    }else{
      Serial.println("error");
      
     btData = "";
     inData=0; 
    }
 medVol=0;   
}
//======================================
  

}
