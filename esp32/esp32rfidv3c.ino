
#include <WiFi.h>
#include <HTTPClient.h>
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <EEPROM.h>
#define EEPROM_SIZE 35

#define SS_PIN 4
#define RST_PIN 5
#define DOOR_PIN 2

MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::StatusCode status;
LiquidCrystal_I2C lcd(0x27,16,2); 



/********************************************************************************/
//Things to change
const char * ssid = "pixel6";  //"rayyan_2.4GHz@unifi";
const char * password = "1234abcd";  //"20rayyan14";
String GOOGLE_SCRIPT_ID = "AKfycbwmH4rXKiUGzJEZLpwN1Pa1FFO05Z3TQmkb84F0JozgOGlH0WJwbAApZk3qQlM01Kwm";

const int sendInterval = 2000; 
/********************************************************************************/
 
String roomLoc="jaya1r5";
String userid;
int eepromOffset = 0;
int eepromOffset2 = 16;

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
 EEPROM.begin(EEPROM_SIZE);
   
   //===
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
  int j=0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    Serial.println(j);
    j++;
    if(j>60){
      Serial.println("wifi not connected, timeout");
      Serial.println("please scan RFID tag");
      lcd.clear();  
  lcd.setCursor(0,0);   //Set cursor to character 0 on line 0
  lcd.print("WiFi Failed");
  lcd.setCursor(0,1);   //Set cursor to character 0 on line 0
  lcd.print("Scan RFID Tag");
      break;
    }
  }
  if(WiFi.status() == WL_CONNECTED){
Serial.println(WiFi.localIP());  
Serial.println("Connected to WiFi");
 //=====
  lcd.clear();  
  lcd.setCursor(0,0);   //Set cursor to character 0 on line 0
  lcd.print("WiFi Connected");
  lcd.setCursor(0,1);   //Set cursor to character 0 on line 0
  lcd.print("RFID Scan Ready");
  }
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


String RFuserid;
for (byte i = 0; i < mfrc522.uid.size; i++) {
  
  RFuserid += String(mfrc522.uid.uidByte[i], HEX);
}
RFuserid.toUpperCase();
userid=RFuserid;
Serial.print("rfid uid: ");
Serial.println(userid );
  
Serial.println("----- ");

Serial.println("----- ");
//=====
  lcd.clear();  
  lcd.setCursor(2,0);   //Set cursor to character 2 on line 0
  lcd.print(userid);
//======
if(WiFi.status() == WL_CONNECTED){
  connectToGoogle(userid);
} else {
  checkAccEeprom(userid);
}
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
      Serial.println(httpCode);
      Serial.println("Error on HTTP request");
           //=====
      lcd.clear();  
      lcd.setCursor(0,0);   //
      lcd.print("Error on");
      lcd.setCursor(0,1);   //
      lcd.print("HTTP request");
      checkAccEeprom(userid);
      delay(3000);
    }
      http.end();

//=================================================  
}

void handleDataFromGoogle(String data)
{
  String uid1;
  String uid2;
  
  String data1;
  String data2;

  char input_string1[25]; /*String length defined*/
  char input_string2[10]; /*String length defined*/

  char buffer[35];
  data.toCharArray(buffer, data.length() + 1);
  sscanf(buffer, "%[^#]#%s" , input_string1,input_string2); /*sscanf function is used to read input string*/

  data1=input_string1;
  data2=input_string2;


  //=============================

  if(data1.equalsIgnoreCase("no"+roomLoc))
  {
    //beep(5);
     Serial.println("denied");
      //=====
  lcd.clear();  
  lcd.setCursor(0,0);   //
  lcd.print("access denied!");
  checkInEeprom(userid);
  delay(3000);
//======
  }
  else if(data1.equalsIgnoreCase("yes"+roomLoc))
  {
    
    Serial.println("unlocked...");
     //=====
  lcd.clear();  
  lcd.setCursor(0,0);   //
  lcd.print("access granted");
//======
  openDoor();
  //check eeprom
     readStringFromEEPROM(eepromOffset, &uid1);
     readStringFromEEPROM(eepromOffset2, &uid2);

     Serial.print("eeprom1: ");
     Serial.println(uid1);
     
     Serial.print("eeprom2: ");
     Serial.println(uid2);
    
    if(data2.equalsIgnoreCase("user1")){
      Serial.println("trying to write eeprom");
      if(userid!=uid1){
        //write to add 1
        Serial.print("writing eeprom user1 with: ");
        Serial.println(userid);
         writeStringToEEPROM(eepromOffset, userid);
         EEPROM.commit();
        //int str2AddrOffset = writeStringToEEPROM(str1AddrOffset, str2);
      }

    }else if(data2=="user2"){
      if(userid!=uid2){
        //write to add 2
         Serial.print("writing eeprom user2 with: ");
         Serial.println(userid);
         writeStringToEEPROM(eepromOffset2, userid);
         EEPROM.commit();
      }

      }

   


  //==
    
  } else {
    lcd.clear();  
    lcd.setCursor(0,0);   //
    lcd.print("ID not found");
    checkInEeprom(userid);
    delay(3000);

  }
}

void checkInEeprom(String exId){

  String uid1;
  String uid2;
  String resetId = "87000000";
     readStringFromEEPROM(eepromOffset, &uid1);
     readStringFromEEPROM(eepromOffset2, &uid2);

     if(exId.equalsIgnoreCase(uid1)){
       //reset
       writeStringToEEPROM(eepromOffset, resetId);
       EEPROM.commit();

     } else if(exId.equalsIgnoreCase(uid2)){
       //reset
       writeStringToEEPROM(eepromOffset2, resetId);
       EEPROM.commit();

     }

}

void checkAccEeprom(String userid){

  String uid1;
  String uid2;
 // String resetId = "87000000";
     readStringFromEEPROM(eepromOffset, &uid1);
     readStringFromEEPROM(eepromOffset2, &uid2);

     if(userid.equalsIgnoreCase(uid1)){
       //reset
          Serial.println("unlocked from eeprom...");
     //=====
  lcd.clear();  
  lcd.setCursor(0,0);   //
  lcd.print("access granted");
  lcd.setCursor(0,1);   //
  lcd.print("from eeprom");
       openDoor();

     } else if(userid.equalsIgnoreCase(uid2)){
       //reset
        Serial.println("unlocked from eeprom...");
     //=====
  lcd.clear();  
  lcd.setCursor(0,0);   //
  lcd.print("access granted");
  lcd.setCursor(0,1);   //
  lcd.print("from eeprom");
       openDoor();

     }

}
void openDoor()
{
  digitalWrite(DOOR_PIN,HIGH);
  delay(2000);
  digitalWrite(DOOR_PIN,LOW);
}


int writeStringToEEPROM(int addrOffset, const String &strToWrite)
{
  byte len = strToWrite.length();
  EEPROM.write(addrOffset, len);
  for (int i = 0; i < len; i++)
  {
    EEPROM.write(addrOffset + 1 + i, strToWrite[i]);
  }
  return addrOffset + 1 + len;
}
int readStringFromEEPROM(int addrOffset, String *strToRead)
{
 

  int newStrLen = EEPROM.read(addrOffset);

  if (newStrLen > 16) {
     newStrLen  = 5;
  }

  char data[newStrLen + 1];



  for (int i = 0; i < newStrLen; i++)
  {
    data[i] = EEPROM.read(addrOffset + 1 + i);
     
  }
  data[newStrLen] = '\0'; // !!! NOTE !!! Remove the space between the slash "/" and "0" (I've added a space because otherwise there is a display bug)
  *strToRead = String(data);
  return addrOffset + 1 + newStrLen;
}