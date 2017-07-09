#include <WiFi.h>
#include <WiFiClient.h>
#include "ESP32WebServer.h"
#include <ESPmDNS.h>

const char* ssid = "........";
const char* password = "........";

ESP32WebServer server(80);

#define pinLED    5

void setup(void){
  pinMode(pinLED, OUTPUT);
  digitalWrite(pinLED, LOW);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/control", HTTP_GET, handleControl);
  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });  
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}

/*
 * hanler for http resuest
 * each handler must send string to client in order to close the client connection
 */

void handleRoot() {
  digitalWrite(pinLED, 1);
  server.send(200, "text/plain", "hello from esp32!");
  digitalWrite(pinLED, 0);
}

void handleControl() 
{
  String led = server.arg("led");
  String status = server.arg("status");

  if (led != "")
  {
    Serial.print("led="); Serial.println(led);
  }

  if (status != "")
  {
    Serial.print("status="); Serial.println(status);  
  }
  
  if (led=="0") {
      if (status=="on") {
        digitalWrite(pinLED,HIGH);
        server.send(200, "text/plain", "LED on"); 
      } else
      if (status=="off") {
        digitalWrite(pinLED,LOW);
        server.send(200, "text/plain", "LED off"); 
      } else {
        server.send(200, "text/plain", "invalid LED status"); 
      }
  } else {
      server.send(200, "text/plain", "undefined LED number"); 
  }
}

void handleNotFound(){
  digitalWrite(pinLED, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(pinLED, 0);
}
