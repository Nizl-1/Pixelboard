#include "Joystick.h"

Joystick stick(32, 34, 35); // SW, VRx, VRy (ADC1, WiFi-tauglich)

void setup() {
  Serial.begin(115200);
  Serial.println("Joystick-Test gestartet");
}

void loop() {
  stick.entprellen();

  if (stick.wurdeGedrueckt()) {
    Serial.println("Taster kurz gedrueckt");
  }

  if (stick.wurdeLangeGedrueckt()) {
    Serial.println("Taster lang gedrueckt");
  }

  Serial.print("X=");
  Serial.print(stick.leseX());
  Serial.print(" Y=");
  Serial.println(stick.leseY());

  delay(50);
}
