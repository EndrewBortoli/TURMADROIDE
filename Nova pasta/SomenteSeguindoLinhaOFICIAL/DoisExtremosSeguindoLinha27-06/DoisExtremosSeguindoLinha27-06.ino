
#include <AFMotor.h>
AF_DCMotor  motor[] = {3,4}; // 0 é Esquerdo e 1 é Direito 


void setup() 
{
  //Seta a velocidade inicial do motor
    motor[0].setSpeed(235); // Motor Esquerdo
    motor[1].setSpeed(235); // Motor Direita
  Serial.begin(9600); // Chama o Monitor Serial
  pinMode(2, INPUT);
  
}

void loop() 
{
  int leftSensor = analogRead(A15); //sensor esquerdo
  int rightSensor = analogRead(A10); //sensor direito
  int valorSensor = 300;
  int valorSensorEsq = 300;

  if (leftSensor < valorSensorEsq && rightSensor < valorSensor) { // Seguidor de Linha
    motor[0].run(FORWARD);
    motor[1].run(FORWARD);
  } else if (leftSensor > valorSensorEsq && rightSensor < valorSensor) { // 
    motor[0].run(BACKWARD);
    motor[1].run(FORWARD);  
  } else if (leftSensor < valorSensorEsq && rightSensor > valorSensor) {
    motor[0].run(FORWARD);
    motor[1].run(BACKWARD);
  } else if (leftSensor > valorSensorEsq && rightSensor > valorSensor) {
    motor[0].run(FORWARD);
    motor[1].run(FORWARD);
  } else {
    motor[0].run(RELEASE);
    motor[1].run(RELEASE);
  }
}

