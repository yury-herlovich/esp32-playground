#include <Arduino.h>
#include "blink.h"

// array of pins {red, green, blue}
int pins[3] = {D2, D3, D4};
// default color white
int colors[3] = {255, 255, 255};
bool isLedOn = false;

// const int LED_PIN = LED_BUILTIN;

void setColor(int red, int green, int blue) {
  colors[0] = red;
  colors[1] = green;
  colors[2] = blue;

  ledOn();
}

void setupPin() {
  for (int i = 0; i < 3; i++) {
    pinMode(pins[i], OUTPUT);
  }
}

void blink(int time, int times = 1) {
  bool currentLedStatus = ledStatus();

  for (int i = 0; i < times; i++) {
    // change led colors
    // Green
    setColor(0, 256, 0);
    delay(time);

    // Blue
    setColor(0, 0, 256);
    delay(time);

    // red
    setColor(256, 0, 0);
    delay(time);

    // Yellow
    setColor(256, 256, 0);
    delay(time);

    // Magenta
    setColor(256, 0, 256);
    delay(time);

    // Pink
    setColor(256, 192, 203);
    delay(time);

    // IndianRed
    setColor(205, 92, 92);
    delay(time);

    // DeepPink
    setColor(255, 20, 147);
    delay(time);

    // GreenYellow
    setColor(173, 255, 47);
    delay(time);

    // SteelBlue
    setColor(70, 130, 180);
    delay(time);

    // DarkSlateGray
    setColor(47, 79, 79);
    delay(time);

    setColor(255, 255, 255);
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
