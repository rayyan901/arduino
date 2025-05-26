#include <SoftwareSerial.h>
#define RE 13
SoftwareSerial mySerial(A1, A2); // RX, TX
SoftwareSerial mod(3, 2); // Software serial for RS485 communication
SoftwareSerial mod2(5, 4); // Software serial for RS485 communication
SoftwareSerial mod3(7, 6); // Software serial for RS485 communication
// Request frame for the soil sensor
const byte soilSensorRequest[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x02, 0xC4, 0x0B};
byte soilSensorResponse[9];

int var1 = 10;
int var2 = 20;
int var3 = 3;

int moisVal1=0,moisVal2=0, moisVal3=0;
//float   moisVal3=0;
unsigned long previousMillis = 0;        // will store last time LED was updated
const long interval = 180000;           // interval at which to blink (milliseconds)
// Define the digital output pin for the relay or LED
const int outputPin = 8;
const int moistureThreshold = 30; 
bool readErr=0;
void setup() {
  mySerial.begin(4800); // Set baud rate
  Serial.begin(115200); // For debugging (optional)
  pinMode(outputPin, OUTPUT);

  mod2.begin(4800);    // Initialize software serial communication at 4800 baud rate
   mod3.begin(4800);    // Initialize software serial communication at 4800 baud rate
    mod.begin(4800);    // Initialize software serial communication at 4800 baud rate
  pinMode(RE, OUTPUT); // Set RE pin as output

Serial.println("Moisture Sensor");
   moisVal1 = readMoisture();
   moisVal2 = readMoisture2();
   moisVal3 = readMoisture3();
}

void loop() {

  //==========

       // get the current time
  unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;   

    // yourFunction(); 
    while(mySerial.available()){mySerial.read();}
     
     moisVal1 = readMoisture();
          if(readErr==0){
     Serial.print("Sensor 1: ");
     Serial.println(moisVal1); 
     } else if(readErr==1){
      moisVal1=1;
      Serial.println("Sensor 1: Error");
     }

     moisVal2 = readMoisture2();
      if(readErr==0){
     Serial.print("Sensor 2: ");
     Serial.println(moisVal2); 
     } else if(readErr==1){
      moisVal2=1;
      Serial.println("Sensor 2: Error");
     } 

     //moisVal3 = readMoisture3();
     //Serial.println(moisVal3); 
      moisVal3 = readMoisture3();
      if(readErr==0){
     Serial.print("Sensor 3: ");
     Serial.println(moisVal3); 
     } else if(readErr==1){
      moisVal3=1;
      Serial.println("Sensor 3: Error");
     } 



    //Serial.println("Function called every 3 seconds"); 
     // Check if all sensor values are below the threshold===============================================================================
  if (moisVal1 < moistureThreshold && moisVal2 < moistureThreshold && moisVal3 < moistureThreshold && readErr!=1) {
    // If all sensors are below the threshold, set the output pin LOW
    digitalWrite(outputPin, LOW);  // Turn on the relay/LED (LOW usually means ON for relays)
    Serial.println("Soil is dry"); // Optional debug message
  } else {
    // If at least one sensor is above the threshold, set the output pin HIGH
    digitalWrite(outputPin, HIGH); // Turn off the relay/LED
    Serial.println("Soil is moist"); // Optional debug message
  }
  }

  //===========
   mySerial.listen();
   //delay(1000);
  if (mySerial.available() > 0) {
    char request = mySerial.read(); 
    if (request == 'r') { // Request received from ESP32
      // Send data to ESP32
      mySerial.print(moisVal1); 
      mySerial.print(","); 
      mySerial.print(moisVal2); 
      mySerial.print(","); 
      mySerial.println(moisVal3); 
      Serial.println("Data sent to ESP32"); // For debugging
    }
  }
  //-------------------
}

int readMoisture() {


  // Start the transmission mode for RS485
  float sensorVal;
  int mois=0;

  digitalWrite(RE, HIGH);
  delay(10);
  
   mod.listen();
    // Send the request frame to the soil sensor
  mod.write(soilSensorRequest, sizeof(soilSensorRequest));
 
  // End the transmission mode and set to receive mode for RS485

  digitalWrite(RE, LOW);
  delay(10);

// Wait for the response from the sensor or timeout after 1 second
  unsigned long startTime = millis();
  //mod.listen();
  while (mod.available() < 9 && millis() - startTime < 1000)
  {
    delay(1);
  }
  //mod.listen();
  if (mod.available() >= 9) // If valid response received
  {
    // Read the response from the sensor
    byte index = 0;
    //mod.listen();
    while (mod.available() && index < 9)
    {
      soilSensorResponse[index] = mod.read();
      //Serial.print(soilSensorResponse[index], HEX); // Print the received byte in HEX format
      //Serial.print(" ");
      index++;
    }
    //Serial.println();
 
    // Parse and calculate the Moisture value
    int Moisture_Int = int(soilSensorResponse[3] << 8 | soilSensorResponse[4]);
    float Moisture_Percent = Moisture_Int / 10.0;
    sensorVal = Moisture_Percent;
    // Serial.print("Moisture: ");
    // Serial.print(Moisture_Percent);
    // Serial.println(" %RH");
   
   readErr=0;
 
  }
  else
  {
    // Print error message if no valid response received
    Serial.println("Sensor timeout or incomplete frame");
    sensorVal=0;
    readErr=1;
  
  }
 mois = int(sensorVal);
return mois;  
}
//=================
int readMoisture2() {


  // Start the transmission mode for RS485
  float sensorVal;
  int mois=0;

  digitalWrite(RE, HIGH);
  delay(10);
  
   mod2.listen();
    // Send the request frame to the soil sensor
  mod2.write(soilSensorRequest, sizeof(soilSensorRequest));
 
  // End the transmission mode and set to receive mode for RS485

  digitalWrite(RE, LOW);
  delay(10);

// Wait for the response from the sensor or timeout after 1 second
  unsigned long startTime = millis();
  //mod.listen();
  while (mod2.available() < 9 && millis() - startTime < 1000)
  {
    delay(1);
  }
  //mod.listen();
  if (mod2.available() >= 9) // If valid response received
  {
    // Read the response from the sensor
    byte index = 0;
    //mod.listen();
    while (mod2.available() && index < 9)
    {
      soilSensorResponse[index] = mod2.read();
      //Serial.print(soilSensorResponse[index], HEX); // Print the received byte in HEX format
      //Serial.print(" ");
      index++;
    }
    //Serial.println();
 
    // Parse and calculate the Moisture value
    int Moisture_Int = int(soilSensorResponse[3] << 8 | soilSensorResponse[4]);
    float Moisture_Percent = Moisture_Int / 10.0;
    sensorVal = Moisture_Percent;
    // Serial.print("Moisture: ");
    // Serial.print(Moisture_Percent);
    // Serial.println(" %RH");
   
    readErr=0;
 
  }
  else
  {
    // Print error message if no valid response received
    Serial.println("Sensor timeout or incomplete frame");
    sensorVal=0;
    readErr=1;
  
  }
 mois = int(sensorVal);
return mois; 
//return sensorVal;  
}

//=================
int readMoisture3() {


  // Start the transmission mode for RS485
  float sensorVal;
  int mois=0;
  digitalWrite(RE, HIGH);
  delay(10);
  
   mod3.listen();
    // Send the request frame to the soil sensor
  mod3.write(soilSensorRequest, sizeof(soilSensorRequest));
 
  // End the transmission mode and set to receive mode for RS485

  digitalWrite(RE, LOW);
  delay(10);

// Wait for the response from the sensor or timeout after 1 second
  unsigned long startTime = millis();
  //mod.listen();
  while (mod3.available() < 9 && millis() - startTime < 1000)
  {
    delay(1);
  }
  //mod.listen();
  if (mod3.available() >= 9) // If valid response received
  {
    // Read the response from the sensor
    byte index = 0;
    //mod.listen();
    while (mod3.available() && index < 9)
    {
      soilSensorResponse[index] = mod3.read();
      //Serial.print(soilSensorResponse[index], HEX); // Print the received byte in HEX format
      //Serial.print(" ");
      index++;
    }
    //Serial.println();
 
    // Parse and calculate the Moisture value
    int Moisture_Int = int(soilSensorResponse[3] << 8 | soilSensorResponse[4]);
    float Moisture_Percent = Moisture_Int / 10.0;
    sensorVal = Moisture_Percent;
    // Serial.print("Moisture: ");
    // Serial.print(Moisture_Percent);
    // Serial.println(" %RH");
    readErr=0;
 
 
  }
  else
  {
    // Print error message if no valid response received
    Serial.println("Sensor timeout or incomplete frame");
    sensorVal=0;
    readErr=1;
  
  }
mois = int(sensorVal);
return mois; 
//return sensorVal;  
}

