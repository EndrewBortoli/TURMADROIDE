#include <AFMotor.h>
#include <HCSR04.h>

AF_DCMotor motorEsquerdo(1);  // Motor Esquerdo conectado ao pino 1
AF_DCMotor motorDireito(2);   // Motor Direito conectado ao pino 2

#define sensorEsquerdo A8
#define sensorDireito A9
#define LIMIAR 800       // Limiar para detecção da linha preta
#define DISTANCIA_OBSTACULO_MIN 1 // Distância mínima para identificar obstáculo
#define DISTANCIA_OBSTACULO_MAX 4 // Distância máxima para identificar obstáculo

UltraSonicDistanceSensor distanceSensor(31, 30);  // Pino de trigger: 31, Pino de echo: 30

void setup() {
  pinMode(sensorEsquerdo, INPUT);
  pinMode(sensorDireito, INPUT);

  motorEsquerdo.setSpeed(215);
  motorDireito.setSpeed(215);

  Serial.begin(9600);
}

void loop() {
  int leituraEsquerda = analogRead(sensorEsquerdo);
  int leituraDireita = analogRead(sensorDireito);

  int distanciaObstaculo = distanceSensor.measureDistanceCm(); // Realiza a leitura da distância do sensor ultrassônico em cm

  if (distanciaObstaculo > DISTANCIA_OBSTACULO_MIN && distanciaObstaculo < DISTANCIA_OBSTACULO_MAX) {
    // Obstáculo detectado pelo sensor ultrassônico
    desviarObstaculo();
  } else {
    if (leituraEsquerda < LIMIAR && leituraDireita < LIMIAR) {
      // Ambos os sensores estão sobre a linha preta
      motorEsquerdo.run(FORWARD);
      motorDireito.run(FORWARD);
    } else if (leituraEsquerda < LIMIAR) {
      // Somente o sensor esquerdo está sobre a linha preta
      motorEsquerdo.run(BACKWARD);
      motorDireito.run(FORWARD);
    } else if (leituraDireita < LIMIAR) {
      // Somente o sensor direito está sobre a linha preta
      motorEsquerdo.run(FORWARD);
      motorDireito.run(BACKWARD);
    } else {
      // Nenhum sensor está sobre a linha preta
      motorEsquerdo.run(FORWARD);
      motorDireito.run(FORWARD);
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
  delay(1700); // Ajuste o tempo conforme necessário para o robô seguir em frente mais tempo
  motorEsquerdo.run(FORWARD);
  motorDireito.run(BACKWARD);
  delay(2000); // ajueste o tempo para o robô girar a esquerda
  motorEsquerdo.run(FORWARD);
  motorDireito.run(FORWARD);
  delay(3900); // ajuste o tempo para andar para frente
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