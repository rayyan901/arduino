   long  duration2,distance_cm2=255,duration,distance_cm=255,jarak=15,jarak2=10;
   int Trig_pin=8;
   int Echo_pin=9;
   
   int Trig_pin2=6;
   int Echo_pin2=7;
   
   int valve=10;
   int valve2=11;
   int ondelay=8;  //30 = 9.7 secs.....8 with 600ms
   int i;
   void ranging();
   void ranging2();

   long currentMillis,valvetimer,pumptimer,valveDebounce=400,pumpDebounce=400;
   bool valveOn=0,pumpOn=0;
void setup() {
  // put your setup code here, to run once:
   pinMode(Trig_pin,OUTPUT);
   pinMode(Echo_pin,INPUT);
  
   pinMode(Trig_pin2,OUTPUT);
   pinMode(Echo_pin2,INPUT);
  // pinMode(7,OUTPUT);
   pinMode(13,OUTPUT);
   pinMode(valve,OUTPUT);
   pinMode(valve2,OUTPUT);

Serial.begin(9600);
Serial.println("Hello");
digitalWrite(13, LOW);
digitalWrite(valve, LOW); 
}

void loop() {
  // put your main code here, to run repeatedly:   

  ranging();
  ranging2();
  Serial.print("distance: ");
  Serial.print(distance_cm);
  
  Serial.print(" --- ");
  Serial.println(distance_cm2);
  
  if(distance_cm>2 && distance_cm<jarak){
    digitalWrite(13, HIGH);
    digitalWrite(valve, HIGH);
    valveOn=1;
    valvetimer=millis();
    delay(50);
  //==========delay start==========================
  
  //===========delay end========================
  } else if(valveOn==1){
  currentMillis=millis();
  if(currentMillis-valvetimer>valveDebounce){
  digitalWrite(13, LOW);  //just for debugging by switching ON onboard LED.
  digitalWrite(valve, LOW); // toggle low for spray valve.
  valveOn=0;
  }
  }else if(valveOn==0){
  digitalWrite(13, LOW);  //just for debugging by switching ON onboard LED.
  digitalWrite(valve, LOW); // toggle low for spray valve.
    
  }
if(distance_cm2>2 && distance_cm2<jarak2){
  //digitalWrite(13, HIGH);
    digitalWrite(valve2, HIGH);
    pumpOn=1;
    pumptimer=millis();
    delay(50);
  //===========delay end========================
  } 
  else  if(pumpOn==1){
  currentMillis=millis();
  if(currentMillis-pumptimer>pumpDebounce){
  //digitalWrite(13, LOW);  //just for debugging by switching ON onboard LED.
  digitalWrite(valve2, LOW); // toggle low for spray valve.
  pumpOn=0;
  }
  }else if(pumpOn==0){
  //digitalWrite(13, LOW);  //just for debugging by switching ON onboard LED.
  digitalWrite(valve2, LOW); // toggle low for spray valve.
    
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

  digitalWrite(Trig_pin2, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig_pin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig_pin2, LOW);
  duration2 = pulseIn(Echo_pin2,HIGH);

  distance_cm2 = duration2 /29 / 2 ;

}
