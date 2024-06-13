#include <DHT.h>

#define DHTPIN 2      // Pino onde o sensor está conectado
#define DHTTYPE DHT22 // Sensor AM2302 é igual ao DHT22

DHT dht(DHTPIN, DHTTYPE);

const unsigned long interval5Min = 300000; // Intervalo de 5 minutos em milissegundos
const unsigned long interval1Hour = 3600000; // Intervalo de 1 hora em milissegundos

unsigned long previousMillis5Min = 0;
unsigned long previousMillis1Hour = 0;

float tempSum = 0;
int tempCount = 0;

void setup() {
  Serial.begin(9600);
  dht.begin();
  Serial.println("Hora,Temperatura,Umidade,Media de Temperatura");
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis5Min >= interval5Min) {
    previousMillis5Min = currentMillis;
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t)) {
      Serial.println("Falha na leitura do sensor!");
      return;
    }

    Serial.print(currentMillis / 1000);
    Serial.print(",");
    Serial.print(t);
    Serial.print(",");
    Serial.print(h);
    Serial.print(",");
    Serial.println();

    tempSum += t;
    tempCount++;
  }

  if (currentMillis - previousMillis1Hour >= interval1Hour) {
    previousMillis1Hour = currentMillis;
    float tempAvg = tempSum / tempCount;

    Serial.print("Media de Temperatura da Ultima Hora: ");
    Serial.println(tempAvg);

    Serial.print("Hora: ");
    Serial.print(currentMillis / 1000);
    Serial.print(", Media de Temperatura da Ultima Hora: ");
    Serial.println(tempAvg);

    tempSum = 0;
    tempCount = 0;
  }
}
