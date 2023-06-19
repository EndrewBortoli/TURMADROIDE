class LightSensor
{
private:
    byte pin;

    void init()
    {
        pinMode(pin, INPUT);
    }

public:
    int minRead;
    int maxRead;
    byte blackThreshold;
    byte minGreen;
    byte maxGreen;
    int raw;
    byte light;
    bool black;

    LightSensor(byte pin, int minRead = 0, int maxRead = 1023, byte blackThreshold = 50)
    {
        this->pin = pin;
        this->minRead = minRead;
        this->maxRead = maxRead;
        this->blackThreshold = blackThreshold;
        init();
    }

    void read()
    {
        this->raw = analogRead(pin);
        this->light = constrain(map(raw, minRead, maxRead, 100, 0), 0, 100);
        this->black = light >= blackThreshold;
    }

    byte getLight()
    {
        read();
        return this->light;
    }

    int getRawRead()
    {
        read();
        return this->raw;
    }
};

// Criando uma instância da classe LightSensor
LightSensor sensor(A0);

void setup()
{
  // Inicializações do Arduino (se necessário)
}

void loop()
{
  // Seu código principal aqui
  byte luz = sensor.getLight();
  int leitura = sensor.getRawRead();

  // Faça algo com os valores lidos

  delay(1000); // Aguarde um segundo
}
