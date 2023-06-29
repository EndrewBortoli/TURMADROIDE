
#include <AFMotor.h>
AF_DCMotor  motor[] = {3,4}; // 0 é Esquerdo e 1 é Direito 

// Pinos de conexão do primeiro sensor TCS320
const int s0_1 = 26;
const int s1_1 = 28;
const int s2_1 = 31;
const int s3_1 = 29;
const int out_1 = 50;

// Pinos de conexão do segundo sensor TCS320
const int s0_2 = 40;
const int s1_2 = 41;
const int s2_2 = 34;
const int s3_2 = 37;
const int out_2 = 39;//

// Definindo as variáveis de cada cor do sesor 1
int vermelhoS1 = 0;
int verdeS1 = 0;
int azulS1 = 0;
// Definindo as variáveis de cada cor do sensor 2
int vermelhoS2 = 0;
int verdeS2 = 0;
int azulS2 = 0;


void setup() 
{
  //Seta a velocidade inicial do motor
    motor[0].setSpeed(225); // Motor Esquerdo
    motor[1].setSpeed(225); // Motor Direita

  Serial.begin(9600); // Chama o Monitor Serial

  pinMode(2, INPUT);

    //colocando as entradas do sensor 1 como output ou input
  pinMode(s0_1, OUTPUT);
  pinMode(s1_1, OUTPUT);
  pinMode(s2_1, OUTPUT);
  pinMode(s3_1, OUTPUT);
  pinMode(out_1, INPUT);

  //colocando as entradas do sensor 2 como output ou input
  pinMode(s0_2, OUTPUT);
  pinMode(s1_2, OUTPUT);
  pinMode(s2_2, OUTPUT);
  pinMode(s3_2, OUTPUT);
  pinMode(out_2, INPUT);

  digitalWrite(s0_1, HIGH);
  digitalWrite(s1_1, LOW);

  digitalWrite(s0_2, HIGH);
  digitalWrite(s1_2, LOW);
}

void loop() 
{
  color();

  int leftSensor = analogRead(A15); //sensor esquerdo
  int rightSensor = analogRead(A10); //sensor direito
  int valorSensor = 100;
  int valorSensorEsq = 100;

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
  } else if (vermelhoS1 > 150 && vermelhoS1 < 190 && azulS1 > 15 && azulS1 < 170 && verdeS1 > 130 && verdeS1 < 180) {
    void EsquerdaVerde();
  } else if (vermelhoS2 > 150 && vermelhoS2 < 190 && azulS2 > 15 && azulS2 < 170 && verdeS2 > 130 && verdeS2 < 180) {
    void DireitaVerde();
  } else if (verdeS1 > 100 && verdeS2 > 100) {
    void Beco();
  } else {
    motor[0].run(RELEASE);
    motor[1].run(RELEASE);
  }
}

void color() {
  digitalWrite(s2_1, LOW);
  digitalWrite(s3_1, LOW);
  vermelhoS1 = pulseIn(out_1, digitalRead(out_1) == HIGH ? LOW : HIGH);
  digitalWrite(s3_1, HIGH);
  azulS1 = pulseIn(out_1, digitalRead(out_1) == HIGH ? LOW : HIGH);
  digitalWrite(s2_1, HIGH);
  verdeS1 = pulseIn(out_1, digitalRead(out_1) == HIGH ? LOW : HIGH);

  digitalWrite(s2_2, LOW);
  digitalWrite(s3_2, LOW);
  vermelhoS2 = pulseIn(out_2, digitalRead(out_2) == HIGH ? LOW : HIGH);
  digitalWrite(s3_2, HIGH);
  azulS2 = pulseIn(out_2, digitalRead(out_2) == HIGH ? LOW : HIGH);
  digitalWrite(s2_2, HIGH);
  verdeS2 = pulseIn(out_2, digitalRead(out_2) == HIGH ? LOW : HIGH);
}

void EsquerdaVerde() {
    motor[0].run(BACKWARD);
    motor[1].run(FORWARD);
    delay(2300);
}
void DireitaVerde() {
    motor[0].run(FORWARD);
    motor[1].run(BACKWARD);
    delay(2300);
}

void Beco(){
    motor[0].run(FORWARD);
    motor[1].run(BACKWARD);
    delay(3600);
}