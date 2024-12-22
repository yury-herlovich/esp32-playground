#include <Arduino.h>
#include <WiFiMulti.h>
#include <secrets.h>

WiFiMulti wifiMulti;

void blink(int time);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(921600);

  Serial.println("Hello from the setup");

  // connect to wifi
  wifiMulti.addAP(WIFI_SSID, WIFI_PASS);

  blink(250);

  while (wifiMulti.run() != WL_CONNECTED) {
    blink(250);
  }

  Serial.println("Connected to wifi");
}

void loop() {
  digitalWrite(LED_BUILTIN, WiFi.status() == WL_CONNECTED ? HIGH : LOW);
}

void blink(int time) {
  digitalWrite(LED_BUILTIN,HIGH);
  delay(time);

  digitalWrite(LED_BUILTIN, LOW);
  delay(time);
}
