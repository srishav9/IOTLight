/*
    This sketch sends data via HTTP GET requests to data.sparkfun.com service.

    You need to get streamId and privateKey at data.sparkfun.com and paste them
    below. Or just customize this script to talk to other HTTP servers.

*/

#include <ESP8266WiFi.h>

const char* ssid     = "localhost.localdomain";
const char* password = "LOqvH1xY";

const char* host = "10.42.0.1";
//const char* streamId   = "....................";
//const char* privateKey = "....................";

int device1 = 2;//d4
int device2 = 0;//d3
String line ="";
void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(device1,OUTPUT);
  pinMode(device2,OUTPUT);
  digitalWrite(device1,1);
  digitalWrite(device2,1);
  // We start by connecting to a WiFi network

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

  // We now create a URI for the request
  String url = "/iot/readFromServer.php";
//  url += streamId;
//  url += "?private_key=";
//  url += privateKey;
//  url += "&value=";
//  url += value;//

  Serial.print("Requesting URL: ");
  Serial.println(url);

  // This will send the request to the server
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

  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    line = client.readStringUntil('\r');
    Serial.print(line);
  }
  if(line.indexOf("device_one_on")!=-1){
      Serial.println("THE LIGHT IS ON");
      digitalWrite(device1,0);
      //digitalWrite(lamp2,0);
    }
 
   if(line.indexOf("device_one_off")!=-1){
      Serial.println("THE LIGHT IS OFF");
      digitalWrite(device1,1);
      //digitalWrite(lamp2,1);
    }
    if(line.indexOf("device_two_on")!=-1){
      Serial.println("THE LIGHT IS ON");
      digitalWrite(device2,0);
      //digitalWrite(lamp2,1);
    }
    if(line.indexOf("device_two_off")!=-1){
      Serial.println("THE LIGHT IS OFF");
      digitalWrite(device2,1);
      //digitalWrite(lamp2,1);
    }

  Serial.println();
  Serial.println("closing connection");
}
