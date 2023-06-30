#include <AFMotor.h>
#include <HCSR04.h>

AF_DCMotor motorEsquerdo(3);  // Motor Esquerdo conectado ao pino 1
AF_DCMotor motorDireito(4);   // Motor Direito conectado ao pino 2

#define sensorEsquerdo A10
#define sensorDireito A15
#define sensorExtremoEsquerdo A9
#define sensorExtremoDireito A13

#define LIMIAR 140       // Limiar para detecção da linha preta
#define DISTANCIA_OBSTACULO_MIN 1 // Distância mínima para identificar obstáculo
#define DISTANCIA_OBSTACULO_MAX 4 // Distância máxima para identificar obstáculo

UltraSonicDistanceSensor distanceSensor(51, 53);  // Pino de trigger: 51, Pino de echo: 53

void setup() {
  pinMode(sensorEsquerdo, INPUT);
  pinMode(sensorDireito, INPUT);
  pinMode(sensorExtremoEsquerdo, INPUT);
  pinMode(sensorExtremoDireito, INPUT);
  
  int Velocidade = 220;
  motorEsquerdo.setSpeed(Velocidade);
  motorDireito.setSpeed(Velocidade);

  Serial.begin(9600);
}

void loop() {
  int leituraEsquerda = analogRead(sensorEsquerdo);
  int leituraDireita = analogRead(sensorDireito);
  int leituraExtremoEsquerdo = analogRead(sensorExtremoEsquerdo);
  int leituraExtremoDireito = analogRead(sensorExtremoDireito);

  int distanciaObstaculo = distanceSensor.measureDistanceCm(); // Realiza a leitura da distância do sensor ultrassônico em cm

  if (distanciaObstaculo > DISTANCIA_OBSTACULO_MIN && distanciaObstaculo < DISTANCIA_OBSTACULO_MAX) {
    // Obstáculo detectado pelo sensor ultrassônico
    Desviar();
  } else {
    if (leituraExtremoEsquerdo < LIMIAR && leituraEsquerda < LIMIAR && leituraDireita < LIMIAR && leituraExtremoDireito < LIMIAR) {
      // Todos os sensores estão sobre a linha preta
      motorEsquerdo.run(FORWARD);
      motorDireito.run(FORWARD);
    } else if (leituraExtremoEsquerdo < LIMIAR && leituraEsquerda < LIMIAR) {
      // Somente o sensor extremo esquerdo e o sensor esquerdo estão sobre a linha preta
      motorEsquerdo.run(BACKWARD);
      motorDireito.run(FORWARD);
    } else if (leituraExtremoDireito < LIMIAR && leituraDireita < LIMIAR) {
      // Somente o sensor extremo direito e o sensor direito estão sobre a linha preta
      motorEsquerdo.run(FORWARD);
      motorDireito.run(BACKWARD);
    } else if (leituraExtremoEsquerdo < LIMIAR) {
      // Somente o sensor extremo esquerdo está sobre a linha preta
      motorEsquerdo.run(BACKWARD);
      motorDireito.run(FORWARD);
    } else if (leituraExtremoDireito < LIMIAR) {
      // Somente o sensor extremo direito está sobre a linha preta
      motorEsquerdo.run(FORWARD);
      motorDireito.run(BACKWARD);
    } else if (leituraEsquerda < LIMIAR && leituraDireita < LIMIAR) {
      // Somente os sensores central esquerdo e central direito estão sobre a linha preta
      motorEsquerdo.run(FORWARD);
      motorDireito.run(FORWARD);
    } else if (leituraEsquerda < LIMIAR) {
      // Somente o sensor central esquerdo está sobre a linha preta
      motorEsquerdo.run(BACKWARD);
      motorDireito.run(FORWARD);
    } else if (leituraDireita < LIMIAR) {
      // Somente o sensor central direito está sobre a linha preta
      motorEsquerdo.run(FORWARD);
      motorDireito.run(BACKWARD);
    } else {
      // Nenhum sensor está sobre a linha preta
      motorEsquerdo.run(FORWARD);
      motorDireito.run(FORWARD);
    }
  }
}

void Desviar() {
  // Lógica para desviar do obstáculo
    int leituraEsquerda = analogRead(sensorEsquerdo);
  int leituraDireita = analogRead(sensorDireito);

  motorEsquerdo.run(BACKWARD);
  motorDireito.run(BACKWARD);
  delay(500); // Ajuste o tempo conforme necessário para o robô recuar mais tempo
  motorEsquerdo.run(FORWARD);
  motorDireito.run(BACKWARD);
  delay(1200); // Ajuste o tempo conforme necessário para o robô girar mais tempo
  motorEsquerdo.run(FORWARD);
  motorDireito.run(FORWARD);
  delay(1650); // Ajuste o tempo conforme necessário para o robô seguir em frente mais tempo
  motorEsquerdo.run(BACKWARD);
  motorDireito.run(FORWARD);
  delay(1200); // ajuste o tempo para o robô girar a esquerda
  motorEsquerdo.run(FORWARD);
  motorDireito.run(FORWARD);
  delay(2300); // ajuste o tempo para andar para frente
  motorEsquerdo.run(BACKWARD);
  motorDireito.run(FORWARD);
  delay(1150); // ajuste o tempo para virar a esquerda
  motorEsquerdo.run(FORWARD);
  motorDireito.run(FORWARD);
  delay(500);
//  delay(2700); // ajuste o tempo para andar para frente 
  if (leituraEsquerda > LIMIAR && leituraDireita > LIMIAR){
  motorEsquerdo.run(FORWARD);
  motorDireito.run(BACKWARD);
  delay(1600); // ajuste o tempo para virar a direita
  }

}
