#include <IRremote.h>

int IR_RECEIVE_PIN = 11; // Define o pino do sensor infravermelho
IRrecv irrecv(IR_RECEIVE_PIN);
decode_results results;

void setup() {
  Serial.begin(9600); // Inicia a comunicação serial
}

void loop() {
  if (irrecv.decode(&results)) { // Verifica se há dados para serem lidos
    Serial.print("Valor recebido: ");
    Serial.print(results.value, HEX); // Exibe o valor recebido como um número hexadecimal
    Serial.println(); // Adiciona uma nova linha após exibir o valor
    irrecv.resume(); // Prepara o sensor para a próxima leitura
  }
}
