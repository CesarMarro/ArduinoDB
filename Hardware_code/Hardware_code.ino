#include "WiFi.h"
#include <HTTPClient.h>

const int irPin = 19;  // Pin conectado al pin OUT del sensor IR
int irState = 0;


const char* ssid = "Maza1601";
const char* password = "Marroza2024$$";
// Reemplaza con la IP local de tu servidor
const char* serverUrl = "http://192.168.1.42:3001/data";

void setup() {
  Serial.begin(115200);

  

  pinMode(irPin, INPUT);

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    Serial.println("Setup done");

  WiFi.begin(ssid, password);
  Serial.print("Conectando a WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n¡Conectado!");

}

void loop() {
  irState = digitalRead(irPin);

  delay(200);

  if (irState == LOW) {  // El sensor detecta un objeto
    Serial.println("Objeto detectado");
    if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json"); // Especificar el tipo de contenido

    // Crear un objeto JSON válido
    String postData = "{\"value\":1}"; // Datos a enviar como objeto JSON

    int httpCode = http.POST(postData);
    
    if (httpCode > 0) {
      String response = http.getString();
      Serial.println("Respuesta: " + response);
    } else {
      Serial.println("Error en la solicitud HTTP");
    }
    http.end();
  }
    delay(2000);  
  }
}

