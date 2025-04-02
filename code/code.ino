#include <Ps3Controller.h>

int enableRightMotor = 5;
int rightMotorPin1 = 7;
int rightMotorPin2 = 6;

int enableLeftMotor = 9;
int leftMotorPin1 = 4;
int leftMotorPin2 = 3;

int motorSpeed = 255;

unsigned long lastCommandTime = 0;
int currentCommand = 0;

void setup() {
  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);

  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  Ps3.begin("90:90:69:00:00:00");
  Serial.begin(115200);
  Serial.println("Pronto para conectar o controle PS3...");
}

void moveForward(int speed) {
  digitalWrite(rightMotorPin1, HIGH);
  digitalWrite(rightMotorPin2, LOW);
  digitalWrite(leftMotorPin1, HIGH);
  digitalWrite(leftMotorPin2, LOW);

  analogWrite(enableRightMotor, speed);
  analogWrite(enableLeftMotor, speed);
}

void moveBackward(int speed) {
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, HIGH);
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, HIGH);

  analogWrite(enableRightMotor, speed);
  analogWrite(enableLeftMotor, speed);
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
  if (Ps3.isConnected()) {
    if (millis() - lastCommandTime > 10) 
      {
      lastCommandTime = millis(); 

      if (Ps3.data.button.up || Ps3.data.button.cross) {
        currentCommand = 1;
      }
      else if (Ps3.data.analog.button.r2 > 0) {
        currentCommand = 2;
      }
      else if (Ps3.data.button.down || Ps3.data.button.square) {
        currentCommand = 3;
      }
      else if (Ps3.data.analog.button.l2 > 0) {
        currentCommand = 4;
      }
      else if (Ps3.data.button.left) {
        currentCommand = 5;
      }
      else if (Ps3.data.button.right) {
        currentCommand = 6;
      }
      else {
        currentCommand = 0;
      }

      switch (currentCommand) {
        case 1:
          moveForward(motorSpeed);
          Serial.println("Movendo para frente");
          break;
        case 2:
          moveForward(Ps3.data.analog.button.r2);
          Serial.print("R2 pressionado com valor: ");
          Serial.println(Ps3.data.analog.button.r2);
          break;
        case 3:
          moveBackward(motorSpeed);
          Serial.println("Movendo para trás");
          break;
        case 4:
          moveBackward(Ps3.data.analog.button.l2);
          Serial.print("L2 pressionado com valor: ");
          Serial.println(Ps3.data.analog.button.l2);
          break;
        case 5:
          turnLeft();
          Serial.println("Virando para a esquerda");
          break;
        case 6:
          turnRight();
          Serial.println("Virando para a direita");
          break;
        default:
          stopMotors();
          Serial.println("Parado");
          break;
      }
    }
  }
}