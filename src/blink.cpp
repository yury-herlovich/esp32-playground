#include <Arduino.h>

void blink(int time) {
  digitalWrite(LED_BUILTIN,HIGH);
  delay(time);

  digitalWrite(LED_BUILTIN, LOW);
  delay(time);
}

void ledOn() {
  digitalWrite(LED_BUILTIN, HIGH);
}
