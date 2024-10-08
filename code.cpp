#include "Wire.h"

#define EnderecoSensor 0x70
#define ComandoDeLeitura 0x51

int pino_buzzer = 12;
#define frequencia 4000

void setup() {
  Serial.begin(9600);
  Wire.begin();
  pinMode(pino_buzzer, OUTPUT);
}

void loop() {
  fazerLeituraDistancia();
  delay(100);
  int distancia = requisitarDistancia();
  Serial.println(distancia);

  if (distancia < 50) { // Menos de 50 cm
    tone(pino_buzzer, frequencia);
  } else if (distancia < 100) { // 50 cm a 100 cm
    tone(pino_buzzer, frequencia);
    delay(200);
    noTone(pino_buzzer);
    delay(200);
  } else if (distancia < 200) { // 1 a 2 metros
    tone(pino_buzzer, frequencia);
    delay(300);
    noTone(pino_buzzer);
    delay(300);
  } else if (distancia < 300) { // 2 a 3 metros
    tone(pino_buzzer, frequencia);
    delay(400);
    noTone(pino_buzzer);
    delay(400);
  } else if (distancia < 400) { // 3 a 4 metros
    tone(pino_buzzer, frequencia);
    delay(500);
    noTone(pino_buzzer);
    delay(500);
  } else if (distancia < 500) { // 4 a 5 metros
    tone(pino_buzzer, frequencia);
    delay(600);
    noTone(pino_buzzer);
    delay(600);
  } else {
    noTone(pino_buzzer); // Acima de 5 metros
  }
}


void fazerLeituraDistancia() {
  Wire.beginTransmission(EnderecoSensor);
  Wire.write(ComandoDeLeitura);
  Wire.endTransmission();
  delay(70);
}

int requisitarDistancia() {
  Wire.requestFrom(EnderecoSensor, 2);
  if (Wire.available() >= 2) {
    byte ByteAlto = Wire.read();
    byte ByteBaixo = Wire.read();
    int distancia = word(ByteAlto, ByteBaixo);
    return distancia;
  } else {
    return 0;
  }
}
