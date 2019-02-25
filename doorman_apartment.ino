#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <StepperMotorFork.h>
#include "Secrets.h"
/* Secrets.h contains:
const char* ssid = "WifiNetworkName";
const char* password = "WifiPassword";
*/
ESP8266WebServer server(80);
IPAddress ip(192, 168, 0, 51); // where xx is the desired IP Address
IPAddress gateway(192, 168, 0, 1); // set gateway to match your network. this is the ip address of your router.

StepperMotor motor(14,12,13,15);//the 4 pins going to stepper motor controller
int inPin = 5;//pin used for pushbutton input
bool locked = false;

void trigger(){
  if (!locked) {
      motor.step(-1280);
      locked = true;
      }
    else {
      motor.step(1280);
      locked = false;
      }
    delay(200);
}

void sendJSON(int code, String json) {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(code, "application/javascript", json);
}

String getLockedStatus(bool locked) {
  if (locked) {
    return "true";
  } else {
    return "false";
  }
}


void setup(void) {

  Serial.begin(115200);

  motor.setStepDuration(1);
  pinMode(inPin, INPUT);//input pin for stepper motor manual override
  
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
    sendJSON(200, "{\"alive\":\"true\"}\n");
  });

  server.on("/api/toggle", []() {
    sendJSON(200, "{\"success\":\"true\"}\n");
    trigger();
  });

  server.on("/api/status", []() {
    sendJSON(200, "{\"locked\":\""+ getLockedStatus(locked) + "\"}\n");
  });

  server.onNotFound( []() {
    sendJSON(404, "{\"error\":\"404\"}\n");
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  if (digitalRead(inPin) == HIGH) { //button is pushed    
    trigger();
  }
}
