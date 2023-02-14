// IS727272 - Cordero Hernández, Marco Ricardo
#include <WiFi.h>
#include <WiFiClient.h>

#define LED 15

// Nombre y contraseña del Acess Point
const char *ssid = "IoT MADNESS";
const char *password = "IS727272";
/* La contraseña debe tener como mínimo 8 caracteres, si no, creará
   una red abierta con el nombre de la tarjerta */

WiFiServer server(80);

void setup() {
  pinMode(LED, OUTPUT); // GPIO indicado en directiva pasada como salida

  Serial.begin(115200);
  Serial.println();
  Serial.println("Configurando Access Point...");

  // Si se desea una red abierta con nombre, se puede omitir el argumento de contraseña
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("Dirección IP de AP: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Servidor inicializado");
}

void loop() {
  WiFiClient client = server.available();   // Manejador para nuevos clientes

  if (client) {                             // Si hay un nuevo cliente,
    Serial.println("Nuevo cliente");        // notificar mediante la consola y
    String currentLine = "";                // definir una variable para maneja los datos de entrada
    while (client.connected()) {            // Repetir mientras el cliente este conectado, y
      if (client.available()) {             // si hay bytes para leer desde el cliente,
        char c = client.read();             // leer un byte y después
        Serial.write(c);                    // imprimirlo en el monitor serial

        if (c == '\n') {                    // Si el byte es un salto de línea...
          // significa que se obtuvieron dos saltos de línea seguidos,
          // es decir, se recibió una solicitud HTTP; se debe responder
          if (currentLine.length() == 0) {
            /* Los encabezados HTTP siempre comienzan con un status (ej. HTTP/1.1 200 OK)
               y el tipo de contenido, de forma que el cliente sabe qué es el contenido 
               Finalmente, la respuesta termina con un salto de línea */
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println(); // NO BORRAR

            // Después del encabezado, viene el contenido de la respuesta (HTML)
            client.print("Click <a href=\"/H\">aquí</a> para PRENDER el LED.<br>");
            client.print("Click <a href=\"/L\">aquí</a> para APAGAR el LED.<br>");

            client.println();
            break;
          } else {
            // Si se obtuvo una nueva línea, borrar el manejador
            currentLine = "";
          }
        } else if (c != '\r') {  // Si se obtuvo cualquier otra cosa (a excepción de un retorno de carro),
          currentLine += c;      // añadir los contenidos al manejador
        }

        // Revisar tipo de petición/acción solicitada
        if (currentLine.endsWith("GET /H")) { // Prender LED
          digitalWrite(LED, HIGH);
        } if (currentLine.endsWith("GET /L")) { // Apagar LED
          digitalWrite(LED, LOW);
        }
      }
    }
    
    // Terminar conexión
    client.stop();
    Serial.println("Cliente desconectado");
  }
}