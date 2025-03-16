#include <ps5Controller.h>

int enableRightMotor = 22;
int rightMotorPin1 = 32;
int rightMotorPin2 = 33;

int enableLeftMotor = 23;
int leftMotorPin1 = 18;
int leftMotorPin2 = 19;

#define MAX_MOTOR_SPEED 255

int currentCommand = 0;

void setup() {
  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);

  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  ps5.begin("00:00:00:00:00:00");
  Serial.begin(115200);
  Serial.print("Conectando ao controle...");
}

void loop() {
  if (ps5.isConnected())
  {
    Serial.print("Conectado ao controle!");

    if (ps5.Up() || ps5.Cross())
    {
      currentCommand = 1;
    }
    else if (ps5.R2())
    {
      currentCommand = 2;
    }
    else if (ps5.Down() || ps5.Circle())
    {
      currentCommand = 3;
    }
    else if (ps5.L2())
    {
      currentCommand = 4;
    }
    else if (ps5.Left())
    {
      currentCommand = 5;
    }
    else if (ps5.Right())
    {
      currentCommand = 6;
    }
    else 
    {
      currentCommand = 0;
    }

    switch (currentCommand) 
    {
      case 1:
        digitalWrite(rightMotorPin1, HIGH);
        digitalWrite(rightMotorPin2, LOW);
        digitalWrite(leftMotorPin1, HIGH);
        digitalWrite(leftMotorPin2, LOW);
        
        analogWrite(enableRightMotor, MAX_MOTOR_SPEED);
        analogWrite(enableLeftMotor, MAX_MOTOR_SPEED);
        break;
      case 2:
        digitalWrite(rightMotorPin1, HIGH);
        digitalWrite(rightMotorPin2, LOW);
        digitalWrite(leftMotorPin1, HIGH);
        digitalWrite(leftMotorPin2, LOW);
        
        analogWrite(enableRightMotor, ps5.R2Value());
        analogWrite(enableLeftMotor, ps5.R2Value());
        break;
      case 3:
        digitalWrite(rightMotorPin1, LOW);
        digitalWrite(rightMotorPin2, HIGH);
        digitalWrite(leftMotorPin1, LOW);
        digitalWrite(leftMotorPin2, HIGH);
        
        analogWrite(enableRightMotor, MAX_MOTOR_SPEED);
        analogWrite(enableLeftMotor, MAX_MOTOR_SPEED);
        break;
      case 4:
        digitalWrite(rightMotorPin1, LOW);
        digitalWrite(rightMotorPin2, HIGH);
        digitalWrite(leftMotorPin1, LOW);
        digitalWrite(leftMotorPin2, HIGH);
        
        analogWrite(enableRightMotor, ps5.L2Value());
        analogWrite(enableLeftMotor, ps5.L2Value());
        break;
      case 5:
        digitalWrite(rightMotorPin1, HIGH);
        digitalWrite(rightMotorPin2, LOW);
        digitalWrite(leftMotorPin1, LOW);
        digitalWrite(leftMotorPin2, HIGH);
        
        analogWrite(enableRightMotor, MAX_MOTOR_SPEED);
        analogWrite(enableLeftMotor, MAX_MOTOR_SPEED);
        break;
      case 6:
        digitalWrite(rightMotorPin1, LOW);
        digitalWrite(rightMotorPin2, HIGH);
        digitalWrite(leftMotorPin1, HIGH);
        digitalWrite(leftMotorPin2, LOW);
        
        analogWrite(enableRightMotor, MAX_MOTOR_SPEED);
        analogWrite(enableLeftMotor, MAX_MOTOR_SPEED);
        break;
      default:
        digitalWrite(rightMotorPin1, LOW);
        digitalWrite(rightMotorPin2, LOW);
        digitalWrite(leftMotorPin1, LOW);
        digitalWrite(leftMotorPin2, LOW);
        analogWrite(enableRightMotor, 0);
        analogWrite(enableLeftMotor, 0);
        break;
    }
  }
}
