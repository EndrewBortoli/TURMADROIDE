#include <AFMotor.h>
#include <HCSR04.h>

AF_DCMotor  motorEsquerdo(3); // 3 é Esquerdo  
AF_DCMotor  motorDireito(4); // 4 é Direito 

// Pinos de conexão do primeiro sensor TCS320
const int s0_1 = 26;
const int s1_1 = 28;
const int s2_1 = 31;
const int s3_1 = 29;
const int out_1 = 27;

// Pinos de conexão do segundo sensor TCS320
const int s0_2 = 40;
const int s1_2 = 41;
const int s2_2 = 34;
const int s3_2 = 37;
const int out_2 = 39;

// Pinos de conexão do sensor ultrassônico
const int triggerPin = 10;  // Pino de trigger do sensor ultrassônico
const int echoPin = 11;     // Pino de echo do sensor ultrassônico

int corVerdeS1;
int corVermelhoS1;
int corAzulS1;

int corVerdeS2;
int corVermelhoS2;
int corAzulS2;

long duration;              // Variável para armazenar a duração do pulso ultrassônico
int distance;               // Variável para armazenar a distância medida pelo sensor

void setup() {
  // Setar a velocidade inicial do motor
  motorEsquerdo.setSpeed(240); // Motor Esquerdo
  motorDireito.setSpeed(240); // Motor Direita
  Serial.begin(9600); // Chama o Monitor Serial
  pinMode(2, INPUT);

  pinMode(s0_1, OUTPUT);
  pinMode(s1_1, OUTPUT);
  pinMode(s2_1, OUTPUT);
  pinMode(s3_1, OUTPUT);
  pinMode(out_1, INPUT);

  pinMode(s0_2, OUTPUT);
  pinMode(s1_2, OUTPUT);
  pinMode(s2_2, OUTPUT);
  pinMode(s3_2, OUTPUT);
  pinMode(out_2, INPUT);

  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  digitalWrite(s0_1, HIGH);
  digitalWrite(s1_1, LOW);

  digitalWrite(s0_2, HIGH);
  digitalWrite(s1_2, LOW);
}

void loop() {
  color();

  int distancia = medirDistancia();
  
  if (corVermelhoS1 > 25 && corAzulS1 > 28 && corVerdeS1 > 22) {
    direitaVerde();  
  } else if (corVermelhoS2 > 110 && corAzulS2 > 95 && corVerdeS2 > 100) {
    esquerdaVerde();
  } else if (corVermelhoS1 > 25 && corAzulS1 > 28 && corVerdeS1 > 22 && corVermelhoS2 > 110 && corAzulS2 > 95 && corVerdeS2 > 100) {
    becoVerde();
  } else if (distancia < 10) {
    // Realize uma ação quando a distância for menor que 10 cm
    // Por exemplo, pare o motor ou mude a direção
  } else {
    seguidorDeLinha();
  }
}

void color() {
  digitalWrite(s2_1, LOW);
  digitalWrite(s3_1, LOW);
  corVermelhoS1 = pulseIn(out_1, digitalRead(out_1) == HIGH ? LOW : HIGH);
  digitalWrite(s3_1, HIGH);
  corAzulS1 = pulseIn(out_1, digitalRead(out_1) == HIGH ? LOW : HIGH);
  digitalWrite(s2_1, HIGH);
  corVerdeS1 = pulseIn(out_1, digitalRead(out_1) == HIGH ? LOW : HIGH);

  digitalWrite(s2_2, LOW);
  digitalWrite(s3_2, LOW);
  corVermelhoS2 = pulseIn(out_2, digitalRead(out_2) == HIGH ? LOW : HIGH);
  digitalWrite(s3_2, HIGH);
  corAzulS2 = pulseIn(out_2, digitalRead(out_2) == HIGH ? LOW : HIGH);
  digitalWrite(s2_2, HIGH);
  corVerdeS2 = pulseIn(out_2, digitalRead(out_2) == HIGH ? LOW : HIGH);
}

int medirDistancia() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;  // Calcula a distância em centímetros
  
  return distance;
}

void seguidorDeLinha() {
  int leftSensor = analogRead(A15); //sensor esquerdo
  int rightSensor = analogRead(A10); //sensor direito
  int valorSensor = 200;
  int valorSensorEsq = 100;
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

void direitaVerde() {
  int leftSensor = analogRead(A15); //sensor esquerdo
  int rightSensor = analogRead(A10); //sensor direito
  int valorSensor = 200;
  int valorSensorEsq = 100;
  motorEsquerdo.run(FORWARD);
  motorDireito.run(BACKWARD);
  delay(1000);
  motorEsquerdo.run(FORWARD);
  motorDireito.run(FORWARD);
  delay(200);
}

void esquerdaVerde() {
  int leftSensor = analogRead(A15); //sensor esquerdo
  int rightSensor = analogRead(A10); //sensor direito
  int valorSensor = 200;
  int valorSensorEsq = 100;
  motorEsquerdo.setSpeed(255);
  motorEsquerdo.run(BACKWARD);
  motorDireito.run(FORWARD);
  delay(1100);
  motorEsquerdo.run(FORWARD);
  motorDireito.run(FORWARD);
  delay(200);
}

void becoVerde() {
  int leftSensor = analogRead(A15); //sensor esquerdo
  int rightSensor = analogRead(A10); //sensor direito
  int valorSensor = 200;
  int valorSensorEsq = 100;
  motorEsquerdo.run(FORWARD);
  motorDireito.run(BACKWARD);
  delay(4000);
  motorEsquerdo.run(FORWARD);
  motorDireito.run(FORWARD);
  delay(200);
}
