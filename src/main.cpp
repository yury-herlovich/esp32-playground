#include <Arduino.h>

void blink(int time);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(921600);
  Serial.println("Hello from the setup");
}

void loop() {
  // put your main code here, to run repeatedly:
  blink(250);
  blink(250);

  blink(1000);
  Serial.println("Hello from the loop");
}

void blink(int time) {
  digitalWrite(LED_BUILTIN,HIGH);
  delay(time);

  digitalWrite(LED_BUILTIN, LOW);
  delay(time);
}
