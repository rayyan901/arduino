/*************************************************************

  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

/* Fill-in information from Blynk Device Info here */
// #define BLYNK_TEMPLATE_ID           "TMPL6IrMvYMoe"
// #define BLYNK_TEMPLATE_NAME         "Quickstart Template"
// #define BLYNK_AUTH_TOKEN            "PO4wblaEKupxDLHJ0MwOZhKvF9I9Wjmf"

#define BLYNK_TEMPLATE_ID "TMPL6qdlqDP8r"
#define BLYNK_TEMPLATE_NAME "Smart Farm"
#define BLYNK_AUTH_TOKEN "_RnmM_IkIwdSSZtyDk8b8dnjceKxci2A"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

//define the pins used by the LoRa transceiver module
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO0 26

//433E6 for Asia
//866E6 for Europe
//915E6 for North America
#define BAND 433E6

//OLED pins
// #define OLED_SDA 4
// #define OLED_SCL 15 
#define OLED_RST -1
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SCREEN_ADDRESS 0x3C // I2C address for the 128x64 screen



#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

//Libraries for OLED Display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

int counter = 0;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Pixel6";
char pass[] = "1234abcd";

BlynkTimer timer;

//This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V1)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();
  
  if (value==1){
    Blynk.virtualWrite(V0, counter);
  }
  // Update state
  //Blynk.virtualWrite(V1, value);
}

//This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V2)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();
  
  if (value==1){
    Serial.println("Buka");
  display.clearDisplay();
  //display.setCursor(0,0);
 
  //display.setTextSize(2);
  
  
  display.setCursor(50,30);
  display.print("Buka");        
  display.display();
 
  } else{
    Serial.println("Tutup");
  display.clearDisplay();
  display.setCursor(50,30);
  display.print("Tutup");        
  display.display();
  
  }
  // Update state
  //Blynk.virtualWrite(V1, value);
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // // Change Web Link Button message to "Congratulations!"
  // Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  // Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  // Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
  
  Serial.println("Online!");
  display.clearDisplay();
  display.setCursor(0,0);
 
  display.setTextSize(2);
  
  display.print("Online!");
  display.display();
  //delay(2000);
  //display.clearDisplay();
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V0, counter); //millis() / 1000);
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void my1secondTimerEvent()
{
  display.clearDisplay();
  display.setCursor(0,0);
 
  display.setTextSize(2);
  
  display.print("Num: ");
  //display.setCursor(50,0);
  display.print(counter);      
  display.display();

  counter++;
  if(counter>255){
    counter=0;
  }
}



void setup()
{
  // Debug console
  Serial.begin(115200);

  // Initialize with the I2C address 0x3D (for the LilyGO LoRa32 433MHz)
  if(!display.begin(0x3D, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  // Initialize with the SSD1306_128_64 switch
  display.display();
  delay(2000);  // Pause for 2 seconds

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(0,0);
  display.print("Smart Farm");
  display.display();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(20000L, myTimerEvent);
  timer.setInterval(5000L, my1secondTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}
