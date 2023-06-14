#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

const char* host = "script.google.com";
const int httpsPort = 443;
const char* fingerprint  = "46 B2 C3 44 9C 59 09 8B 01 B6 F8 BD 4C FB 00 74 91 2F EF F6"; // for https

float data1=61.25,data2=62.89,data3=63.54,data4=64.0;

const char* ssid = "viewsonic";
const char* password = "1234abcd";
String GOOGLE_SCRIPT_ID = "AKfycbwWLfPuAej97RA_gByfKv7Wbw43oQ95RAYQHwsIQyek11cTxBhWxioRiBOciNA1EbZRTQ"; // Replace by your GAS service id
const String unitName = "headquarter"; // any name without spaces and special characters
WiFiClientSecure client;

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200); 

 WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.println("Started");
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
}
}
void loop() {
  // put your main code here, to run repeatedly:
  sendData("value1",NULL);
  delay(10000);

}

String sendData(String params, char* domain) {
  //google scripts requires two get requests 
  bool needRedir = false;

  if (domain == NULL)
  {
    domain=(char*)host;
    needRedir = true;
    params = "/macros/s/" + GOOGLE_SCRIPT_ID + "/exec?" + params;
    params = params +"="+data1;
    params = params+ "&value2" + "="+data2;
    params = params+ "&value3" + "="+data3;
    params = params+ "&value4" + "="+data4;
  }
  
  Serial.println(params);
  Serial.println(*domain);
  String result = "";
  client.setInsecure();
  Serial.print("connecting to ");
  Serial.println(host);
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return "";
  }

  if (client.verify(fingerprint, domain)) {
  }

  Serial.print("requesting URL: ");
  Serial.println(params);

  client.print(String("GET ") + params + " HTTP/1.1\r\n" +
    "Host: " + domain + "\r\n" +
    "Connection: close\r\n\r\n");

  Serial.println("request sent");
  while (client.connected()) {

    String line = client.readStringUntil('\n');
    //Serial.println(line);
    if (needRedir) {

    int ind = line.indexOf("/macros/echo?user");
    if (ind > 0)
    {
      Serial.println(line);
      line = line.substring(ind);
      ind = line.lastIndexOf("\r");
      line = line.substring(0, ind);
      Serial.println(line);
      result = line;
    }
    }

    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  while (client.available()) {
    String line = client.readStringUntil('\n');
    if(!needRedir)
    if (line.length() > 5)
      result = line;
    //Serial.println(line);
    
    }
  if (needRedir)
    return sendData(result, "script.googleusercontent.com");
  else return result;
  

}
