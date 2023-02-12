/* IS727272 - Cordero Hernández, Marco Ricardo
 * La manera en que esta implementación funciona es mediante
 * el uso del sistema de archivos inteno (SPIFFS) de la ESP321.
 * De esta forma, no se necesita especificar la estructura HTML
 * dentro de este mismo archivo.
 * El IDE de Arduino trabaja con el plugin de SPIFFS de forma
 * que se suben los archivos contenidos en la carpeta /data
 * OJO: Al momento, solo Arduino 1.X.X soporta el plugin
 */
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

const char* ssid     = ""; // Nombre de red
const char* password = ""; // Contraseña de red

// Se pueden usar macros también para las siguientes constantes
const int ledPin = 2, outer_ledPin = 15;
String ledState;

// Inicialización de servidor web asíncrono
AsyncWebServer server(80);

// Reemplazo de valor de led en página web
String processor(const String& var){
  Serial.println(var);
  if(var == "STATE"){
    ledState = (digitalRead(ledPin)) ? "ON" : "OFF";
    Serial.print(ledState);
    return ledState;
  }
  return String();
}
 
void setup(){
  Serial.begin(115200);

  // LED interno y externo en modo de escritura
  pinMode(ledPin, OUTPUT);
  pinMode(outer_ledPin, OUTPUT);

  // Inicialización de sistema de archivos
  if(!SPIFFS.begin(true)){
    Serial.println("Ha ocurrido un error con el sistema de archivos\nIntenta de nuevo...");
    return;
  }

  // Conexión a WiFI
  WiFi.begin(ssid, password);
  Serial.print("Conectando a WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  // Imprimir IP asignada
  Serial.print("\r\nConexión exitosa\nIP asignada: ");
  Serial.println(WiFi.localIP());

  // Ruta a la raíz (página de inicio)
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Ruta a estilos
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
  });

  // Ruta para prender LEDs
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, HIGH); digitalWrite(outer_ledPin, HIGH);
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Ruta para apagar LEDs
  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, LOW); digitalWrite(outer_ledPin, LOW);
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Iniciar servidor
  server.begin();
}
 
void loop() {}