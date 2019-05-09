
// constants won't change. They're used here to set pin numbers:
const int ad0 = 2;     // the number of the pushbutton pin
const int ad1 = 3;      // the number of the LED pin
const int ad2 = 4;
const int ad3 = 5;
const int ad4 = 6;
const int ad5 = 7;
const int ad6 = 8;
const int ad7 = 9;
const int adcByte = 10;
const int conv = 11;
const int busy = 12;


byte a2d = 0;
byte lsb_a2d = 0;
byte lsbAdc,msbAdc,conv_state=0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

   pinMode(ad0, INPUT);
   pinMode(ad1, INPUT);
   pinMode(ad2, INPUT);
   pinMode(ad3, INPUT);   
   pinMode(ad4, INPUT);
   pinMode(ad5, INPUT);
   pinMode(ad6, INPUT);
   pinMode(ad7, INPUT);
   pinMode(busy, INPUT);
   pinMode(adcByte, OUTPUT);
   pinMode(conv, OUTPUT);

   digitalWrite(conv, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:


digitalWrite(conv, HIGH);
digitalWrite(conv, LOW);
delayMicroseconds(10);
digitalWrite(conv, HIGH);

do{
  conv_state=digitalRead(busy);
}while(conv_state==0);


digitalWrite(adcByte, LOW);
msbAdc=readByte();
Serial.print(lsbAdc);
Serial.print("  ");

digitalWrite(adcByte, HIGH);
lsbAdc=readByte();
Serial.println(lsbAdc); 
delay(1000);
}

byte readByte(){
byte myByte;  
myByte  = digitalRead (ad0);
myByte |= digitalRead (ad1) << 1;
myByte |= digitalRead (ad2) << 2;
myByte |= digitalRead (ad3) << 3;
myByte |= digitalRead (ad4) << 4;
myByte |= digitalRead (ad5) << 5;
myByte |= digitalRead (ad6) << 6;
myByte |= digitalRead (ad7) << 7;
return myByte;

}
