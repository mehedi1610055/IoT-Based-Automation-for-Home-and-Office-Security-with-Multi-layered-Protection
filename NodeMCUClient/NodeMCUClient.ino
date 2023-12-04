#include <ESP8266WiFi.h>

char *ssid = "InfinityStone";
char *password = "khalid1610038";
int buzzerPin = 5;

IPAddress station(192,168,1,19);
IPAddress server(192,168,1,20);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

int port = 2390;
WiFiClient tcpclient;
  
void setup(){

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);
  WiFi.config(station,gateway,subnet);

  Serial.begin(115200);
  Serial.print("Connecting to WiFi");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  if(WiFi.status() == WL_CONNECTED){
    Serial.println("");
    Serial.println("<<<WiFi Connected>>>");
  }

  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("RSSI: ");
  Serial.println(WiFi.RSSI());
  pinMode(buzzerPin,OUTPUT);
}


void loop(){
  String message = "0";
  if(tcpclient.connect(server,port)){
    tcpclient.setNoDelay(1);
    message = tcpclient.readStringUntil('\r');
    Serial.print("Received: ");
    Serial.println(message);
    tcpclient.println("Delivered: " + message);
    digitalWrite(16,HIGH);
    delay(100);
    digitalWrite(16,LOW);
    delay(100);
    if(message[0] == '0'){
      
    }
    if(message[0] == '1'){
        tone(buzzerPin,1000,400);
        delay(400);
        tone(buzzerPin,2500,200);
        delay(200);
        tone(buzzerPin,1000,200);
        delay(200);
        tone(buzzerPin,2500,200);
        delay(200);
        tone(buzzerPin,1000,200);
        delay(200);
    }
    if(message[0] == '2'){
        tone(buzzerPin,3000,300);
        delay(200);
        tone(buzzerPin,1000,200);
        delay(200);
        tone(buzzerPin,1500,200);
        delay(200);
        tone(buzzerPin,1000,200);
        delay(200);
    }
    if(message[0] == '3'){
        tone(buzzerPin,1000,200);
        delay(400);
        tone(buzzerPin,1500,200);
        delay(200);
        tone(buzzerPin,2500,200);
        delay(200);
        tone(buzzerPin,1500,200);
        delay(200);

    }
    if(message[0] == '4'){
        tone(buzzerPin,3000,200);
        delay(200);
        tone(buzzerPin,2000,200);
        delay(200);
        tone(buzzerPin,1000,200);
        delay(200);
    }
    if(message[0] == '5'){
        tone(buzzerPin,1500,200);
        delay(200);
        tone(buzzerPin,2000,200);
        delay(200);
        tone(buzzerPin,2500,200);
        delay(200);
        tone(buzzerPin,3000,200);
        delay(200);
    }
    if(message[0] == '6'){
        tone(buzzerPin,3000,200);
        delay(200);
        tone(buzzerPin,2500,200);
        delay(200);
        tone(buzzerPin,2000,200);
        delay(200);
        tone(buzzerPin,1500,200);
        delay(200);
    }
  }

}
