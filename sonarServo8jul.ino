#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
   
   const int Echo_pin=2; 
   const int Trig_pin=3;
   const int switchPos=30;
   const int restPos=0;
   
   long  duration,distance_cm=255,jarak=15;
 
   
   void ranging();

void setup() {
  // put your setup code here, to run once:
   myservo.attach(5);

   pinMode(Trig_pin,OUTPUT);
   pinMode(Echo_pin,INPUT);

  
Serial.begin(9600);
Serial.println("Hello");


  myservo.write(switchPos);
    delay(500);
    myservo.write(restPos);
    delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:



  ranging();
  
  Serial.print("distance: ");
  Serial.println(distance_cm);

  if(distance_cm<11 && distance_cm>0){
    myservo.write(switchPos);
    delay(500);
    myservo.write(restPos);
    delay(1000);
  }



delay(500);
//;digitalread

}


void ranging() {

  digitalWrite(Trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig_pin, LOW);
  duration = pulseIn(Echo_pin,HIGH,20000);

  distance_cm = duration /29 / 2 ;

}
