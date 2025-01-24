#ifndef BLINK_H
#define BLINK_H

void setupPin();
void setColor(int red, int green, int blue);
void blink(int time, int times);
void ledOn();
void ledOff();
void switchLed();
bool ledStatus();

#endif // BLINK_H
