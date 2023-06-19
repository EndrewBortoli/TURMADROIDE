#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <AFMotor.h>

AF_DCMotor motor[] = {3, 4}; // 0 é Esquerdo e 1 é Direito

const int trigPin = A11;
const int echoPin = A12;

int sensorLateralEsquerda = A14;
int sensorCentralEsquerda = A13;
int sensorCentralDireita = A12;
int sensorLateralDireita = A11;

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
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);


  // Calibração automática para a cor branca
  Serial.println("Realizando a calibracao automatica para a cor branca...");
  delay(2000);
  calibrar(sensorLateralEsquerda, valorMinimoBranco, valorMaximoBranco);
  calibrar(sensorCentralEsquerda, valorMinimoBranco, valorMaximoBranco);
  calibrar(sensorCentralDireita, valorMinimoBranco, valorMaximoBranco);
  calibrar(sensorLateralDireita, valorMinimoBranco, valorMaximoBranco);

  delay(6000);

  // Calibração automática para a cor preta
  Serial.println("Realizando a calibracao automatica para a cor preta...");
  delay(2000);
  calibrar(sensorLateralEsquerda, valorMinimoPreto, valorMaximoPreto);
  calibrar(sensorCentralEsquerda, valorMinimoPreto, valorMaximoPreto);
  calibrar(sensorCentralDireita, valorMinimoPreto, valorMaximoPreto);
  calibrar(sensorLateralDireita, valorMinimoPreto, valorMaximoPreto);

    delay(6000);

  // Calibração automática para a cor verde ( todos sensores )
  Serial.println("Realizando a calibracao automatica para a cor verde...");
  delay(2000);
  calibrar(sensorLateralEsquerda, valorMinimoPreto, valorMaximoPreto);
  calibrar(sensorCentralEsquerda, valorMinimoPreto, valorMaximoPreto);
  calibrar(sensorCentralDireita, valorMinimoPreto, valorMaximoPreto);
  calibrar(sensorLateralDireita, valorMinimoPreto, valorMaximoPreto);

    delay(6000);

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

  // Verifica se os dois sensores centrais identificaram a cor verde ao mesmo tempo
  if (corCentralEsquerda == "Verde" && corCentralDireita == "Verde")
  {
    // Vira 180 graus
    girar180Graus();
  }
  // Verifica se apenas o sensor central da esquerda identificou a cor verde
  else if (corCentralEsquerda == "Verde")
  {
    // Vira 90 graus para a esquerda
    girar90GrausEsquerda();
  }
  // Verifica se apenas o sensor central da direita identificou a cor verde
  else if (corCentralDireita == "Verde")
  {
    // Vira 90 graus para a direita
    girar90GrausDireita();
  }

  // Verifica a distância do objeto pelo sensor ultrassônico
  if (medirDistancia() <= 10)
  {
    // Executa a sequência de desvio do objeto
    desviarObjeto();
  }

  delay(500);
}

void calibrar(int sensorPin, int &valorMinimo, int &valorMaximo)
{
  for (int i = 0; i < 20; i++)
  {
    int valor = analogRead(sensorPin);
    if (valor < valorMinimo)
    {
      valorMinimo = valor;
    }
    if (valor > valorMaximo)
    {
      valorMaximo = valor;
    }
    delay(100);
  }
}

void calibrar(int sensorPin, int &valorMinimoPreto, int &valorMaximoPreto, int &valorMinimoBranco, int &valorMaximoBranco)
{
  for (int i = 0; i < 20; i++)
  {
    int valor = analogRead(sensorPin);
    if (valor < valorMinimoPreto)
    {
      valorMinimoPreto = valor;
    }
    if (valor > valorMaximoPreto)
    {
      valorMaximoPreto = valor;
    }
    if (valor < valorMinimoBranco)
    {
      valorMinimoBranco = valor;
    }
    if (valor > valorMaximoBranco)
    {
      valorMaximoBranco = valor;
    }
    delay(100);
  }
}

String determinarCor(int valor, int valorMinimoPreto, int valorMaximoPreto, int valorMinimoBranco, int valorMaximoBranco)
{
  int valorMapeado = map(valor, valorMinimoPreto, valorMaximoPreto, 0, 255);

  if (valorMapeado < 50)
  {
    return "Preto";
  }
  else if (valorMapeado < 200)
  {
    return "Verde";
  }
  else
  {
    return "Branco";
  }
}

void girar90GrausEsquerda()
{
  // Implemente aqui a lógica para o robô girar 90 graus para a esquerda
  // Utilize os motores para realizar a rotação desejada
  // Você pode ajustar a velocidade e duração da rotação conforme necessário
  motor[0].run(BACKWARD);
  motor[1].run(BACKWARD);
  delay(1000);
  motor[0].run(RELEASE);
  motor[1].run(RELEASE);
}

void girar90GrausDireita()
{
  // Implemente aqui a lógica para o robô girar 90 graus para a direita
  // Utilize os motores para realizar a rotação desejada
  // Você pode ajustar a velocidade e duração da rotação conforme necessário
  motor[0].run(FORWARD);
  motor[1].run(FORWARD);
  delay(1000);
  motor[0].run(RELEASE);
  motor[1].run(RELEASE);
}

void girar180Graus()
{
  // Implemente aqui a lógica para o robô girar 180 graus
  // Utilize os motores para realizar a rotação desejada
  // Você pode ajustar a velocidade e duração da rotação conforme necessário
  motor[0].run(FORWARD);
  motor[1].run(FORWARD);
  delay(2000);
  motor[0].run(RELEASE);
  motor[1].run(RELEASE);
}

int medirDistancia()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  return distance;
}

void desviarObjeto()
{
  // Implemente aqui a lógica para o robô desviar do objeto
  // Utilize os motores para realizar o desvio
  // Você pode ajustar a velocidade e duração do desvio conforme necessário

  // Exemplo: girar 90 graus para a direita
  girar90GrausDireita();

  // Exemplo: mover para frente por 1 segundo
  motor[0].run(FORWARD);
  motor[1].run(FORWARD);
  delay(1000);
  motor[0].run(RELEASE);
  motor[1].run(RELEASE);

  // Exemplo: girar 90 graus para a esquerda
  girar90GrausEsquerda();

  // Exemplo: mover para frente por 1 segundo
  motor[0].run(FORWARD);
  motor[1].run(FORWARD);
  delay(1000);
  motor[0].run(RELEASE);
  motor[1].run(RELEASE);

  // Exemplo: girar 90 graus para a esquerda
  girar90GrausEsquerda();
}