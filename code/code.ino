#include <Ps3Controller.h>

int enableRightMotor = 22;
int rightMotorPin1 = 32;
int rightMotorPin2 = 33;

int enableLeftMotor = 23;
int leftMotorPin1 = 18;
int leftMotorPin2 = 19;

#define MAX_MOTOR_SPEED 255

const int PWMFreq = 1000;
const int PWMResolution = 8;

const int rightMotorPWMSpeedChannel = 4;
const int leftMotorPWMSpeedChannel = 5;

void rotateMotor(int rightMotorSpeed, int leftMotorSpeed)
{
  if (rightMotorSpeed < 0)
  {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);    
  }
  else if (rightMotorSpeed > 0)
  {
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);      
  }
  else
  {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, LOW);      
  }
  
  if (leftMotorSpeed < 0)
  {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);    
  }
  else if (leftMotorSpeed > 0)
  {
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);      
  }
  else
  {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, LOW);      
  }
  
  ledcWrite(rightMotorPWMSpeedChannel, abs(rightMotorSpeed));
  ledcWrite(leftMotorPWMSpeedChannel, abs(leftMotorSpeed));  
}

void setUpPinModes()
{
  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
  
  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  ledcAttachChannel(enableRightMotor, PWMFreq, PWMResolution, rightMotorPWMSpeedChannel);
  ledcAttachChannel(enableLeftMotor, PWMFreq, PWMResolution, leftMotorPWMSpeedChannel);

  rotateMotor(0, 0); 
}

void setup()
{
  Serial.begin(115200);
  setUpPinModes();
  Ps3.begin("90:90:69:00:00:00");

  if(!Ps3.isConnected())
  {
    return;
  }

  Serial.println("Controle PS3 conectado!");
}

void loop()
{
  int rightMotorSpeed = 0;
  int leftMotorSpeed = 0;

  if (Ps3.data.button.up || Ps3.data.button.cross)
  {
    Serial.println("Acelerando!");
    rightMotorSpeed = MAX_MOTOR_SPEED;
    leftMotorSpeed = MAX_MOTOR_SPEED;
  }
  else if (Ps3.data.analog.button.r2 > 0)
  {
    rightMotorSpeed = Ps3.data.analog.button.r2;
    leftMotorSpeed = Ps3.data.analog.button.r2;
    Serial.print("Pressão no botão R2: ");
    Serial.println(Ps3.data.analog.button.r2);
  }
  else if (Ps3.data.button.down) 
  {
    Serial.println("Ré!");
    rightMotorSpeed = -MAX_MOTOR_SPEED;
    leftMotorSpeed = -MAX_MOTOR_SPEED;
  }
  else if (Ps3.data.analog.button.l2)
  {
    rightMotorSpeed = -Ps3.data.analog.button.l2;
    leftMotorSpeed = -Ps3.data.analog.button.l2;
    Serial.print("Pressão no botão L2: ");
    Serial.println(Ps3.data.analog.button.l2);
  }

  if (Ps3.data.button.left)
  {
    Serial.println("Esquerda!");
    rightMotorSpeed = MAX_MOTOR_SPEED;
    leftMotorSpeed = -MAX_MOTOR_SPEED;
  }

  if (Ps3.data.button.right)
  {
    Serial.println("Direita!");
    rightMotorSpeed = -MAX_MOTOR_SPEED;
    leftMotorSpeed = MAX_MOTOR_SPEED;
  }

  if (Ps3.data.button.circle || Ps3.data.button.r1)
  {
    Serial.println("Freio!");
    rightMotorSpeed = 0;
    leftMotorSpeed = 0;
  }

  rotateMotor(rightMotorSpeed, leftMotorSpeed);
}