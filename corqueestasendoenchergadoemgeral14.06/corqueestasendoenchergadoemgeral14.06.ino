int sensorLateralEsquerda = A1;
int sensorCentralEsquerda = A2;
int sensorCentralDireita = A3;
int sensorLateralDireita = A4;
int valorMinimoLE = 1023; // Valor inicial máximo para sensorLateralEsquerda
int valorMaximoLE = 0;    // Valor inicial mínimo para sensorLateralEsquerda
int valorMinimoCE = 1023; // Valor inicial máximo para sensorCentralEsquerda
int valorMaximoCE = 0;    // Valor inicial mínimo para sensorCentralEsquerda
int valorMinimoCD = 1023; // Valor inicial máximo para sensorCentralDireita
int valorMaximoCD = 0;    // Valor inicial mínimo para sensorCentralDireita
int valorMinimoLD = 1023; // Valor inicial máximo para sensorLateralDireita
int valorMaximoLD = 0;    // Valor inicial mínimo para sensorLateralDireita

void setup()
{
  pinMode(sensorLateralEsquerda, INPUT);
  pinMode(sensorCentralEsquerda, INPUT);
  pinMode(sensorCentralDireita, INPUT);
  pinMode(sensorLateralDireita, INPUT);
  Serial.begin(9600);

  // Calibração automática
  Serial.println("Realizando a calibracao automatica...");

  // Calibração dos sensores LDR
  calibrar(sensorLateralEsquerda, valorMinimoLE, valorMaximoLE);
  calibrar(sensorCentralEsquerda, valorMinimoCE, valorMaximoCE);
  calibrar(sensorCentralDireita, valorMinimoCD, valorMaximoCD);
  calibrar(sensorLateralDireita, valorMinimoLD, valorMaximoLD);

  Serial.println("Calibracao concluida.");
  Serial.println("Valores minimos e maximos:");
  Serial.print("Lateral Esquerda: ");
  Serial.print(valorMinimoLE);
  Serial.print(" - ");
  Serial.println(valorMaximoLE);
  Serial.print("Central Esquerda: ");
  Serial.print(valorMinimoCE);
  Serial.print(" - ");
  Serial.println(valorMaximoCE);
  Serial.print("Central Direita: ");
  Serial.print(valorMinimoCD);
  Serial.print(" - ");
  Serial.println(valorMaximoCD);
  Serial.print("Lateral Direita: ");
  Serial.print(valorMinimoLD);
  Serial.print(" - ");
  Serial.println(valorMaximoLD);
}

void loop()
{
  int valorLE = lerSensor(sensorLateralEsquerda, valorMinimoLE, valorMaximoLE);
  int valorCE = lerSensor(sensorCentralEsquerda, valorMinimoCE, valorMaximoCE);
  int valorCD = lerSensor(sensorCentralDireita, valorMinimoCD, valorMaximoCD);
  int valorLD = lerSensor(sensorLateralDireita, valorMinimoLD, valorMaximoLD);

  // Determina a cor com base na variação do valor
  String corLE = determinarCor(valorLE);
  String corCE = determinarCor(valorCE);
  String corCD = determinarCor(valorCD);
  String corLD = determinarCor(valorLD);

  // Mostra os valores e cores no monitor serial
  Serial.println("Valores dos sensores:");
  Serial.print("Lateral Esquerda: ");
  Serial.print(valorLE);
  Serial.print("\tCor: ");
  Serial.println(corLE);
  Serial.print("Central Esquerda: ");
  Serial.print(valorCE);
  Serial.print("\tCor: ");
  Serial.println(corCE);
  Serial.print("Central Direita: ");
  Serial.print(valorCD);
  Serial.print("\tCor: ");
  Serial.println(corCD);
  Serial.print("Lateral Direita: ");
  Serial.print(valorLD);
  Serial.print("\tCor: ");
  Serial.println(corLD);

  delay(500);
}

void calibrar(int sensorPin, int& valorMinimo, int& valorMaximo)
{
  Serial.print("Calibrando sensor...");
  for (int i = 0; i < 20; i++) {
    int valor = analogRead(sensorPin);
    if (valor < valorMinimo) {
      valorMinimo = valor;
    }
    if (valor > valorMaximo) {
      valorMaximo = valor;
    }
    delay(100);
  }
  Serial.println(" Concluido.");
}

int lerSensor(int sensorPin, int valorMinimo, int valorMaximo)
{
  int valor = analogRead(sensorPin);
  return map(valor, valorMinimo, valorMaximo, 0, 255);
}

String determinarCor(int valorMapeado)
{
  if (valorMapeado < 50) {
    return "Preta";
  } else if (valorMapeado < 200) {
    return "Verde";
  } else {
    return "Branca";
  }
}
