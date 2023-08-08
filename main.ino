#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "";         // Cambia "TU_SSID" por el nombre de tu red Wi-Fi
const char* password = "";  // Cambia "TU_CONTRASEÑA" por la contraseña de tu red Wi-Fi
const char* url = "";
WiFiClient wifiClient;
HTTPClient http;

const int ledPin = D4;
const int interval = 30;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);  // Configura el pin del LED como salida
  digitalWrite(ledPin, HIGH);  // Apaga el LED al inicio

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(ledPin, HIGH);
    delay(900);
    digitalWrite(ledPin, LOW);
    delay(100);
    Serial.println("Connecting to WiFi...");
  }

  digitalWrite(ledPin, LOW);
  Serial.printf("Connected to %s\n", ssid);
  Serial.print("IP address:");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    if (http.begin(wifiClient, url)) {
      int httpCode = http.GET();
      if (httpCode > 0) {
        Serial.printf("HTTP Code: %d\n", httpCode);
      } else {
        Serial.printf("Error en la conexión. %s\n", http.errorToString(httpCode).c_str());
      }
      http.end();
    } else {
      Serial.println("Error al iniciar la conexión HTTP");
    }
  } else {
    Serial.println("No se pudo conectar a la red Wi-Fi");
  }

  // Espera el tiempo definido antes de hacer la siguiente petición
  delay(interval * 1000);
}
