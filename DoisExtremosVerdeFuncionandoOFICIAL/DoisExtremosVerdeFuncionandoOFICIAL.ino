
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

int corVerdeS1;
int corVermelhoS1;
int corAzulS1;

int corVerdeS2;
int corVermelhoS2;
int corAzulS2;



void setup() {
  // put your setup code here, to run once:

  //Seta a velocidade inicial do motor
  motorEsquerdo.setSpeed(225); // Motor Esquerdo
  motorDireito.setSpeed(225); // Motor Direita
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

  digitalWrite(s0_1, HIGH);
  digitalWrite(s1_1, LOW);

  digitalWrite(s0_2, HIGH);
  digitalWrite(s1_2, LOW);
}

void loop() {
  color();

  if (corVermelhoS1 > 25 && corVerdeS1 > 25 && corAzulS1 > 25) {
    direitaVerde();  
  }else if (corVermelhoS2 > 110){
    esquerdaVerde();
  }else if (corVermelhoS2 > 110 && corVermelhoS2 > 110){
    becoVerde();
  }else{
    seguidordeLinha();
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


void seguidordeLinha(){
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

void direitaVerde(){
  int leftSensor = analogRead(A15); //sensor esquerdo
  int rightSensor = analogRead(A10); //sensor direito
  int valorSensor = 200;
  int valorSensorEsq = 100;
  motorEsquerdo.run(BACKWARD);
  motorDireito.run(FORWARD);
  delay(900);
  motorEsquerdo.run(FORWARD);
  motorDireito.run(FORWARD);
  delay(200);
  
  }
  
void esquerdaVerde(){
  int leftSensor = analogRead(A15); //sensor esquerdo
  int rightSensor = analogRead(A10); //sensor direito
  int valorSensor = 200;
  int valorSensorEsq = 100;
  motorEsquerdo.run(FORWARD);
  motorDireito.run(BACKWARD);
  delay(900);
  motorEsquerdo.run(FORWARD);
  motorDireito.run(FORWARD);
  delay(200);
  }

void becoVerde(){  
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
