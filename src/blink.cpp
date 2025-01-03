#include <Arduino.h>
#include "blink.h"

void blink(int time, int times = 1) {
  bool currentLedStatus = ledStatus();

  for (int i = 0; i < times; i++) {
    digitalWrite(LED_BUILTIN,HIGH);
    delay(time);

    digitalWrite(LED_BUILTIN, LOW);
    delay(time);
  }

  digitalWrite(LED_BUILTIN, currentLedStatus);
}

void ledOn() {
  digitalWrite(LED_BUILTIN, HIGH);
}

void ledOff() {
  digitalWrite(LED_BUILTIN, LOW);
}

void switchLed() {
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

bool ledStatus() {
  return digitalRead(LED_BUILTIN);
}
