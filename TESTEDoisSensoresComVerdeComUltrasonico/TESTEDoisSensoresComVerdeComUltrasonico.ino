#include <AFMotor.h>
#include <HCSR04.h>

AF_DCMotor motorEsquerdo(3);  // Motor Esquerdo conectado ao pino 3
AF_DCMotor motorDireito(4);   // Motor Direito conectado ao pino 4

#define sensorEsquerdo A10
#define sensorDireito A15
#define LIMIAR 140       // Limiar para detecção da linha preta
#define DISTANCIA_OBSTACULO_MIN 1 // Distância mínima para identificar obstáculo
#define DISTANCIA_OBSTACULO_MAX 4 // Distância máxima para identificar obstáculo

UltraSonicDistanceSensor distanceSensor(31, 30);  // Pino de trigger: 31, Pino de echo: 30

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

int corVerdeS1;
int corVermelhoS1;
int corAzulS1;

int corVerdeS2;
int corVermelhoS2;
int corAzulS2;

void setup() {
  pinMode(sensorEsquerdo, INPUT);
  pinMode(sensorDireito, INPUT);
  int Velocidade = 220;
  motorEsquerdo.setSpeed(Velocidade);
  motorDireito.setSpeed(Velocidade);

  Serial.begin(9600);

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

  digitalWrite(s0_1, HIGH);
  digitalWrite(s1_1, LOW);

  digitalWrite(s0_2, HIGH);
  digitalWrite(s1_2, LOW);
}

void loop() {
  int leituraEsquerda = analogRead(sensorEsquerdo);
  int leituraDireita = analogRead(sensorDireito);

  int distanciaObstaculo = distanceSensor.measureDistanceCm(); // Realiza a leitura da distância do sensor ultrassônico em cm

  if (distanciaObstaculo > DISTANCIA_OBSTACULO_MIN && distanciaObstaculo < DISTANCIA_OBSTACULO_MAX) {
    // Obstáculo detectado pelo sensor ultrassônico
    Desviar();
  } else {
    color();

    if (corVermelhoS1 > 25 && corVerdeS1 > 25 && corAzulS1 > 25) {
      direitaVerde();
    } else if (corVermelhoS2 > 110) {
      esquerdaVerde();
    } else if (corVermelhoS2 > 110 && corVerdeS2 > 75 && corAzulS2 > 75) {
      becoVerde();
    } else {
      seguidordeLinha();
    }
  }
}

void Desviar() {
  motorEsquerdo.setSpeed(255);
  motorDireito.setSpeed(255);

  motorEsquerdo.run(BACKWARD);
  motorDireito.run(BACKWARD);

  delay(400);

  motorEsquerdo.run(BACKWARD);
  motorDireito.run(FORWARD);

  delay(450);
}

void color() {
  digitalWrite(s2_1, LOW);
  digitalWrite(s3_1, LOW);
  int corVermelhoS1 = pulseIn(out_1, digitalRead(out_1) == HIGH ? LOW : HIGH);
  
  digitalWrite(s2_1, HIGH);
  digitalWrite(s3_1, HIGH);
  int corVerdeS1 = pulseIn(out_1, digitalRead(out_1) == HIGH ? LOW : HIGH);
  
  digitalWrite(s2_1, LOW);
  digitalWrite(s3_1, HIGH);
  int corAzulS1 = pulseIn(out_1, digitalRead(out_1) == HIGH ? LOW : HIGH);

  digitalWrite(s2_2, LOW);
  digitalWrite(s3_2, LOW);
  int corVermelhoS2 = pulseIn(out_2, digitalRead(out_2) == HIGH ? LOW : HIGH);
  
  digitalWrite(s2_2, HIGH);
  digitalWrite(s3_2, HIGH);
  int corVerdeS2 = pulseIn(out_2, digitalRead(out_2) == HIGH ? LOW : HIGH);
  
  digitalWrite(s2_2, LOW);
  digitalWrite(s3_2, HIGH);
  int corAzulS2 = pulseIn(out_2, digitalRead(out_2) == HIGH ? LOW : HIGH);

  Serial.print("S1 - Vermelho: ");
  Serial.print(corVermelhoS1);
  Serial.print(", Verde: ");
  Serial.print(corVerdeS1);
  Serial.print(", Azul: ");
  Serial.println(corAzulS1);

  Serial.print("S2 - Vermelho: ");
  Serial.print(corVermelhoS2);
  Serial.print(", Verde: ");
  Serial.print(corVerdeS2);
  Serial.print(", Azul: ");
  Serial.println(corAzulS2);
}

void direitaVerde() {
  motorEsquerdo.run(FORWARD);
  motorDireito.run(FORWARD);
}

void esquerdaVerde() {
  motorEsquerdo.run(BACKWARD);
  motorDireito.run(FORWARD);
}

void becoVerde() {
  motorEsquerdo.run(FORWARD);
  motorDireito.run(BACKWARD);
}

void seguidordeLinha() {
  if (leituraEsquerda < LIMIAR && leituraDireita < LIMIAR) {
    // Linha reta
    motorEsquerdo.run(FORWARD);
    motorDireito.run(FORWARD);
  } else if (leituraEsquerda < LIMIAR && leituraDireita >= LIMIAR) {
    // Curva para a esquerda
    motorEsquerdo.run(BACKWARD);
    motorDireito.run(FORWARD);
  } else if (leituraEsquerda >= LIMIAR && leituraDireita < LIMIAR) {
    // Curva para a direita
    motorEsquerdo.run(FORWARD);
    motorDireito.run(BACKWARD);
  }
}
