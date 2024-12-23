
#include <HardwareSerial.h>
//HardwareSerial ESP32Serial2(2);



#define RXD2 34
#define TXD2 35



void setup() {
  // Note the format for setting a serial port is as follows: Serial2.begin(baud-rate, protocol, RX pin, TX pin);
  Serial.begin(9600);
  //Serial1.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial2.begin(9600,SERIAL_8N1,12,13);
  //ESPSerial2.begin(9600, SERIAL_8N1, 34, 35);
  Serial.println("Serial Txd is on pin: "+String(TX));
  Serial.println("Serial Rxd is on pin: "+String(RX));
  delay(5000);
}

void loop() { //Choose Serial1 or Serial2 as required
  while (Serial2.available()) {
    Serial.print(char(Serial2.read()));
  }
  Serial2.println("Hello, uno?");
  delay(1000);
}