#include <MD_TCS230.h>

// Configuração dos pinos
const int S0_PIN = 2;
const int S1_PIN = 3;
const int S2_PIN = 4;
const int S3_PIN = 5;
const int OUT_PIN = 6;

// Criação do objeto MD_TCS230
MD_TCS230 colorSensor(S0_PIN, S1_PIN, S2_PIN, S3_PIN, OUT_PIN);

void setup() {
  // Inicialização da comunicação serial
  Serial.begin(9600);

  // Configuração do sensor para frequência desligada (0%)
  colorSensor.setFrequency(TCS230_FREQ_OFF);
}

void loop() {
  // Realiza uma leitura das intensidades de cor
  int red = colorSensor.readRed();
  int green = colorSensor.readGreen();
  int blue = colorSensor.readBlue();

  // Verifica as intensidades de cor para identificar a cor predominante
  if (red > green && red > blue) {
    Serial.println("Cor: Vermelho");
  } else if (green > red && green > blue) {
    Serial.println("Cor: Verde");
  } else if (blue > red && blue > green) {
    Serial.println("Cor: Azul");
  } else {
    Serial.println("Cor: Desconhecida");
  }

  delay(1000);
}
