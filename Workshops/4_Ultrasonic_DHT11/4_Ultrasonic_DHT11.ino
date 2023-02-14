// IS727272 - Cordero Hernández, Marco Ricardo
#include <NewPing.h>
#include <DHT.h>

// Directivas para pines y parámetros de sensor ultrásonico HC-SR04
#define TRIGGER_PIN 22
#define ECHO_PIN 23
#define MAX_DISTANCE 200

// Directivas para pin y parámetro de sensor de humedad DHT11
#define DHTPIN 32
#define DHTTYPE DHT11

// LED indicador
#define LED 15

// Funciones de librerías para inicializar sensores a utilizar
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
DHT dht(DHTPIN, DHTTYPE);

// Intervalo entre captuas de sensores
const int delta = 2000;

void setup() {
  Serial.begin(115200);
  dht.begin();

  // Para indicador LED
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  Serial.print("Tiempo entre capturas: ");
  Serial.print(delta/1000.0);
  Serial.println(" segundos");
}

void loop() {
  delay(delta); // Espera entre intervalos

  // Parpadeo del LED para indicar captura
  digitalWrite(LED, HIGH);
  delay(150);
  digitalWrite(LED, LOW);

  // Parte del HC-SR04
  Serial.print("\r\nDistancia del sensor: ");
  Serial.print(sonar.ping_cm());
  Serial.println("cm");

  // Parte del DHT11
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Fallo de lectura del sensor de humedad");
  }

  float hic = dht.computeHeatIndex(t, h, false);
  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.print("%\r\nTemperatura: ");
  Serial.print(t);
  Serial.print("° C\r\nSensación térmica: ");
  Serial.print(hic);
  Serial.println("° C");
}