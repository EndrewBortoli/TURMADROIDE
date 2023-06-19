int sensorLateralEsquerda = A1;
int sensorCentralEsquerda = A2;
int sensorCentralDireita = A3;
int sensorLateralDireita = A4;

int valorMinimoBranco = 1023; // Valor inicial máximo para branco
int valorMaximoBranco = 0;    // Valor inicial mínimo para branco
int valorMinimoPreto = 1023;  // Valor inicial máximo para preto
int valorMaximoPreto = 0;     // Valor inicial mínimo para preto

void setup()
{
  pinMode(sensorLateralEsquerda, INPUT);
  pinMode(sensorCentralEsquerda, INPUT);
  pinMode(sensorCentralDireita, INPUT);
  pinMode(sensorLateralDireita, INPUT);
  Serial.begin(9600);

  // Calibração automática para a cor branca
  Serial.println("Realizando a calibracao automatica para a cor branca...");
  delay(2000);
  calibrar(sensorLateralEsquerda, valorMinimoBranco, valorMaximoBranco);
  calibrar(sensorCentralEsquerda, valorMinimoBranco, valorMaximoBranco);
  calibrar(sensorCentralDireita, valorMinimoBranco, valorMaximoBranco);
  calibrar(sensorLateralDireita, valorMinimoBranco, valorMaximoBranco);

  // Calibração automática para a cor preta
  Serial.println("Realizando a calibracao automatica para a cor preta...");
  delay(2000);
  calibrar(sensorLateralEsquerda, valorMinimoPreto, valorMaximoPreto);
  calibrar(sensorCentralEsquerda, valorMinimoPreto, valorMaximoPreto);
  calibrar(sensorCentralDireita, valorMinimoPreto, valorMaximoPreto);
  calibrar(sensorLateralDireita, valorMinimoPreto, valorMaximoPreto);

  // Calibração automática para a cor verde (sensores centrais apenas)
  Serial.println("Realizando a calibracao automatica para a cor verde...");
  delay(2000);
  calibrar(sensorLateralEsquerda, valorMinimoPreto, valorMaximoPreto);
  calibrar(sensorCentralEsquerda, valorMinimoPreto, valorMaximoPreto);
  calibrar(sensorCentralDireita, valorMinimoPreto, valorMaximoPreto);
  calibrar(sensorLateralDireita, valorMinimoPreto, valorMaximoPreto);

  Serial.println("Calibracao concluida.");
  Serial.println("Valores para a cor branca:");
  Serial.print("Valor minimo: ");
  Serial.println(valorMinimoBranco);
  Serial.print("Valor maximo: ");
  Serial.println(valorMaximoBranco);
  Serial.println("Valores para a cor preta:");
  Serial.print("Valor minimo: ");
  Serial.println(valorMinimoPreto);
  Serial.print("Valor maximo: ");
  Serial.println(valorMaximoPreto);
}

void loop()
{
  int valorLateralEsquerda = analogRead(sensorLateralEsquerda);
  int valorCentralEsquerda = analogRead(sensorCentralEsquerda);
  int valorCentralDireita = analogRead(sensorCentralDireita);
  int valorLateralDireita = analogRead(sensorLateralDireita);

  String corLateralEsquerda = determinarCor(valorLateralEsquerda, valorMinimoPreto, valorMaximoPreto, valorMinimoBranco, valorMaximoBranco);
  String corCentralEsquerda = determinarCor(valorCentralEsquerda, valorMinimoPreto, valorMaximoPreto, valorMinimoBranco, valorMaximoBranco);
  String corCentralDireita = determinarCor(valorCentralDireita, valorMinimoPreto, valorMaximoPreto, valorMinimoBranco, valorMaximoBranco);
  String corLateralDireita = determinarCor(valorLateralDireita, valorMinimoPreto, valorMaximoPreto, valorMinimoBranco, valorMaximoBranco);

  Serial.print("Sensor Lateral Esquerda: ");
  Serial.println(corLateralEsquerda);
  Serial.print("Sensor Central Esquerda: ");
  Serial.println(corCentralEsquerda);
  Serial.print("Sensor Central Direita: ");
  Serial.println(corCentralDireita);
  Serial.print("Sensor Lateral Direita: ");
  Serial.println(corLateralDireita);

  delay(500);
}

void calibrar(int sensorPin, int &valorMinimo, int &valorMaximo)
{
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
}

void calibrar(int sensorPin, int &valorMinimoPreto, int &valorMaximoPreto, int &valorMinimoBranco, int &valorMaximoBranco)
{
  for (int i = 0; i < 20; i++) {
    int valor = analogRead(sensorPin);
    if (valor < valorMinimoPreto) {
      valorMinimoPreto = valor;
    }
    if (valor > valorMaximoPreto) {
      valorMaximoPreto = valor;
    }
    if (valor < valorMinimoBranco) {
      valorMinimoBranco = valor;
    }
    if (valor > valorMaximoBranco) {
      valorMaximoBranco = valor;
    }
    delay(100);
  }
}

String determinarCor(int valor, int valorMinimoPreto, int valorMaximoPreto, int valorMinimoBranco, int valorMaximoBranco)
{
  int valorMapeado = map(valor, valorMinimoPreto, valorMaximoPreto, 0, 255);

  if (valorMapeado < 50) {
    return "Preto";
  } else if (valorMapeado < 200) {
    return "Verde";
  } else {
    return "Branco";
  }
}
