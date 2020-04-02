
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int ir=12;
bool servopos=0;
void setup() {
  // put your setup code here, to run once:
   myservo.attach(9);

pinMode(ir,INPUT);
pinMode(13,OUTPUT);
Serial.begin(9600);

  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(0);              // tell servo to go to position in variable 'pos'
    delay(10); 
  }

}

void loop() {
  // put your main code here, to run repeatedly:
bool buttonState = digitalRead(ir);
digitalWrite(13, buttonState);
//Serial.println(buttonState);

if(!buttonState){

   //servopos=!servopos;
  
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(180);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15ms for the servo to reach the position
  }  
  
   for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(0);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15ms for the servo to reach the position
 } 
  //}
  //Serial.print("pos: ");
  //Serial.println(servopos);
}



delay(200);
//;digitalread

}
