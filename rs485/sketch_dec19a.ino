#include <Wire.h> 
#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h>
#include <HardwareSerial.h>
//#include <SoftwareSerial.h>

#define RE 14

// Request frame for the soil sensor
const byte soilSensorRequest[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x02, 0xC4, 0x0B};
byte soilSensorResponse[9];
//SoftwareSerial mod(34,35); // Software serial for RS485 communication


// OLED display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1 // Reset pin not used
#define SCREEN_ADDRESS 0x3C // I2C address for the 128x64 screen

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
    Serial.begin(9600);
    Serial.println(F("Starting"));
    Serial2.begin(4800, SERIAL_8N1, 34, 35);
    // mod.begin(4800);    // Initialize software serial communication at 4800 baud rate
  pinMode(RE, OUTPUT); // Set RE pin as output

    // Initialize OLED display
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;);
    }

    display.clearDisplay();
    display.display();

     // Display on OLED
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 0);
        display.print("Moisture Percentage:");
        display.setTextSize(2);
        display.setCursor(0, 20);
        display.print("67");
        display.print("%");
        display.display();


}

void loop() {

    float moisVal = readMoisture();
  
    Serial.print("Moisture: ");
    Serial.print(moisVal);
    Serial.println(" %RH");
   
 
  delay(1000); // Wait for a second before the next loop iteration
    delay(1);
}

float readMoisture() {


  // Start the transmission mode for RS485
  float sensorVal;
  digitalWrite(RE, HIGH);
  delay(10);

    // Send the request frame to the soil sensor
  Serial2.write(soilSensorRequest, sizeof(soilSensorRequest));
 
  // End the transmission mode and set to receive mode for RS485

  digitalWrite(RE, LOW);
  delay(10);

// Wait for the response from the sensor or timeout after 1 second
  unsigned long startTime = millis();
  while (Serial2.available() < 9 && millis() - startTime < 1000)
  {
    delay(1);
  }
 
  if (Serial2.available() >= 9) // If valid response received
  {
    // Read the response from the sensor
    byte index = 0;
    while (Serial2.available() && index < 9)
    {
      soilSensorResponse[index] = Serial2.read();
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








