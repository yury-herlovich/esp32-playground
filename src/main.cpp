#include <Arduino.h>
#include <WiFi.h>
#include <secrets.h>
#include <httpServer.h>
#include "blink.h"
#include <SPIFFS.h>
#include "pubsub.h"

void setup() {
  setupPin();
  Serial.begin(921600);

  Serial.println("Hello from the setup");

  delay(2000);

  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // connect to wifi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
}

bool IsConnected = false;

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    if (!IsConnected) {
      Serial.println("Connected to the WiFi network");
      Serial.println(WiFi.localIP());

      ledOn();
      IsConnected = true;


      startHttpServer();
      connectToMqtt();
    }

    listenConnections();
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println(".");
    switchLed();
    IsConnected = false;
    delay(500);
  }
}
