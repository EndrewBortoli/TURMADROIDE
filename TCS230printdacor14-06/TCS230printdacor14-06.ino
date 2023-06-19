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

int = corVerdeS1
int = corVermelhoS1
int = corAzulS1

int = corVerdeS2
int = corVermelhoS2
int = corAzulS2


// Definindo as variáveis de cada cor
int vermelhoS1 = 0;
int verdeS1 = 0;
int azulS1 = 0;

int vermelhoS2 = 0;
int verdeS2 = 0;
int azulS2 = 0;

void setup() {
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
  color();
  Serial.print("Sensor 1 - ");
  if (vermelhoS1 < 60 && azulS1 < 60 && verdeS1 < 60)
    Serial.println("BRANCO");
  else if (vermelhoS1 > 60 && vermelhoS1 < 250 && azulS1 > 60 && azulS1 < 180 && verdeS1 > 50 && verdeS1 < 160)
    Serial.println("PRETO");
  else if (vermelhoS1 > 250 && azulS1 > 180 && verdeS1 > 160)
    Serial.println("VERDE");

  Serial.print("Sensor 2 - ");
  if (vermelhoS2 < 40 && azulS2 < 40 && verdeS2 < 40)
    Serial.println("BRANCO");
  else if (vermelhoS2 > 50 && vermelhoS2 < 190 && azulS2 > 50 && azulS2 < 110 && verdeS2 > 50 && verdeS2 < 120)
    Serial.println("PRETO");
  else if (vermelhoS2 > 190 && azulS2 > 110 && verdeS2 > 120)
    Serial.println("VERDE");

  delay(1000);
}

void color() {
  digitalWrite(s2_1, LOW);
  digitalWrite(s3_1, LOW);
  vermelhoS1 = pulseIn(out_1, digitalRead(out_1) == HIGH ? LOW : HIGH);
  digitalWrite(s3_1, HIGH);
  azulS1 = pulseIn(out_1, digitalRead(out_1) == HIGH ? LOW : HIGH);
  digitalWrite(s2_1, HIGH);
  verdeS1 = pulseIn(out_1, digitalRead(out_1) == HIGH ? LOW : HIGH);

  digitalWrite(s2_2, LOW);
  digitalWrite(s3_2, LOW);
  vermelhoS2 = pulseIn(out_2, digitalRead(out_2) == HIGH ? LOW : HIGH);
  digitalWrite(s3_2, HIGH);
  azulS2 = pulseIn(out_2, digitalRead(out_2) == HIGH ? LOW : HIGH);
  digitalWrite(s2_2, HIGH);
  verdeS2 = pulseIn(out_2, digitalRead(out_2) == HIGH ? LOW : HIGH);
}
