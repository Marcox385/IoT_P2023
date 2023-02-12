// IS727272 - Cordero Hernández, Marco Ricardo
#include "WiFi.h"

const char* ssid     = ""; // Nombre de red
const char* password = ""; // Contraseña de red

void setup(void) {
  Serial.begin(115200); // Baud rate | tasa de baudios
  
  // Conexión a WiFi
  WiFi.begin(ssid, password);

  /* Intentar conexión a la red;
     Imprimir "." mientras establece conexión */
  Serial.print("Conectando a WiFi");
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
  }

  // Imprimir IP asignada
  Serial.print("\r\nConexión exitosa\nIP asignada: ");
  Serial.print(WiFi.localIP());
}

void loop() {}