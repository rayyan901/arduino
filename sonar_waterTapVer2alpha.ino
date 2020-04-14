   const int Trig_pin=8;
   const int Echo_pin=9;   
   const int TrigSoap=6;
   const int EchoSoap=7;
   const int valveRelay=10;
   const int soapRelay=11;
   
   long  duration2,soapDistance=255,duration,distance_cm=255,jarak=15,soapDistRange=10;
   long currentMillis,valveRelaytimer,pumptimer,valveRelayDebounce=400,pumpDebounce=400;
   bool valveRelayOn=0,pumpOn=0;
   
   void ranging();
   void ranging2();

void setup() {
  // put your setup code here, to run once:
   pinMode(Trig_pin,OUTPUT);
   pinMode(Echo_pin,INPUT);
  
   pinMode(TrigSoap,OUTPUT);
   pinMode(EchoSoap,INPUT);
  // pinMode(7,OUTPUT);
   pinMode(13,OUTPUT);
   pinMode(valveRelay,OUTPUT);
   pinMode(soapRelay,OUTPUT);

Serial.begin(9600);
Serial.println("Hello");
digitalWrite(13, LOW);
digitalWrite(valveRelay, LOW); 
digitalWrite(soapRelay, LOW);    
}

void loop() {
  // put your main code here, to run repeatedly:   

  ranging();
  ranging2();
  Serial.print("distance: ");
  Serial.print(distance_cm);
  
  Serial.print(" --- ");
  Serial.println(soapDistance);
  
  if(distance_cm>2 && distance_cm<jarak){
    digitalWrite(13, HIGH);
    digitalWrite(valveRelay, HIGH);
    valveRelayOn=1;
    valveRelaytimer=millis();
    delay(50);
  //==========delay start==========================
  
  //===========delay end========================
  } else if(valveRelayOn==1){
  currentMillis=millis();
  if(currentMillis-valveRelaytimer>valveRelayDebounce){
  digitalWrite(13, LOW);  //just for debugging by switching ON onboard LED.
  digitalWrite(valveRelay, LOW); // toggle low for spray valveRelay.
  valveRelayOn=0;
  }
  }else if(valveRelayOn==0){
  digitalWrite(13, LOW);  //just for debugging by switching ON onboard LED.
  digitalWrite(valveRelay, LOW); // toggle low for spray valveRelay.
    
  }
if(soapDistance>2 && soapDistance<soapDistRange){
  //digitalWrite(13, HIGH);
    digitalWrite(soapRelay, HIGH);
    pumpOn=1;
    pumptimer=millis();
    delay(50);
  //===========delay end========================
  } 
  else  if(pumpOn==1){
  currentMillis=millis();
  if(currentMillis-pumptimer>pumpDebounce){
  //digitalWrite(13, LOW);  //just for debugging by switching ON onboard LED.
  digitalWrite(soapRelay, LOW); // toggle low for spray valveRelay.
  pumpOn=0;
  }
  }else if(pumpOn==0){
  //digitalWrite(13, LOW);  //just for debugging by switching ON onboard LED.
  digitalWrite(soapRelay, LOW); // toggle low for spray valveRelay.
    
  }
  delay(50);
}





void ranging() {

  digitalWrite(Trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig_pin, LOW);
  duration = pulseIn(Echo_pin,HIGH);

  distance_cm = duration /29 / 2 ;

}


void ranging2() {

  digitalWrite(TrigSoap, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigSoap, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigSoap, LOW);
  duration2 = pulseIn(EchoSoap,HIGH);

  soapDistance = duration2 /29 / 2 ;

}
