

int ledPin = 13;  // LED connected to digital pin 13
int inPin = 12;    // pushbutton connected to digital pin 7
int val = 0;   
// the setup routine runs once when you press reset:
void setup() {

  pinMode(ledPin, OUTPUT); 
  pinMode(inPin, INPUT);    // sets the digital pin 7 as input
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A6);
  int delaytime;
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (9800.0 / 1023.0);
  delaytime=voltage;
  if(delaytime>8000){
    delaytime=8000;
    }
  // print out the value you read:
  Serial.print(delaytime);
  Serial.print("  ");
  Serial.println(voltage);

while( (val = digitalRead(inPin)));
 while( !(val = digitalRead(inPin)));   // read the input pin
 delayMicroseconds(delaytime); 
  digitalWrite(ledPin, 1);  // sets the LED to the button's value
  delayMicroseconds(1000); 
  digitalWrite(ledPin, 0);
}
