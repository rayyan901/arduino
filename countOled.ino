#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using I2C
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(3,INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  // initialize the OLED object
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
 // Clear the buffer.
  display.clearDisplay();

  // set Text size
  display.setTextSize(2);
  display.setTextColor(WHITE);

  display.setCursor(0,0);
  display.print("0123456789");
  display.display();
  delay(2000);

}
int i=0;
void loop() {
  
  bool touch;
  // put your main code here, to run repeatedly:
  

  while(!digitalRead(3));
  touch=digitalRead(3);
  digitalWrite(LED_BUILTIN, touch);
    i++;
  Serial.print("counter: ");
  Serial.println(i);


  display.clearDisplay();

  display.setCursor(0,20);
  display.print(i);
  display.display(); 

  while(digitalRead(3));
  touch=digitalRead(3);
  digitalWrite(LED_BUILTIN, touch);
     // turn the LED on (HIGH is the voltage level)
  delay(20);                       // wait for a second




}
