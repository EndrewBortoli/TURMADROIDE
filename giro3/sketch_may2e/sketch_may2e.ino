#include <Wire.h>
#include <MPU6050_6Axis_MotionApps20.h>

MPU6050 mpu;
int16_t ax, ay, az, gx, gy, gz;

void setup() 
{
  //Inicializa o giroscópio
  Wire.begin();
  mpu.initialize();
  Serial.begin(9600);

  //Configura o giroscópio
  mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_250);
  mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_2);

  //Verifica se o giroscópio está funcionando corretamente
  Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
}

void loop() 
{
  //Lê os valores do giroscópio
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  //Calcula o ângulo atual usando o giroscópio
  float angle = 0;
  float gyroXangle = 0;
  float elapsedTime, currentTime, previousTime = millis();
  float gyroXrate = 0;
  float angleOffset = 0;

  gyroXrate = (float)gx / 131.0; //131.0 é o fator de escala para o giroscópio de 250 graus/s
  currentTime = millis();
  elapsedTime = (currentTime - previousTime) / 1000.0;
  previousTime = currentTime;

  gyroXangle += gyroXrate * elapsedTime;
  angle = (0.96 * (angle + gyroXrate * elapsedTime)) + (0.04 * gyroXangle);
  angle -= angleOffset;

  //Imprime o ângulo atual no monitor serial
  Serial.print("Angle: ");
  Serial.println(angle);
}
