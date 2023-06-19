#include <AFMotor.h>
AF_DCMotor  motor[] = {3,4}; // 0 é Esquerdo e 1 é Direito 

// Definir os pinos do sensor ultrassônico HC-SR04 FRONTAL
const int trigPin = A11;
const int echoPin = A12;

void setup() 
{
  //Seta a velocidade inicial do motor
  motor[0].setSpeed(200); // Motor Esquerdo
  motor[1].setSpeed(200); // Motor Direita
  
  Serial.begin(9600); // Chama o Monitor Serial
  pinMode(2, INPUT);
  
  // Configura os pinos do sensor ultrassônico
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() 
{
  int leftSensor = analogRead(9); //sensor esquerdo
  int rightSensor = analogRead(8); //sensor direito
  int valorSensor = 900;
  
  // Leitura da distância no sensor ultrassônico frontal
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;
  
  // Verifica se há um objeto a menos de 15cm de distância
  if (distance < 15) {
    // Vira à direita
    turnRight();
  } else if (leftSensor < valorSensor && rightSensor < valorSensor) { // Seguidor de Linha
    motor[0].run(BACKWARD);
    motor[1].run(BACKWARD);
  } else if (leftSensor > valorSensor && rightSensor < valorSensor) { // 
    motor[0].run(FORWARD);
    motor[1].run(BACKWARD);
  } else if (leftSensor < valorSensor && rightSensor > valorSensor) {
    motor[0].run(BACKWARD);
    motor[1].run(FORWARD);
  } else if (leftSensor > valorSensor && rightSensor > valorSensor) {
    motor[0].run(BACKWARD);
    motor[1].run(BACKWARD);
  } else {
    motor[0].run(RELEASE);
    motor[1].run(RELEASE);
  }
}

void turnRight() {
  motor[0].run(FORWARD);
  motor[1].run(BACKWARD);
  delay(600); // Tempo de giro para desviar
  motor[0].run(BACKWARD);
  motor[1].run(BACKWARD);
  delay(700); // Tempo de recuperação
   motor[0].run(BACKWARD);
  motor[1].run(FORWARD);
  delay(600); // Tempo de giro para voltar
  motor[0].run(BACKWARD);
  motor[1].run(BACKWARD);
  delay(700); // Tempo de recuperação
  motor[0].run(BACKWARD);
  motor[1].run(FORWARD);
  delay(600); // Tempo de recuperação
  motor[0].run(BACKWARD);
  motor[1].run(BACKWARD);
  delay(650); // Tempo de recuperação
  
}
