#include "DHT.h"

#define DHTPIN 2      // Pino onde o sensor está conectado
#define DHTTYPE DHT22 // Define o tipo do sensor (DHT22/AM2302)

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(2000); // Intervalo de leitura do sensor

  // Leitura da umidade
  float h = dht.readHumidity();
  // Leitura da temperatura em Celsius
  float t = dht.readTemperature();

  // Verifica se houve alguma falha na leitura
  if (isnan(h) || isnan(t)) {
    Serial.println("Falha ao ler o sensor DHT!");
    return;
  }

  // Imprime os valores no Serial Monitor
  Serial.print("Umidade: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.println(" *C");
}