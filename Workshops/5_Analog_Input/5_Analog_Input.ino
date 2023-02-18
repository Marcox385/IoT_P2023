// IS727272 - Cordero Hernández, Marco Ricardo
const int potPin = 34; // GPIO 34
int potValue = 0; // Valor de potenciómetro

void setup() {
  Serial.begin(115200);
  delay(1000);
}

void loop() {
  delay(750); // Espera de 3/4 de segundo)

  potValue = analogRead(potPin); // Lectura de  valor análogo
  Serial.println(potValue);
}