#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>

SoftwareSerial s(D7,D6);
const char* ssid     = "localhost.localdomain";
const char* password = "LOqvH1xY";

const char* host = "10.42.0.1";

int inPin = 12;
int lock_status;
String line ="";
void setup() {
  Serial.begin(115200);
  s.begin(9600);
  delay(10);
//  pinMode(device1,OUTPUT);
//  pinMode(device2,OUTPUT);
//  digitalWrite(device1,1);
//  digitalWrite(device2,1);
  // We start by connecting to a WiFi network
  pinMode(inPin,INPUT);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
       network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

int value = 0;

void loop() {
  delay(5000);
  ++value;

  Serial.print("connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  
  lock_status = digitalRead(inPin);
  Serial.println(lock_status);

  if(lock_status == HIGH){
    Serial.println("door locked");
    String url = "/iot/updateStatus.php?lock=on";

    Serial.print("Requesting URL: ");
    Serial.println(url);

   //This will send the request to the server
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
    Serial.println();
    Serial.println("closing connection");
  }
  
  else{
    Serial.println("door unlocked");
    String url = "/iot/updateStatus.php?lock=off";

    Serial.print("Requesting URL: ");
    Serial.println(url);

   //This will send the request to the server
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
 Serial.println();
 Serial.println("closing connection");
  }
      
//  String url = "/iot/checkStatus.php";
//
//  Serial.print("Requesting URL: ");
//  Serial.println(url);

  // This will send the request to the server
//  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
//               "Host: " + host + "\r\n" +
//               "Connection: close\r\n\r\n");
//  unsigned long timeout = millis();
//  while (client.available() == 0) {
//    if (millis() - timeout > 5000) {
//      Serial.println(">>> Client Timeout !");
//      client.stop();
//      return;
//    }
//  }
//
//  
//  while (client.available()) {
//    line = client.readStringUntil('\r');
//    Serial.print(line);
//  }
//  if(line.indexOf("forgot")!=-1){
//      Serial.println("something has been turned on");
//  }
//
//  Serial.println();
//  Serial.println("closing connection");
}
  
