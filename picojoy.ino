#include <Joystick.h>

const int gimbalXPin = A0;
const int gimbalYPin = A1;
const int gimbalZPin = A2;
const int buttonPins[6] = {2, 3, 4, 5, 6, 7};

// Calibration values
int centerValueX, centerValueY, centerValueZ;

void setup() {
  Joystick.begin();
  Joystick.useManualSend(true);

  for (int i = 0; i < 6; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  // Calibration
  centerValueX = analogRead(gimbalXPin);
  centerValueY = analogRead(gimbalYPin);
  centerValueZ = analogRead(gimbalZPin);
}

void loop() {
  int gimbalX = analogRead(gimbalXPin);
  int gimbalY = analogRead(gimbalYPin);
  int gimbalZ = analogRead(gimbalZPin);

  // Adjust the mapping based on the center values
  int joystickX = map(gimbalX, centerValueX - 512, centerValueX + 512, 0, 960);
  int joystickY = map(gimbalY, centerValueY - 512, centerValueY + 512, 1000, 0);
  int joystickZ = map(gimbalZ, centerValueZ - 512, centerValueZ + 512, 0, 1000);

  Joystick.X(joystickX);
  Joystick.Y(joystickY);
  Joystick.Z(joystickZ);

  for (int i = 0; i < 6; i++) {
    bool buttonState = digitalRead(buttonPins[i]) == LOW;
    Joystick.button(i + 1, buttonState);
  }

  Joystick.send_now();
  delay(10);
}
