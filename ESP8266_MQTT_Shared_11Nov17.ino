#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h> 
//#include <LiquidCrystal_I2C.h>  
//LiquidCrystal_I2C lcd(0x27, 20, 4);
const char* ssid = "infamous";//******************************************************CHANGE
const char* password = "xboxone6081";//**************************************************CHANGE
const char* mqtt_server = "broker.mqttdashboard.com";//**************************************Use this or your own
const byte ledRed = D6;
const byte horn = D7;
int button = D4;
int press = 0;
boolean buttonToggle = true;


WiFiClient espClient;
PubSubClient client(espClient);
bool toggle = false;
void setup_wifi() {
  delay(100);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length)
{
  if (length > 0) {
    toggle = true;
  }

  if (length == 0) {
    toggle = false;
  }

  Serial.print("Command from MQTT broker is : [");
  Serial.print(topic);

  Serial.println();
  Serial.print(" publish data is:");
  //lcd.clear();
  {
    // for(int i=0;i<length;i++)
    for (int i = 0; i < length; i++)
    {
      Serial.print((char)payload[i]);
  //    lcd.setCursor(0, 0);
    //  lcd.setCursor(i, 0);
      //lcd.write((char)payload[i]);
    }
  }


  Serial.println();
} 

void reconnect() {
  
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    
    String clientId = "mqttdash-054468c4";//******************************************************CHANGE
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str()))
    {
      Serial.println("connected");

      client.subscribe("textdisp");//********************************************************CHANGE TO MATCH ENTRY IN MQTT DASH TOPIC
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(6000);
    }
  }
} 

void setup() {
  Serial.begin(115200);
  pinMode(button, INPUT);
  digitalWrite(D4, HIGH);
  pinMode(ledRed, OUTPUT);
  digitalWrite(ledRed, LOW);
  pinMode(horn, OUTPUT);
  digitalWrite(horn, LOW);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
//  lcd.init(); 
//  lcd.backlight();
}

void loop() {

  
  if (!client.connected()) {
    reconnect();
  }
  if (toggle == true) {
    digitalWrite(ledRed, HIGH);
    digitalWrite(horn, HIGH);
    delay(200);
    digitalWrite(ledRed, LOW);
    digitalWrite(horn, LOW);
    delay(200);
  }
  if (toggle == false) {
    digitalWrite(ledRed, LOW);
    digitalWrite(horn, LOW);

  }

  client.setCallback(callback);
  client.loop();

  press = digitalRead(button);
  if (press == LOW)
  {
    if (buttonToggle)
    {
      digitalWrite(ledRed, HIGH);
      digitalWrite(horn, HIGH);
      buttonToggle = !buttonToggle;
    }
    else
    {
      digitalWrite(ledRed, LOW);
      digitalWrite(horn, LOW);
      buttonToggle = !buttonToggle;
      toggle = false;
      //lcd.clear();
    }
  }
  delay(500);  //delay for debounce
}
