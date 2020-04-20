#include <Arduino.h>
#include <Ticker.h>
#include "../lib/lxlib/lxlib.h"
#include "wibrick/wibrick.h"

bool ledState = false;
void blinkFn() {
  digitalWrite(LED_BUILTIN, ledState);
  ledState = !ledState;
}

LxLib lxLib;
Ticker blinker(blinkFn, 500);

void setup() {
  delay(1000);
  lxLib.begin();
  wibrickSetup();
  pinMode(LED_BUILTIN, OUTPUT);
  blinker.start();
}

void loop() {
  lxLib.update();
  wibrickLoop();
  blinker.update();
}
