#include <SPI.h>
#include <LoRa.h>

int counter = 0;
int secondCounter=0;
byte pin4status=1;

unsigned long previousMillis = 0; 
const long interval = 2000; 
void setup() {

  pinMode(4, INPUT_PULLUP);
 
  
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Sender");

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  LoRa.setTxPower(20);

//===  
}
int val=5;
int countHigh=0;
unsigned long currentMillis; 
void loop() {
  if(counter>=2000){
  Serial.print("time alive: ");
  Serial.println(secondCounter);
  counter=0;
  secondCounter++;
  }
  //========
  pin4status = digitalRead(4);
  if(pin4status==0){
      val=5;
     // send packet
      LoRa.beginPacket();
      LoRa.print(val);
      LoRa.endPacket();
      Serial.print("sending packet: ");
      Serial.println(val);
      previousMillis=0;
    while(pin4status==0){         

    currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
            previousMillis = currentMillis;
            LoRa.beginPacket();
            LoRa.print(val);
            LoRa.endPacket();
            Serial.print("sending packet: ");
            Serial.println(val);
        }   
      
     pin4status = digitalRead(4); //delay(2000);
    }
   //============pin4 high
   previousMillis=0;
   countHigh=0;

   val=6;   
   LoRa.beginPacket();
   LoRa.print(val);
   LoRa.endPacket(); 
   Serial.print("sending packet: ");
   Serial.println(val);
   do{ 
        currentMillis = millis();
        if (currentMillis - previousMillis >= interval) {
            previousMillis = currentMillis;
            LoRa.beginPacket();
            LoRa.print(val);
            LoRa.endPacket();
            Serial.print("sending packet: ");
            Serial.println(val);
            countHigh++;
        }   
     }while(countHigh<=5);
    //===
  } 
  
  
  
delay(1);
counter++;
}
