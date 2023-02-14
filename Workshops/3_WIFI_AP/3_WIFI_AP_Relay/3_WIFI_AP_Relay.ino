// IS727272 - Cordero Hernández, Marco Ricardo
// Revisar 3_WIFI_AP.ino para comentarios detallados
#include <WiFi.h>
#include <WiFiClient.h>

#define RELAY 15

const char *ssid = "IoT Madness";
const char *password = "IS727272";

WiFiServer server(80);

void setup() {
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, HIGH);

  Serial.begin(115200);
  Serial.println();
  Serial.println("Configurando Access Point...");

  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("Dirección IP de AP: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Servidor inicializado");
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("Nuevo cliente");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            client.print("Click <a href=\"/L\">aquí</a> para PRENDER el LED.<br>");
            client.print("Click <a href=\"/H\">aquí</a> para APAGAR el LED.<br>");

            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }

        if (currentLine.endsWith("GET /H")) {
          digitalWrite(RELAY, HIGH);
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(RELAY, LOW);
        }
      }
    }
    
    client.stop();
    Serial.println("Cliente desconectado");
  }
}