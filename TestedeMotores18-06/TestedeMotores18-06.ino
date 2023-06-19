#include <AFMotor.h>

// Inicialização dos motores
AF_DCMotor motor1(3); // Motor esquerdo
AF_DCMotor motor2(4); // Motor direito

void setup() {
  motor1.setSpeed(200); // Velocidade do motor esquerdo
  motor2.setSpeed(200); // Velocidade do motor direito
}

void loop() {
  moveForward();
}

void moveForward() {
  motor1.run(FORWARD); // Motor esquerdo para frente
  motor2.run(FORWARD); // Motor direito para frente
}
