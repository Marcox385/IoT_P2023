// IS727272 - Cordero Hernández, Marco Ricardo
#include <WiFi.h>
#include <WiFiClient.h>

const char* ssid     = ""; // Nombre de red
const char* password = ""; // Contraseña de red

WiFiServer server(80);

// Macros para GPIO's a utilizar
#define INNER_LED 2
#define OUTER_LED 15
String led_status = "";

void setup() {
  Serial.begin(115200);

  // LED interno en modo de escritura
  pinMode(INNER_LED, OUTPUT);
  digitalWrite(INNER_LED, LOW); // Apagado

  // GPIO D15 en modo de escritura
  pinMode(OUTER_LED, OUTPUT);
  digitalWrite(OUTER_LED, LOW); // Apagado
  
  // Conexión WiFi
  WiFi.begin(ssid, password);
  Serial.print("Conectando a WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Conexión exitosa\nIP asignada: ");
  Serial.print(WiFi.localIP());

  // Inicialización de servidor web
  server.begin();
  Serial.println("Servidor listo");
}

void loop() {
  // Revisar si hay conexión de cliente
  WiFiClient client = server.available();
  if (!client) return;

  Serial.println("Nuevo cliente: ");
  Serial.print(client.remoteIP());

  // Esperar interacción del cliente
  while(!client.available()) delay(1);

  // Leer interacción del cliente
  String req = client.readStringUntil('\r');
  Serial.println(req);
  
  // Procesar petición del cliente
  if (req.indexOf("btn_ON") != -1) {
    digitalWrite(INNER_LED, HIGH);
    digitalWrite(OUTER_LED, HIGH);
    led_status = "ON";
  } else if (req.indexOf("btn_OFF") != -1) {
    digitalWrite(INNER_LED, LOW);
    digitalWrite(OUTER_LED, LOW);
    led_status = "OFF";
  }
       
  // Estructura de la página web
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); // No borrar esta línea
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head><meta charset=utf-8><title>IoT_Workshop 2: LED_WebServer</title></head>");
  client.println("<body><center><font face='Arial'>");
  client.println("<h1>Web Server with ESP32</h1>");
  client.println("<h1>EXPEDIENTE - Apellidos, Nombre(s)</h1>");
  client.println("<h2><font color='#009900'>Webserver 1.0</font></h2>");
  client.println("<h3>Main button</h3>");
  client.println("<br><br>");
  client.println("<a href='btn_ON'><button>Turn ON LED</button></a>");
  client.println("<a href='btn_OFF'><button>Turn OFF LED</button></a>");
  client.println("<br><br>");
  client.println(led_status);
  client.println("</font></center></body></html>");

  // Fin de comunicación con servidor
  Serial.print("Cliente desconectado: ");
  Serial.print(client.remoteIP());
  client.flush();
  client.stop();
}