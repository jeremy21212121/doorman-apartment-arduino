#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>


#include "Secrets.h"
/* Secrets.h contains:
const char* ssid = "WifiNetworkName";
const char* password = "WifiPassword";
*/


ESP8266WebServer server(80);
IPAddress ip(192, 168, 0, 50); // where xx is the desired IP Address
IPAddress gateway(192, 168, 0, 1); // set gateway to match your network. this is the ip address of your router.

const int relayPin = D7;

//void handleRoot() {
//  server.send(200, "application/javascript", "{\"alive\":true}");
//  }

void toggleRelay() {
    digitalWrite(relayPin, HIGH);
    delay(100);
    digitalWrite(relayPin, LOW);
    delay(75);
    digitalWrite(relayPin, HIGH);
    delay(100);
    digitalWrite(relayPin, LOW);
  }
void handleNotFound() {
  
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  
}

void setup(void) {
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  IPAddress subnet(255, 255, 255, 0); // set subnet mask to match your network
  WiFi.config(ip, gateway, subnet);
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


  server.on("/", []() {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "application/javascript", "{\"alive\":true}");
  });

  server.on("/api/toggle", []() {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "application/javascript", "{\"success\":true}");
    toggleRelay();
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
}
