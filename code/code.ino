#include <Ps3Controller.h>

int enableRightMotor = 22;
int rightMotorPin1 = 32;
int rightMotorPin2 = 33;

int enableLeftMotor = 23;
int leftMotorPin1 = 18;
int leftMotorPin2 = 19;

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
          digitalWrite(rightMotorPin1, HIGH);
          digitalWrite(rightMotorPin2, LOW);
          digitalWrite(leftMotorPin1, HIGH);
          digitalWrite(leftMotorPin2, LOW);
          analogWrite(enableRightMotor, motorSpeed);
          analogWrite(enableLeftMotor, motorSpeed);
          Serial.println("Movendo para frente");
          break;
        case 2:
          digitalWrite(rightMotorPin1, HIGH);
          digitalWrite(rightMotorPin2, LOW);
          digitalWrite(leftMotorPin1, HIGH);
          digitalWrite(leftMotorPin2, LOW);
          analogWrite(enableRightMotor, Ps3.data.analog.button.r2);
          analogWrite(enableLeftMotor, Ps3.data.analog.button.r2);
          Serial.print("R2 pressionado com valor: ");
          Serial.println(Ps3.data.analog.button.r2);
          break;
        case 3:
          digitalWrite(rightMotorPin1, LOW);
          digitalWrite(rightMotorPin2, HIGH);
          digitalWrite(leftMotorPin1, LOW);
          digitalWrite(leftMotorPin2, HIGH);
          analogWrite(enableRightMotor, motorSpeed);
          analogWrite(enableLeftMotor, motorSpeed);
          Serial.println("Movendo para trás");
          break;
        case 4:
          digitalWrite(rightMotorPin1, LOW);
          digitalWrite(rightMotorPin2, HIGH);
          digitalWrite(leftMotorPin1, LOW);
          digitalWrite(leftMotorPin2, HIGH);
          analogWrite(enableRightMotor, Ps3.data.analog.button.l2);
          analogWrite(enableLeftMotor, Ps3.data.analog.button.l2);
          Serial.print("L2 pressionado com valor: ");
          Serial.println(Ps3.data.analog.button.l2);
          break;
        case 5:
          digitalWrite(rightMotorPin1, HIGH);
          digitalWrite(rightMotorPin2, LOW);
          digitalWrite(leftMotorPin1, LOW);
          digitalWrite(leftMotorPin2, HIGH);
          analogWrite(enableRightMotor, motorSpeed);
          analogWrite(enableLeftMotor, motorSpeed);
          Serial.println("Virando para a esquerda");
          break;
        case 6:
          digitalWrite(rightMotorPin1, LOW);
          digitalWrite(rightMotorPin2, HIGH);
          digitalWrite(leftMotorPin1, HIGH);
          digitalWrite(leftMotorPin2, LOW);
          analogWrite(enableRightMotor, motorSpeed);
          analogWrite(enableLeftMotor, motorSpeed);
          Serial.println("Virando para a direita");
          break;
        default:
          digitalWrite(rightMotorPin1, LOW);
          digitalWrite(rightMotorPin2, LOW);
          digitalWrite(leftMotorPin1, LOW);
          digitalWrite(leftMotorPin2, LOW);
          analogWrite(enableRightMotor, 0);
          analogWrite(enableLeftMotor, 0);
          Serial.println("Parado");
          break;
      }
    }
  }
}