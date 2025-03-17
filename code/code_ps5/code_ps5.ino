#include <ps5Controller.h>

int enableRightMotor = 22;
int rightMotorPin1 = 32;
int rightMotorPin2 = 33;

int enableLeftMotor = 23;
int leftMotorPin1 = 18;
int leftMotorPin2 = 19;

int motorSpeed = 255;
int currentCommand = 0;

void setup() {
  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);

  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  ps5.begin("D0:BC:C1:29:40:47");
  Serial.begin(115200);
  Serial.print("Conectando ao controle...");
}

void moveForward(int speed) {  
  digitalWrite(rightMotorPin1, HIGH);
  digitalWrite(rightMotorPin2, LOW);
  digitalWrite(leftMotorPin1, HIGH);
  digitalWrite(leftMotorPin2, LOW);

  analogWrite(enableRightMotor, speed);
  analogWrite(enableLeftMotor, speed);
}

void moveForwardWithTurning(int speedY, int speedX) {
  int baseSpeed = map(abs(speedY), 0, 127, 0, 255);

  int rightSpeed = baseSpeed;
  int leftSpeed = baseSpeed;

  if (speedX < 0) {
    rightSpeed  = map(speedX, -127, 0, baseSpeed/2, baseSpeed);
  } else if (speedX > 0) {
    leftSpeed = map(speedX, 0, 127, baseSpeed, baseSpeed/2);
  }

  digitalWrite(rightMotorPin1, HIGH);
  digitalWrite(rightMotorPin2, LOW);
  digitalWrite(leftMotorPin1, HIGH);
  digitalWrite(leftMotorPin2, LOW);

  analogWrite(enableRightMotor, rightSpeed);
  analogWrite(enableLeftMotor, leftSpeed);
}

void moveBackward(int speed) {
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, HIGH);
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, HIGH);

  analogWrite(enableRightMotor, speed);
  analogWrite(enableLeftMotor, speed);
}

void moveBackwardWithTurning(int speedY, int speedX) {
  int baseSpeed = map(abs(speedY), 0, 127, 0, 255);

  int rightSpeed = baseSpeed;
  int leftSpeed = baseSpeed;

  if (speedX < 0) {
    rightSpeed = map(speedX, -127, 0, baseSpeed/2, baseSpeed);
  } else if (speedX > 0) {
    leftSpeed = map(speedX, 0, 127, baseSpeed, baseSpeed/2);
  }

  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, HIGH);
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, HIGH);

  analogWrite(enableRightMotor, rightSpeed);
  analogWrite(enableLeftMotor, leftSpeed);
}

void turnLeft() {
  digitalWrite(rightMotorPin1, HIGH);
  digitalWrite(rightMotorPin2, LOW);
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, HIGH);
  
  analogWrite(enableRightMotor, motorSpeed);
  analogWrite(enableLeftMotor, motorSpeed);
}

void turnRight() {
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, HIGH);
  digitalWrite(leftMotorPin1, HIGH);
  digitalWrite(leftMotorPin2, LOW);
  
  analogWrite(enableRightMotor, motorSpeed);
  analogWrite(enableLeftMotor, motorSpeed);
}

void stopMotors() {
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, LOW);
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, LOW);
  
  analogWrite(enableRightMotor, 0);
  analogWrite(enableLeftMotor, 0);
}

void loop() {
  if (ps5.isConnected()) {
    static unsigned long lastUpdate = 0;
    if (millis() - lastUpdate > 50) {
      lastUpdate = millis();
    
      Serial.print("Conectado ao controle!");

      if (ps5.LStickY() > 0) {
        currentCommand = 1;
      }
      else if (ps5.Up() || ps5.Cross()) {
        currentCommand = 2;
      }
      else if (ps5.R2()) {
        currentCommand = 3;
      }
      else if (ps5.LStickY() < 0) {
        currentCommand = 4;
      }
      else if (ps5.Down() || ps5.Square()) {
        currentCommand = 5;
      }
      else if (ps5.L2() > 0) {
        currentCommand = 6;
      }
      else if (ps5.Left()) {
        currentCommand = 7;
      }
      else if (ps5.Right()) {
        currentCommand = 8;
      }
      else {
        currentCommand = 0;
      }

      switch (currentCommand) 
      {
        case 1:
          moveForwardWithTurning(ps5.LStickY(), ps5.LStickX());  
          break;
        case 2:
          moveForward(motorSpeed);
          break;
        case 3:
          moveForward(ps5.R2Value() * 2);
          break;
        case 4:
          moveBackwardWithTurning(-(ps5.LStickY()), ps5.LStickX());
          break;
        case 5:
          moveBackward(motorSpeed);
          break;
        case 6:
          moveBackward(ps5.L2Value() * 2);
          break;
        case 7:
          turnLeft();
          break;
        case 8:
          turnRight();
          break;
        default:
          stopMotors();
          break;
      }
    }
  }
}
