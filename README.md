# IoT_P2023
Workshops reestructurados de la clase de IoT (Primavera 2023)
Repositorio original: https://github.com/edmundormz/IoT_Workshops

## Demostraciones (en inglés)
- Workshop 1: [Imagen](https://drive.google.com/file/d/19j8upjem1mptYsQ_5tSg-P-I5B2oDtM6/view?usp=sharing)
- Workshop 2: [Video](https://youtu.be/Y87mb693c-8)
- Workshop 3: [Video](https://drive.google.com/file/d/1P6NaF_ceu2lAjYbSCZ4WGOurKoFiBcuD/view?usp=sharing); [Discusión (esp)](https://youtu.be/eOIkSxJtZ8E)

## Errores conocidos/encontrados
- Workshop 1:
  * La dirección IP se imprime en otra línea
    * *Solución*: cambiar *Serial.println()* por *Serial.print()*

- Workshop 2:
  * No es posible la carga de archivos a la ESP32
    * *Solución*: descargar [plugin de SPIFFS](https://github.com/me-no-dev/arduino-esp32fs-plugin/releases/)
    * **Nota**: el plugin no funciona para Arduino 2.0, utilizar Arduino 1.X en su lugar

- Workshop 3:
  * No funciona el Access Point con el SSID proporcionado
    * *Solución*: verificar que la contraseña tenga un mínimo de 8 caracteres
    * **Nota**: la función *WiFi.softAP(ssid, password)* fallará sin lo anterior, pero no habrá ningún warning, por lo que habrá que verificarlo manualmente

  * Las conexiones no funcionan como se esperaban
    * *Solución*: rezar y esperar un milagro
    * **Nota**: el voltaje de los GPIOS de la ESP32 no puede convertirse a 5V, únicamente el pin VIN suministra este voltaje cuando se energiza la tarjeta mediante micro-usb, sin embargo, no se puede poner en bajo, estaría atada a alto. (Ver discusión)