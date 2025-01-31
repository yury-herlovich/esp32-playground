#include <Arduino.h>
#include "blink.h"

// array of pins {red, green, blue}
int pins[3] = {D2, D3, D4};
// default color red, green, blue
int colors[3] = {255, 0, 0};
bool isLedOn = false;

// const int LED_PIN = LED_BUILTIN;

void setColor(int red, int green, int blue) {
  colors[0] = red;
  colors[1] = green;
  colors[2] = blue;

  if (ledStatus()) {
    ledOn();
  }
}

void setupPin() {
  for (int i = 0; i < 3; i++) {
    pinMode(pins[i], OUTPUT);
  }
}

void blink(int time, int times = 1) {
  bool currentLedStatus = ledStatus();

  for (int i = 0; i < times; i++) {
    ledOn();
    delay(time);

    ledOff();
    delay(time);
  }

  if (currentLedStatus) {
    ledOn();
  }
}

void ledOn() {
  for (int i = 0; i < 3; i++) {
    analogWrite(pins[i], colors[i]);
  }

  isLedOn = true;
}

void ledOff() {
  for (int i = 0; i < 3; i++) {
    analogWrite(pins[i], LOW);
  }

  isLedOn = false;
}

void switchLed() {
  if (ledStatus()) {
    ledOff();
  } else {
    ledOn();
  }
}

bool ledStatus() {
  return isLedOn;
}
