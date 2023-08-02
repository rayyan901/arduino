#include <WiFi.h>
#include <WiFiClientSecure.h>

const char* ssid = "rayyan_2.4GHz@unifi";//"pixel6";                //tukar
const char* password = "20rayyan14";        //tukar
const char* host = "script.google.com";        
String SCRIPT_ID = "AKfycbyzj5gOLRrl0CKbtC6Cx8BoWtIVE5k37gTffkmsjUppo6moAffirIJt2UjzpLIhYtej0Q"; //tukar

WiFiClientSecure client;

int temperature; 
int humidity;  

void setup() {
  //SETUP SERIAL MONITOR COMMUNICATIONS
  Serial.begin(9600);

  //SETUP WIFI CONNECTION
  Serial.println();
  Serial.print("Connecting to WiFi ");
  Serial.println(ssid);

  //INITIALIZE WIFI RADIO
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  //CONNECT WIFI
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
    
}//END VOID SETUP

void loop() {
/*************SIMULASI SENSOR*****************/  
temperature = random(25, 38); //simulasi temperature dengan random nombor 25-38
humidity = random(55, 83);    //simulasi humidty dengan random nombor 55-83

/*************PENGHANTARAN DATA*****************/  
sendToGoogleSheets();  

//DELAY UNTUK TIDAK FLOODING SERVER 
delay(10000);
  
}//END VOID LOOP


void sendToGoogleSheets(){
  //SET CONNECTION TO INSECURE HTTPS
  client.setInsecure();

  //CONNECT TO HOST SERVER
  Serial.print("Connecting to ");
  Serial.println(host);
  
  if (!client.connect(host, 443)) {      // HTTPS Connection pada Port 443
    Serial.println("Connection failed");
    return;                              //Stop Process jika connection failed
  }

  //SET STRING UNTUK DATA
  String data1 = "ashraf";
  String data2 = "76af43";
  String data3 = String(temperature); //convert temperature kepada format data String
  String data4 = String(humidity);    //convert humidity kepada format data String
  
  //KOMBINASI SEMUA DATA DALAM 1 STRING
  String data = "value1="+data1+"&value2="+data2+"&value3="+data3+"&value4="+data4;

  //SET STRING URL UNTUK REQUEST
  String url = "/macros/s/" + SCRIPT_ID + "/exec?" + data;
  Serial.print("Requesting URL: ");
  Serial.println(url);

  //HANTAR GET API Request
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +            
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  Serial.println("Request sent");
  delay(300);

  //==
  // while(client.available()){
  //   String line = client.readStringUntil('\r');
  //   Serial.print(line);
  // }

 
  client.stop(); //DISCONNECT HTTPS connection (Wajib Disconnect)
}//END sendToGoogle