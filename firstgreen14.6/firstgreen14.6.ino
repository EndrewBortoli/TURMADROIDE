int sensorLateralEsquerda = A1;
int sensorCentralEsquerda = A2;
int sensorCentralDireita = A3;
int sensorLateralDireita = A4;
int valorMinimo = 1023; // Valor inicial máximo
int valorMaximo = 0;    // Valor inicial mínimo

void setup()
{
  pinMode(sensorLateralEsquerda, INPUT);
  pinMode(sensorCentralEsquerda, INPUT);
  pinMode(sensorCentralDireita, INPUT);
  pinMode(sensorLateralDireita, INPUT);
  Serial.begin(9600);

  // Calibração automática
  Serial.println("Realizando a calibracao automatica...");

  // Calibração da cor branca
  delay(2000);
  Serial.println("Calibrando cor branca...");
  for (int i = 0; i < 20; i++) {
    int valor = analogRead(sensorCentralEsquerda);
    if (valor > valorMaximo) {
      valorMaximo = valor;
    }
    delay(100);
  }

  // Calibração da cor preta
  delay(2000);
  Serial.println("Calibrando cor preta...");
  for (int i = 0; i < 20; i++) {
    int valor = analogRead(sensorCentralEsquerda);
    if (valor < valorMinimo) {
      valorMinimo = valor;
    }
    delay(100);
  }

  // Calibração da cor verde
  delay(2000);
  Serial.println("Calibrando cor verde...");
  for (int i = 0; i < 20; i++) {
    int valor = analogRead(sensorCentralEsquerda);
    // Ignora valores próximos do mínimo e máximo
    if (valor > valorMinimo && valor < valorMaximo) {
      // Ignora valores que estão muito próximos dos extremos
      if (valor < valorMaximo - 50 && valor > valorMinimo + 50) {
        // Não atualiza os valores mínimos e máximos
        continue;
      }
    }
    if (valor < valorMinimo) {
      valorMinimo = valor;
    }
    if (valor > valorMaximo) {
      valorMaximo = valor;
    }
    delay(100);
  }

  Serial.println("Calibracao concluida.");
  Serial.print("Valor minimo: ");
  Serial.println(valorMinimo);
  Serial.print("Valor maximo: ");
  Serial.println(valorMaximo);
}

void loop()
{
  int valorCentralEsquerda = analogRead(sensorCentralEsquerda);

  // Mapeia o valor lido para o intervalo [0, 255] para facilitar a visualização
  int valorMapeado = map(valorCentralEsquerda, valorMinimo, valorMaximo, 0, 255);

  // Determina a cor com base na variação do valor
  String cor;
  if (valorMapeado < 50) {
    cor = "Preta";
  } else if (valorMapeado < 200) {
    cor = "Verde";
  } else {
    cor = "Branca";
  }

  Serial.print("Valor lido: ");
  Serial.print(valorCentralEsquerda);
  Serial.print("\tValor mapeado: ");
  Serial.print(valorMapeado);
  Serial.print("\tCor: ");
  Serial.println(cor);

  delay(500);
}
