
   int Trig_pin=2;
   int Echo_pin=3;
   int valve=4;

void setup() {
  // put your setup code here, to run once:
   pinMode(Trig_pin,OUTPUT);
   pinMode(Echo_pin,INPUT);
   pinMode(7,OUTPUT);
   pinMode(13,OUTPUT);
   pinMode(valve,OUTPUT);

Serial.begin(9600);
Serial.println("Hello");
digitalWrite(13, LOW);
digitalWrite(7, LOW); 
}

void loop() {
  // put your main code here, to run repeatedly:
  long  duration,distance_cm=255;


   
  digitalWrite(Trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig_pin, LOW);
  duration = pulseIn(Echo_pin,HIGH);

  distance_cm = duration /29 / 2 ;

  
  Serial.println("distance: ");
  Serial.println(distance_cm);
  
  if(distance_cm>2 && distance_cm<30){
  digitalWrite(13, HIGH);
  digitalWrite(valve, HIGH);
  delay(5000);  
  digitalWrite(13, LOW);
  digitalWrite(valve, LOW);
  }

  delay(500);

}
