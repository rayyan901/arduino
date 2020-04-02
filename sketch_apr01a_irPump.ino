
int pump=7;
int ir=8;
//bool servopos=0;

unsigned long previousMillis = 0,elapse=0;        // will store last time LED was updated

// constants won't change:
const long interval = 500;           // interval at which to blink (milliseconds)

void setup() {
  // put your setup code here, to run once:
  // myservo.attach(9);

pinMode(ir,INPUT);
pinMode(13,OUTPUT);
pinMode(pump,OUTPUT);
Serial.begin(9600);
digitalWrite(pump, LOW);
  

}
void loop() {
  
  // put your main code here, to run repeatedly:
bool irIn = digitalRead(ir);
if(!irIn){
  digitalWrite(pump, HIGH);
  unsigned long currentMillis = millis();
  previousMillis = currentMillis;
  elapse=0;
  while(!irIn & ( elapse <= interval)){
    
    delay(1);

    
    irIn = digitalRead(ir);
    currentMillis = millis();
    elapse=currentMillis - previousMillis;    
  }
  digitalWrite(pump, LOW);
  do{
    irIn = digitalRead(ir);
  }while(!irIn);

  

  
}


}
