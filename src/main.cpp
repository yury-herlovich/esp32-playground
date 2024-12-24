#include <Arduino.h>
#include <WiFi.h>
#include <secrets.h>
#include <httpServer.h>

void blink(int time);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(921600);

  Serial.println("Hello from the setup");

  delay(2000);

  // connect to wifi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
}

bool IsConnected = false;

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    if (!IsConnected) {
      Serial.println("Connected to the WiFi network");
      Serial.println(WiFi.localIP());

      digitalWrite(LED_BUILTIN, HIGH);
      IsConnected = true;


      startHttpServer();
    }

    listenConnections();
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println(".");
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    IsConnected = false;
    delay(500);
  }
}

void blink(int time) {
  digitalWrite(LED_BUILTIN,HIGH);
  delay(time);

  digitalWrite(LED_BUILTIN, LOW);
  delay(time);
}
