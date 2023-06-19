#include <AFMotor.h>
AF_DCMotor  motor[] = {3,4}; // 0 é Esquerdo e 1 é Direito 

// Pinos de conexao do primeiro modulo TCS320
const int s0_1 = 2;
const int s1_1 = 3;
const int s2_1 = 4;
const int s3_1 = 5;
const int out_1 = 6;

// Pinos de conexao do segundo modulo TCS320
const int s0_2 = 7;
const int s1_2 = 8;
const int s2_2 = 9;
const int s3_2 = 10;
const int out_2 = 11;

// Variaveis cores do primeiro sensor
int red_1 = 0;
int green_1 = 0;
int blue_1 = 0;

// Variaveis cores do segundo sensor
int red_2 = 0;
int green_2 = 0;
int blue_2 = 0;


void setup()
{
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

  Serial.begin(9600);

  digitalWrite(s0_1, HIGH);
  digitalWrite(s1_1, LOW);

  digitalWrite(s0_2, HIGH);
  digitalWrite(s1_2, LOW);
}

void loop()
{
  // Detecta a cor do primeiro sensor
  color(1);
  // Mostra valores do primeiro sensor no serial monitor
  Serial.print("Sensor 1 - Verde: ");
  Serial.print(green_1);
  Serial.println();

  // Detecta a cor do segundo sensor
  color(2);
  // Mostra valores do segundo sensor no serial monitor
  Serial.print("Sensor 2 - Verde: ");
  Serial.print(green_2);
  Serial.println();


  // Verifica se a cor verde foi detectada no primeiro sensor
  if (green_1 < red_1 && green_1 < blue_1)
  {
    Serial.println("Verde - Sensor 1");
    // Adicione aqui o código para seguir a linha usando o primeiro sensor
  }

  // Verifica se a cor verde foi detectada no segundo sensor
  if (green_2 < red_2 && green_2 < blue_2)
  {
    Serial.println("Verde - Sensor 2");
    // Adicione aqui o código para seguir a linha usando o segundo sensor
  }
}

void color(int sensor)
{
  // Seleciona os pinos corretos com base no número do sensor
  int s0, s1, s2, s3, out;
  int red, green, blue;

  if (sensor == 1)
  {
    s0 = s0_1;
    s1 = s1_1;
    s2 = s2_1;
    s3 = s3_1;
    out = out_1;
  }
  else if (sensor == 2)
  {
    s0 = s0_2;
    s1 = s1_2;
    s2 = s2_2;
    s3 = s3_2;
    out = out_2;
  }
  else
  {
    return; // Sai da função se o número do sensor for inválido
  }

  // Ajusta a configuração dos pinos para detectar a cor verde
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);

  // Rotina que lê o valor das cores
  red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);

  // Ajusta a configuração dos pinos para detectar a cor preta
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);

  // Rotina que lê o valor das cores
  blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);

  // Ajusta a configuração dos pinos para detectar a cor branca
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);

  // Rotina que lê o valor das cores
  green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);

  // Atribui os valores lidos aos respectivos sensores
  if (sensor == 1)
  {
    red_1 = red;
    green_1 = green;
    blue_1 = blue;
  }
  else if (sensor == 2)
  {
    red_2 = red;
    green_2 = green;
    blue_2 = blue;
  }
}
