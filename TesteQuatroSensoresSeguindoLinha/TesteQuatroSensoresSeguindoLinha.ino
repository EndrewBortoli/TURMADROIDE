#include <AFMotor.h>
#include <HCSR04.h>

AF_DCMotor motorEsquerdo(3);  // Motor Esquerdo conectado ao pino 1
AF_DCMotor motorDireito(4);   // Motor Direito conectado ao pino 2

#define sensorEsquerdo A10
#define sensorDireito A15
#define sensorExtremoEsquerdo A8
#define sensorExtremoDireito A9

#define LIMIAR 140       // Limiar para detecção da linha preta

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


