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

  if (corVermelhoS1 > 25 && corAzulS1 > 25 && corVerdeS1 > 20) {
    Serial.println("VERDE");
  }
  else {
    Serial.println("Outra cor");
  }
  
  Serial.print("Sensor 2 - ");

  if (corVermelhoS2 > 120 && corAzulS2 > 20 && corVerdeS2 > 10) {
    Serial.println("VERDE");
  }
  else {
    Serial.println("Outra cor");
  }

  delay(1000);
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
