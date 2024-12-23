#include <SoftwareSerial.h>

#define RE 8

// Request frame for the soil sensor
const byte soilSensorRequest[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x02, 0xC4, 0x0B};
byte soilSensorResponse[9];
SoftwareSerial mod(2, 3); // Software serial for RS485 communication

 
void setup()
{
  Serial.begin(9600); // Initialize serial communication for debugging
  mod.begin(4800);    // Initialize software serial communication at 4800 baud rate
  pinMode(RE, OUTPUT); // Set RE pin as output

}

void loop()
{
  float moisVal = readMoisture();
  
    Serial.print("Moisture: ");
    Serial.print(moisVal);
    Serial.println(" %RH");
   
 
  delay(1000); // Wait for a second before the next loop iteration
}


float readMoisture() {


  // Start the transmission mode for RS485
  float sensorVal;
  digitalWrite(RE, HIGH);
  delay(10);

    // Send the request frame to the soil sensor
  mod.write(soilSensorRequest, sizeof(soilSensorRequest));
 
  // End the transmission mode and set to receive mode for RS485

  digitalWrite(RE, LOW);
  delay(10);

// Wait for the response from the sensor or timeout after 1 second
  unsigned long startTime = millis();
  while (mod.available() < 9 && millis() - startTime < 1000)
  {
    delay(1);
  }
 
  if (mod.available() >= 9) // If valid response received
  {
    // Read the response from the sensor
    byte index = 0;
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
   
 
 
  }
  else
  {
    // Print error message if no valid response received
    Serial.println("Sensor timeout or incomplete frame");
    sensorVal=0;
  
  }

return sensorVal;  
}

















