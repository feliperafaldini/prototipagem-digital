#define CUSTOM_SETTINGS
#define INCLUDE_LEDCONTROL_MODULE

#include <Dabble.h>
#include <SoftwareSerial.h>

SoftwareSerial BT(10, 11);

#define ENA 5
#define IN1 7
#define IN2 6

#define IN3 4
#define IN4 3
#define ENB 9

void setup() {
  Serial.begin(115200);
  BT.begin(115200);
  Dabble.begin(BT);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void loop() {
  Dabble.process();

  if (GamePad.isUpPressed()) {
    moveForward();
  } else if (GamePad.isDownPressed()) {
    moveBackward();
  } else if (GamePad.isLeftPressed()) {
    turnLeft();
  } else if (GamePad.isRightPressed()) {
    turnRight();
  } else {
    stopMotors();
  }
}
