#include <HCSR04.h>
#include <AFMotor.h>

AF_DCMotor motorEsquerdo(3);  // Motor Esquerdo conectado ao pino 1
AF_DCMotor motorDireito(4);   // Motor Direito conectado ao pino 2 

#define DISTANCIA_OBSTACULO_MIN 1 // Distância mínima para identificar obstáculo
#define DISTANCIA_OBSTACULO_MAX 4 // Distância máxima para identificar obstáculo

UltraSonicDistanceSensor distanceSensor(22, 23);  // Pino de trigger: 22, Pino de echo: 23

void setup() 
{
  //Seta a velocidade inicial do motor
    motorEsquerdo.setSpeed(255); // Motor Esquerdo
    motorDireito.setSpeed(255); // Motor Direita
  Serial.begin(9600); // Chama o Monitor Serial
  pinMode(2, INPUT);
  
}

void loop() 
{
  int leftSensor = analogRead(A15); //sensor esquerdo
  int rightSensor = analogRead(A10); //sensor direito
  int valorSensor = 200;
  int valorSensorEsq = 100;

  int distanciaObstaculo = distanceSensor.measureDistanceCm(); // Realiza a leitura da distância do sensor ultrassônico em cm

  if (distanciaObstaculo > DISTANCIA_OBSTACULO_MIN && distanciaObstaculo < DISTANCIA_OBSTACULO_MAX) {
    // Obstáculo detectado pelo sensor ultrassônico
    desviarObstaculo();
  } else {

  if (leftSensor < valorSensorEsq && rightSensor < valorSensor) { // Seguidor de Linha
    motorEsquerdo.run(FORWARD);
    motorDireito.run(FORWARD);
  } else if (leftSensor > valorSensorEsq && rightSensor < valorSensor) { // 
    motorEsquerdo.run(BACKWARD);
    motorDireito.run(FORWARD);  
  } else if (leftSensor < valorSensorEsq && rightSensor > valorSensor) {
    motorEsquerdo.run(FORWARD);
    motorDireito.run(BACKWARD);
  } else if (leftSensor > valorSensorEsq && rightSensor > valorSensor) {
    motorEsquerdo.run(FORWARD);
    motorDireito.run(FORWARD);
  } else {
    motorEsquerdo.run(RELEASE);
    motorDireito.run(RELEASE);
  }
}
}
void desviarObstaculo() {
  motorEsquerdo.run(BACKWARD);
  motorDireito.run(BACKWARD);
  delay(500); // Ajuste o tempo conforme necessário para o robô recuar mais tempo
  motorEsquerdo.run(BACKWARD);
  motorDireito.run(FORWARD);
  delay(2000); // Ajuste o tempo conforme necessário para o robô girar mais tempo
  motorEsquerdo.run(FORWARD);
  motorDireito.run(FORWARD);
  delay(1600); // Ajuste o tempo conforme necessário para o robô seguir em frente mais tempo
  motorEsquerdo.run(FORWARD);
  motorDireito.run(BACKWARD);
  delay(2250); // ajueste o tempo para o robô girar a esquerda
  motorEsquerdo.run(FORWARD);
  motorDireito.run(FORWARD);
  delay(3750); // ajuste o tempo para andar para frente
  motorEsquerdo.run(FORWARD);
  motorDireito.run(BACKWARD);
  delay(2000); // ajuste o tempo para virar a esquerda
  motorEsquerdo.run(FORWARD);
  motorDireito.run(FORWARD);
  delay(1500); // ajuste o tempo para andar para frente 
  motorEsquerdo.run(BACKWARD);
  motorDireito.run(FORWARD);
  delay(2000); // ajuste o tempo para virar a direita
}