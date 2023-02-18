/* 
   IS727272 - Cordero Hernández, Marco Ricardo
   Nota para implementaciones futuras: los pines ADC2
   no pueden ser utilizados al mismo tiempo que el Wi-Fi,
   en su lugar, utilizar los pines ADC1 cuando sea posible

   -- Pines convertidores análogo a digitial --
   ADC1: 32, 33, 34, 35, 36, 39
   ADC2: 2, 4, 12, 13, 14, 15, 25, 26, 27
*/

const int potPin = 34; // GPIO para valor análogo
bool maxSet = false; // Bandera para valor máximo definido
int setter = 15; // GPIO para registro de valor máximo

int potValue = 0; // Variable para valor de potenciómetro
float maxPotValue = 0; // Valor máximo del potenciómetro

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(setter, INPUT); // GPIO 15 en modo de lectura
}

void loop() {
  delay(750); // Espera de 3/4 de segundo

  if (maxSet) { // Si el valor máximo se ha definido...
    potValue = analogRead(potPin); // Lectura de valor análogo
    Serial.print("Read value: ");
    Serial.println(potValue);
    Serial.print("Percentage: ");
    Serial.print((potValue / maxPotValue)*100);
    Serial.println("%\n");
  } else if (digitalRead(setter) == 1) { // ... Si no, y se ha presionado el push button
    // Setteo de valor máximo (dependiente del usuario)
    maxPotValue = analogRead(potPin);
    maxSet = true;
  } else Serial.println("Max value not set!"); // Si no, indicar ausencia de valor máximo
}