// Pinos de conexão do primeiro sensor TCS320
const int s0_1 = 52;
const int s1_1 = 53;
const int s2_1 = 51;
const int s3_1 = 49;
const int out_1 = 50;

// Pinos de conexão do segundo sensor TCS320
const int s0_2 = 46;
const int s1_2 = 47;
const int s2_2 = 44;
const int s3_2 = 43;
const int out_2 = 45;

//Definindo as variaveis de cada cor
int vermelhoS1 = 0; //Defini um valor incial para a variavel do verde do sensor 1
int verdeS1 = 0; //Defini um valor inicial para a variavel do verde do sensor 1
int azulS1 = 0; //Defini um valor inicial para a variavel do verde do sensor 1

int vermelhoS2 = 0; //Defini um valor incial para a variavel do verde do sensor 2
int verdeS2 = 0; //Defini um valor inicial para a variavel do verde do sensor 2
int azulS2 = 0; //Defini um valor inicial para a variavel do verde do sensor 2

void setup() {
  // put your setup code here, to run once:
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

void loop() {
  // put your main code here, to run repeatedly:
  color(); // Chama a função para ler as cores dos sensores
Serial.print("Sensor 1 - ");
  Serial.print("Vermelho: ");
  Serial.print(vermelhoS1);
  Serial.print(" Verde: ");
  Serial.print(verdeS1);
  Serial.print(" Azul: ");
  Serial.println(azulS1);

  Serial.print("Sensor 2 - ");
  Serial.print("Vermelho: ");
  Serial.print(vermelhoS2);
  Serial.print(" Verde: ");
  Serial.print(verdeS2);
  Serial.print(" Azul: ");
  Serial.println(azulS2);

  delay(1000); // Aguarda 1 segundo antes de ler as cores novamente
}

void color() {
  //Rotina que le o valor das cores para o sensor 1
  digitalWrite(s2_1, LOW);
  digitalWrite(s3_1, LOW);
  //count OUT, pRed, RED
  vermelhoS1 = pulseIn(out_1, digitalRead(out_1) == HIGH ? LOW : HIGH);
  digitalWrite(s3_1, HIGH);
  //count OUT, pBLUE, BLUE
  azulS1 = pulseIn(out_1, digitalRead(out_1) == HIGH ? LOW : HIGH);
  digitalWrite(s2_1, HIGH);
  //count OUT, pGreen, GREEN
  verdeS1 = pulseIn(out_1, digitalRead(out_1) == HIGH ? LOW : HIGH);

  //Rotina que le o valor das cores para o sensor 2
  digitalWrite(s2_2, LOW);
  digitalWrite(s3_2, LOW);
  //count OUT, pRed, RED
  vermelhoS2 = pulseIn(out_2, digitalRead(out_2) == HIGH ? LOW : HIGH);
  digitalWrite(s3_2, HIGH);
  //count OUT, pBLUE, BLUE
  azulS2 = pulseIn(out_2, digitalRead(out_2) == HIGH ? LOW : HIGH);
  digitalWrite(s2_2, HIGH);
  //count OUT, pGreen, GREEN
  verdeS2 = pulseIn(out_2, digitalRead(out_2) == HIGH ? LOW : HIGH);

}
