#include <SPI.h>
#include <LoRa.h>


unsigned long previousMillis = 0; 
const long interval = 2000; 
void setup() {

  //pinMode(13, OUTPUT);
 
  pinMode(4, OUTPUT);
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Receiver");

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

char rBuff[20]; 
int val=0;
int counter=0;
int sec=0;
void loop() {

 unsigned long currentMillis; // = millis();
  
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet: ");
    Serial.print(packetSize);
    Serial.print(" ...'");

    // read packet
    int i=0;
    while (LoRa.available()) {

      rBuff[i]=(char)LoRa.read();
      //rBuff += (char)LoRa.read();
      i++;
      //Serial.print((char)LoRa.read());
    }
    rBuff[i]='\0';
    //=====
//  LoRa.beginPacket();
//  LoRa.print(rBuff[0]);
//  LoRa.endPacket();
    //===
    Serial.print(rBuff);
    //val=rBuff.toInt();
    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());

    if(rBuff[0]=='5'){

     
    
     Serial.println("buka");
     digitalWrite(4, HIGH); 
      
    } else if(rBuff[0]=='6'){
       
       Serial.println("tutup");
       digitalWrite(4, LOW);
       
    }
  }
  //============
    currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
    
    previousMillis = currentMillis;

   Serial.print("time: ");
    Serial.println(sec);
    sec++;

    
  }
  
  //=========
}
