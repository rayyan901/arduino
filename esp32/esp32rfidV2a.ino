
#include <WiFi.h>
#include <HTTPClient.h>
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define SS_PIN 4
#define RST_PIN 5
#define DOOR_PIN 2

MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::StatusCode status;
LiquidCrystal_I2C lcd(0x27,16,2); 



/********************************************************************************/
//Things to change
const char * ssid = "pixel6";
const char * password = "1234abcd";
String GOOGLE_SCRIPT_ID = "AKfycby2JH6gL1kB9mnlmLvBMCvs_gsCDIxo4mvZUFg__WMhNYg0VR8v-uvl7-TF30HHS2bH";

const int sendInterval = 2000; 
/********************************************************************************/
 
String roomLoc="jaya1r5";

void setup() {
//=========
  lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  
  // Print a message on both lines of the LCD.
  lcd.setCursor(2,0);   //Set cursor to character 2 on line 0
  lcd.print("Online");
  
  lcd.setCursor(2,1);   //Move cursor to character 2 on line 1
  lcd.print("RFID");
  delay(2000);
//===========
  Serial.begin(115200);
  delay(10);

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally

  pinMode(DOOR_PIN, OUTPUT);

  SPI.begin();        // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.println("Started");
  Serial.print("Connecting");
  //=====
  lcd.clear();  
  lcd.setCursor(2,0);   //Set cursor to character 2 on line 0
  lcd.print("Connecting...");
//======
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
Serial.println(WiFi.localIP());  
Serial.println("Connected to WiFi");
 //=====
  lcd.clear();  
  lcd.setCursor(0,0);   //Set cursor to character 0 on line 0
  lcd.print("WiFi Connected");
  lcd.setCursor(0,1);   //Set cursor to character 0 on line 0
  lcd.print("RFID Scan Ready");
//======

}

void loop() {

  if (!mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }

  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  //=====


String userid;
for (byte i = 0; i < mfrc522.uid.size; i++) {
  
  userid += String(mfrc522.uid.uidByte[i], HEX);
}
userid.toUpperCase();
Serial.print("rfid uid: ");
Serial.println(userid );
  
Serial.println("----- ");

Serial.println("----- ");
//=====
  lcd.clear();  
  lcd.setCursor(2,0);   //Set cursor to character 2 on line 0
  lcd.print(userid);
//======

  connectToGoogle(userid);
  Serial.println("waiting for next scan...");

  //=====
  lcd.clear();  
  lcd.setCursor(2,0);   //Set cursor to character 2 on line 0
  lcd.print("next scan...");
//======
  delay(sendInterval);
}



void connectToGoogle(String userId) {
   
   HTTPClient http;
   
   String url="https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?value1="+userId;
   Serial.println(url);
   Serial.println("Making a request"); 
   
      lcd.setCursor(0,1);   //
      lcd.print("Sending request");

   http.begin(url.c_str()); //Specify the URL
   http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
   int httpCode = http.GET();
//=============================================
   String payload;
    if (httpCode > 0) { //Check for the returning code
        payload = http.getString();
        
        Serial.print("httpCode: ");
        Serial.println(httpCode);
        Serial.println(payload);
        if (httpCode == 200) {
          handleDataFromGoogle(payload);
        }
      }
    else {
      Serial.println("Error on HTTP request");
           //=====
      lcd.clear();  
      lcd.setCursor(0,0);   //
      lcd.print("Error on");
      lcd.setCursor(0,1);   //
      lcd.print("HTTP request");
    }
      http.end();

//=================================================  
}

void handleDataFromGoogle(String data)
{
    
  if(data.equalsIgnoreCase("no"+roomLoc))
  {
    //beep(5);
     Serial.println("denied");
      //=====
  lcd.clear();  
  lcd.setCursor(0,0);   //
  lcd.print("access denied!");
  delay(3000);
//======
  }
  else if(data.equalsIgnoreCase("yes"+roomLoc))
  {
    
    Serial.println("unlocked...");
     //=====
  lcd.clear();  
  lcd.setCursor(0,0);   //
  lcd.print("access granted");
//======
    openDoor();
    
  } else {
    lcd.clear();  
    lcd.setCursor(0,0);   //
    lcd.print("ID not found");
    delay(3000);

  }
}


void openDoor()
{
  digitalWrite(DOOR_PIN,HIGH);
  delay(2000);
  digitalWrite(DOOR_PIN,LOW);
}
