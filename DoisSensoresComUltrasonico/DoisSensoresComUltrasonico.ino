#include <HCSR04.h>
#include <AFMotor.h>

AF_DCMotor motorEsquerdo(3);  // Motor Esquerdo conectado ao pino 3
AF_DCMotor motorDireito(4);   // Motor Direito conectado ao pino 4

HCSR04 sensorUltrassonico(22, 23);  // Pino de trigger: 22, Pino de echo: 23

const int DistanciaDeObjeto = 5;

void distanceMeasurement(); // Function prototype

void setup() 
{
  // Setar a velocidade inicial dos motores
  motorEsquerdo.setSpeed(255); 
  motorDireito.setSpeed(255);

  Serial.begin(9600); // Inicializar o Monitor Serial
  pinMode(2, INPUT);
}

void loop() 
{
  distanceMeasurement(); // Chamar a função para medir a distância com o sensor ultrassônico

  int leftSensor = analogRead(A15); // Sensor esquerdo
  int rightSensor = analogRead(A10); // Sensor direito
  int valorSensor = 200;
  int valorSensorEsq = 100;
  int distanciaObstaculo = sensorUltrassonico.dist(); // Realizar a leitura da distância do sensor ultrassônico em cm

  if (distanciaObstaculo < DistanciaDeObjeto)  {
    // Obstáculo detectado pelo sensor ultrassônico
    desviarObstaculo();
  } 
  else if (leftSensor < valorSensorEsq && rightSensor < valorSensor) { // Seguidor de Linha
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

void desviarObstaculo() {
  motorEsquerdo.run(BACKWARD);
  motorDireito.run(BACKWARD);
  delay(500);
  motorEsquerdo.run(BACKWARD);
  motorDireito.run(FORWARD);
  delay(2000);
  motorEsquerdo.run(FORWARD);
  motorDireito.run(FORWARD);
  delay(1600);
  motorEsquerdo.run(FORWARD);
  motorDireito.run(BACKWARD);
  delay(2250);
  motorEsquerdo.run(FORWARD);
  motorDireito.run(FORWARD);
  delay(3750);
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

void distanceMeasurement() {
  float distance = sensorUltrassonico.dist();  // Mede a distância em centímetros
  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");
}
