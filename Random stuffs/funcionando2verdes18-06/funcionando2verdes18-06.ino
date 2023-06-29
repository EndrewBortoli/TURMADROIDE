#include <AFMotor.h>

// Pinos de conexão do primeiro sensor TCS320
const int s0_1 = 52;
const int s1_1 = 53;
const int s2_1 = 51;
const int s3_1 = 49;
const int out_1 = 50;

// Pinos de conexão do segundo sensor TCS320
const int s0_2 = 46;
const int s1_2 = 47;
const int s2_2 = 44;
const int s3_2 = 43;
const int out_2 = 45;

// Definindo as variáveis de cada cor do sesor 1
int vermelhoS1 = 0;
int verdeS1 = 0;
int azulS1 = 0;
// Definindo as variáveis de cada cor do sensor 2
int vermelhoS2 = 0;
int verdeS2 = 0;
int azulS2 = 0;
// define os motores
AF_DCMotor motor1(3); // Motor esquerdo
AF_DCMotor motor2(4); // Motor direito


void setup() {
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

//Iniciando o SerialMonitor
  Serial.begin(9600);

  digitalWrite(s0_1, HIGH);
  digitalWrite(s1_1, LOW);

  digitalWrite(s0_2, HIGH);
  digitalWrite(s1_2, LOW);

  motor1.setSpeed(180); // Velocidade do motor esquerdo
  motor2.setSpeed(180); // Velocidade do motor direito

  delay(1000); // Aguarda 1 segundo antes de iniciar a rodada
}

void loop() {
  color();

    // Lógica para o robô seguir a linha com base nas leituras dos sensores
  if (vermelhoS1 < 60 && azulS1 < 60 && verdeS1 < 60 && vermelhoS2 < 40 && azulS2 < 40 && verdeS2 < 40) {
    // Ambos sensores detectam branco (GAP)
    // seguir em frente
    motor1.run(FORWARD);
    motor2.run(FORWARD);
  }
  else if (vermelhoS1 > 60 && vermelhoS1 < 250 && azulS1 > 60 && azulS1 < 180 && verdeS1 > 50 && verdeS1 < 160 && vermelhoS2 > 50 && vermelhoS2 < 190 && azulS2 > 50 && azulS2 < 110 && verdeS2 > 50 && verdeS2 < 120) {
    // Ambos sensores detectam preto (Encruzilhada)
    // seguir em frente
    motor1.run(FORWARD);
    motor2.run(FORWARD);
  }
  else if (vermelhoS1 > 60 && vermelhoS1 < 250 && azulS1 > 60 && azulS1 < 180 && verdeS1 > 50 && vermelhoS2 < 40 && azulS2 < 40 && verdeS2 < 40) {
    // Sensor 1 detecta preto e Sensor 2 detecta branco
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
  }
  else if (vermelhoS1 < 60 && azulS1 < 60 && verdeS1 < 60 && vermelhoS2 > 50 && vermelhoS2 < 190 && azulS2 > 50 && azulS2 < 110 && verdeS2 > 50 && verdeS2 < 120) {
    // Sensor 1 detecta preto e Sensor 2 detecta branco
    motor1.run(BACKWARD);
    motor2.run(FORWARD);
  }
  else if (vermelhoS1 > 250 && azulS1 > 180 && verdeS1 > 160 && vermelhoS2 < 40 && azulS2 < 40 && verdeS2 < 40) {//esquerda detectou 
    // Vire para a esquerda
    motor1.run(BACKWARD);
    motor2.run(FORWARD);
  }
  else if (vermelhoS1 < 60 && azulS1 < 60 && verdeS1 < 60 && vermelhoS2 > 190 && azulS2 > 110 && verdeS2 > 120) {//direita detectou verde
    // Vire para a direita
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
  }
  else if (vermelhoS1 > 260 && azulS1 > 160 && verdeS1 > 160 && vermelhoS2 > 170 && azulS2 > 100 && verdeS2 > 100) {//os dois detectam o verde 
    //
    motor1.run(FORWARD); // Motor esquerdo para frente
  motor2.run(BACKWARD); // Motor direito para trás
  delay(4700);
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

void virar180graus(){
  motor1.run(RELEASE); //parar
  motor2.run(RELEASE); //parar

}

