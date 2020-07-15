   const int irPin1=2;
   const int irPin2=3;

   const int valveRelay=10;
   const int soapRelay=11;

   const int on=0;
   const int off=1;
   
   
   long currentMillis,valveRelaytimer,pumptimer,valveRelayDebounce=400,pumpDebounce=50;
   bool valveRelayOn=0,pumpOn=0;
   


void setup() {
  // put your setup code here, to run once:
   pinMode(irPin1,INPUT);
   pinMode(irPin2,INPUT);
   

   pinMode(13,OUTPUT);
   pinMode(valveRelay,OUTPUT);
   pinMode(soapRelay,OUTPUT);

Serial.begin(9600);
Serial.println("Hello");
digitalWrite(13, LOW);
digitalWrite(valveRelay, off); 
digitalWrite(soapRelay, off);    
}

void loop() {
  
  
  if(!(digitalRead(irPin1))){
   // digitalWrite(13, HIGH);
    digitalWrite(valveRelay,on);
    valveRelayOn=1;
    valveRelaytimer=millis();
    //delay(50);
  //==========delay start==========================
  
  //===========delay end========================
  } else if(valveRelayOn==1){
  currentMillis=millis();
  if(currentMillis-valveRelaytimer>valveRelayDebounce){
  //digitalWrite(13, LOW);  //just for debugging by switching ON onboard LED.
  digitalWrite(valveRelay, off); // toggle low for spray valveRelay.
  valveRelayOn=0;
  }
  }else if(valveRelayOn==0){
  //digitalWrite(13, LOW);  //just for debugging by switching ON onboard LED.
  digitalWrite(valveRelay, off); // toggle low for spray valveRelay.
    
  }
if(!(digitalRead(irPin2))){
    digitalWrite(13, HIGH);
    digitalWrite(soapRelay, on);
    pumpOn=1;
    pumptimer=millis();
    //delay(50);
  //===========delay end========================
  } 
  else  if(pumpOn==1){
  currentMillis=millis();
  if(currentMillis-pumptimer>pumpDebounce){
  digitalWrite(13, LOW);  //just for debugging by switching ON onboard LED.
  digitalWrite(soapRelay, off); // toggle low for spray valveRelay.
  pumpOn=0;
  }
  }else if(pumpOn==0){
  digitalWrite(13, LOW);  //just for debugging by switching ON onboard LED.
  digitalWrite(soapRelay, off); // toggle low for spray valveRelay.
    
  }
  delay(50);
}
