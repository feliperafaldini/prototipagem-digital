#include <Ps3Controller.h>

// Definindo os pinos para os motores
int enableRightMotor = 22;
int rightMotorPin1 = 32;
int rightMotorPin2 = 33;

int enableLeftMotor = 23;
int leftMotorPin1 = 18;
int leftMotorPin2 = 19;

// Definindo a velocidade dos motores (PWM)
int motorSpeed = 200; // Valor de PWM (0 a 255)

void setup() {
  // Configurando os pinos como saída
  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);

  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  // Inicializando o controle PS3
  Ps3.begin("90:90:69:00:00:00"); // Substitua pelo endereço MAC do seu ESP32
  Serial.begin(115200);
  Serial.println("Pronto para conectar o controle PS3...");
}

void loop() {
  if (Ps3.isConnected()) {
    // Verificando os botões do controle PS3
    if (Ps3.data.button.up || Ps3.data.button.cross) {
      // Movendo os motores para frente
      digitalWrite(rightMotorPin1, HIGH);
      digitalWrite(rightMotorPin2, LOW);
      digitalWrite(leftMotorPin1, HIGH);
      digitalWrite(leftMotorPin2, LOW);
      analogWrite(enableRightMotor, motorSpeed); // Velocidade controlada por PWM
      analogWrite(enableLeftMotor, motorSpeed);  // Velocidade controlada por PWM
      Serial.println("Movendo para frente");
    }
    else if (Ps3.data.analog.button.r2)
    {
      digitalWrite(rightMotorPin1, HIGH);
      digitalWrite(rightMotorPin2, LOW);
      digitalWrite(leftMotorPin1, HIGH);
      digitalWrite(leftMotorPin2, LOW);
      analogWrite(enableRightMotor, Ps3.data.analog.button.r2); // Velocidade controlada por PWM
      analogWrite(enableLeftMotor, Ps3.data.analog.button.r2);
    } 
    else if (Ps3.data.button.down || Ps3.data.button.square) {
      // Movendo os motores para trás
      digitalWrite(rightMotorPin1, LOW);
      digitalWrite(rightMotorPin2, HIGH);
      digitalWrite(leftMotorPin1, LOW);
      digitalWrite(leftMotorPin2, HIGH);
      analogWrite(enableRightMotor, motorSpeed); // Velocidade controlada por PWM
      analogWrite(enableLeftMotor, motorSpeed);  // Velocidade controlada por PWM
      Serial.println("Movendo para trás");
    } 
    else if (Ps3.data.analog.button.l2)
    {
      digitalWrite(rightMotorPin1, LOW);
      digitalWrite(rightMotorPin2, HIGH);
      digitalWrite(leftMotorPin1, LOW);
      digitalWrite(leftMotorPin2, HIGH);
      analogWrite(enableRightMotor, Ps3.data.analog.button.l2); // Velocidade controlada por PWM
      analogWrite(enableLeftMotor, Ps3.data.analog.button.l2);
    }
    else if (Ps3.data.button.left) {
      // Virando para a esquerda
      digitalWrite(rightMotorPin1, HIGH);
      digitalWrite(rightMotorPin2, LOW);
      digitalWrite(leftMotorPin1, LOW);
      digitalWrite(leftMotorPin2, HIGH);
      analogWrite(enableRightMotor, motorSpeed); // Velocidade controlada por PWM
      analogWrite(enableLeftMotor, motorSpeed);  // Velocidade controlada por PWM
      Serial.println("Virando para a esquerda");
    } else if (Ps3.data.button.right) {
      // Virando para a direita
      digitalWrite(rightMotorPin1, LOW);
      digitalWrite(rightMotorPin2, HIGH);
      digitalWrite(leftMotorPin1, HIGH);
      digitalWrite(leftMotorPin2, LOW);
      analogWrite(enableRightMotor, motorSpeed); // Velocidade controlada por PWM
      analogWrite(enableLeftMotor, motorSpeed);  // Velocidade controlada por PWM
      Serial.println("Virando para a direita");
    } else {
      // Parando os motores
      digitalWrite(rightMotorPin1, LOW);
      digitalWrite(rightMotorPin2, LOW);
      digitalWrite(leftMotorPin1, LOW);
      digitalWrite(leftMotorPin2, LOW);
      analogWrite(enableRightMotor, 0); // Parar os motores
      analogWrite(enableLeftMotor, 0);  // Parar os motores
      Serial.println("Parado");
    }
  }
}