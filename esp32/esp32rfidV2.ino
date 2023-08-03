/*	Project : Read Google Spread Sheet Data from ESP32	*/
/*Refer following video for complete project : https://youtu.be/0LoeaewIAdY*/


#include <WiFi.h>
#include <HTTPClient.h>
#include <SPI.h>
#include <MFRC522.h>

#include <Wire.h>

#define SS_PIN 21
#define RST_PIN 22
#define DOOR_PIN 2

MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::StatusCode status;


//sample action
void openDoor()
{
  digitalWrite(DOOR_PIN,HIGH);
  delay(2000);
  digitalWrite(DOOR_PIN,LOW);
}


/********************************************************************************/
//Things to change
const char * ssid = "rayyan_2.4GHz@unifi";
const char * password = "20rayyan14";
String GOOGLE_SCRIPT_ID = "AKfycbwwZ-P_OmiqOCtuG4agOnJvuJoVJptOUVG8H_I1c6Zo3er7PZH93SAvRWC2NFSSU58F";

const int sendInterval = 5000; 
/********************************************************************************/


String roomLoc="jaya1r5";
WiFiClientSecure client;



void setup() {
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
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
Serial.println(WiFi.localIP());  
Serial.println("Ready to go");
//testdrawstyles();
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
  //Serial.print(mfrc522.uid.uidByte[i], HEX);
  userid += String(mfrc522.uid.uidByte[i], HEX);
}
userid.toUpperCase();
Serial.print(" concat: ");
Serial.println(userid );



  
 
// #ifdef TERMINAL_NAME
//  pointerShift+=sprintf(url+pointerShift,"&terminal=%s",TERMINAL_NAME);
// #endif

  
Serial.println("----- ");
for ( size_t i=0; i < mfrc522.uid.size; i++)
{
  
  Serial.printf("%X",mfrc522.uid.uidByte[i]);
  
}

Serial.println("----- ");

  spreadsheet_comm(userid);
  delay(sendInterval);
}

void handleDataFromGoogle(String data)
{

  
  

    
  if(data.equalsIgnoreCase("beep"+roomLoc))
  {
    //beep(5);
     Serial.println("denied");
  }
  else if(data.equalsIgnoreCase("door"+roomLoc))
  {
    
    Serial.println("unlocked...");
    openDoor();
    
  }
}


void spreadsheet_comm(String userId) {
   HTTPClient http;
   String rfidUid="fahmi";
   String url="https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?value1="+userId;
   Serial.println(url);
	Serial.println("Making a request");
	http.begin(url.c_str()); //Specify the URL and certificate
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
	int httpCode = http.GET();
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
    }
	http.end();
}