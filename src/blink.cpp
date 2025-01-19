#include <Arduino.h>
#include "blink.h"

const int LED_PIN = D3;
// const int LED_PIN = LED_BUILTIN;

void setupPin() {
  pinMode(LED_PIN, OUTPUT);
}

void blink(int time, int times = 1) {
  bool currentLedStatus = ledStatus();

  for (int i = 0; i < times; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(time);

    digitalWrite(LED_PIN, LOW);
    delay(time);
  }

  digitalWrite(LED_PIN, currentLedStatus);
}

void ledOn() {
  digitalWrite(LED_PIN, HIGH);
}

void ledOff() {
  digitalWrite(LED_PIN, LOW);
}

void switchLed() {
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}

bool ledStatus() {
  return digitalRead(LED_PIN);
}
