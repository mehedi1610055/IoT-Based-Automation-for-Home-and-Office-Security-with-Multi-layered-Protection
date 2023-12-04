#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char *auth = "x3Py7TUrrTzKm6rRU54BOGEYTclQfJhl";
char *ssid = "InfinityStone";
char *password = "khalid1610038";
char *blynkserver          = "blynk-cloud.com";
unsigned int blynkport      = 8442;

int ldrPin = 5;
int ultrasonicPin = 4;    
int soundPin = 14;
int tempPin = 12;
int flamePin = 13;  
int gasPin = 15;  
int blinkPin = 2;

IPAddress station(192,168,1,15);
IPAddress server(192,168,1,20);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

int port = 2390;
WiFiServer tcpserver(port);
WiFiClient tcpclient; 

void setup(){
  
  //WiFi.mode(WIFI_STA);
  //WiFi.begin(ssid,password);
  WiFi.config(server,gateway,subnet);
  
  Blynk.connectWiFi(ssid, password);
  Blynk.config(auth,blynkserver,blynkport);
  Blynk.connect();
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

  tcpserver.begin();
  
  pinMode(ldrPin,OUTPUT);
  pinMode(ultrasonicPin,OUTPUT);
  pinMode(soundPin,OUTPUT);
  pinMode(tempPin,OUTPUT);
  pinMode(flamePin,OUTPUT);
  pinMode(gasPin,OUTPUT);
  pinMode(blinkPin,OUTPUT);
}

void CheckConnection(){    // check every 11s if connected to Blynk server
  if(!Blynk.connected()){
    Serial.println("Not connected to Blynk server"); 
    Blynk.connect();  // try to connect to server with default timeout
  }
  else{
    Serial.println("Connected to Blynk server");     
  }
}



void loop(){

  
  digitalWrite(ldrPin,LOW);
  digitalWrite(ultrasonicPin,LOW);
  digitalWrite(soundPin,LOW);
  digitalWrite(tempPin,LOW);
  digitalWrite(flamePin,LOW);
  digitalWrite(gasPin,LOW);
  
  
  if(tcpserver.hasClient()){
    tcpclient = tcpserver.available();  
    tcpclient.setNoDelay(1);

    digitalWrite(blinkPin,HIGH);
    delay(250);
    digitalWrite(blinkPin,LOW);
    delay(250);
    
    if(digitalRead(ldrPin) == 1){
      tcpclient.println("1");
    }
    if(digitalRead(ultrasonicPin) == 1){
      tcpclient.println("2");
    }
    if(digitalRead(soundPin) == 1){
      tcpclient.println("3");
    }
    if(digitalRead(tempPin) == 1){
      tcpclient.println("4");
    }
    if(digitalRead(flamePin) == 1){
      tcpclient.println("5");
    }
    if(digitalRead(gasPin) == 1){
      tcpclient.println("6");
    }
    if(digitalRead(ldrPin) != 1 && digitalRead(ultrasonicPin) != 1 && digitalRead(soundPin) != 1 && digitalRead(tempPin) != 1 && digitalRead(flamePin) != 1 && digitalRead(gasPin) != 1){
      tcpclient.println("0");
    }
    String message = tcpclient.readStringUntil('\r');
    Serial.println(message);
  }

  delay(500);

  Blynk.run();
}
