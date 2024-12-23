#include <Arduino.h>
#include <WiFi.h>
#include <secrets.h>

void blink(int time);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(921600);

  Serial.println("Hello from the setup");

  // connect to wifi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
}

bool IsConnected = false;

void loop() {
  if (WiFi.status() == WL_CONNECTED && !IsConnected) {
    Serial.println("Connected to the WiFi network");
    digitalWrite(LED_BUILTIN, HIGH);
    IsConnected = true;
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
