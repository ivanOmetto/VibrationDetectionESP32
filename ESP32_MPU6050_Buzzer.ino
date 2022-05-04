// sudo chmod 666 /dev/ttyUSB0 
// ============================== //
// Feito por: Ivan Ometto
// https://github.com/ivanOmetto
// ============================== //

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;
const int freq = 2000;
const int channel = 0;
const int resolution = 8;

void testValues(float num, int maxV, int minV) {
  if (num >= maxV || num <= minV){
    ledcWriteTone(channel, 2000);
    delay(10);
  } else {
    ledcWriteTone(channel, 0);
  }
}

void setup(void) {
  ledcSetup(channel, freq, resolution);
  ledcAttachPin(15, channel);
  
  Serial.begin(115200);
  while (!Serial)
    delay(10);
  
  Serial.println("MPU6050 test!");

  if (!mpu.begin()) {
    Serial.println("Falha encontrar MPU6050!");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Encontrado!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  delay(100);
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  Serial.print("Temperatura:");
  Serial.print(temp.temperature);
  Serial.print("\tx-aceleracao:");
  Serial.print(a.acceleration.x);
  Serial.print("\ty-aceleracao:");
  Serial.print(a.acceleration.y);
  Serial.print("\tz-aceleracao:");
  Serial.print(a.acceleration.z);
  Serial.print("\tx-giroscopio:");
  Serial.print(g.gyro.x);
  Serial.print("\ty-giroscopio:");
  Serial.print(g.gyro.y);
  Serial.print("\tz-giroscopio:");
  Serial.println(g.gyro.z);

  testValues(a.acceleration.x, 15, -3);
  testValues(a.acceleration.y, 3, -3);
  testValues(a.acceleration.z, 3, -3);
  testValues(g.gyro.x, 3, -3);
  testValues(g.gyro.y, 3, -3);
  testValues(g.gyro.z, 3, -3);
  testValues(temp.temperature, 33, 0);

  delay(10);
}
