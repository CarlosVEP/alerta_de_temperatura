#include <Arduino.h>
#include <DHTesp.h>
#include <WiFi.h>

const int DHT_PIN = 15;
DHTesp dhtSensor;

//Configuración del WiFi(Wokwi)
const char* ssid = "Wokwi-GUEST";
const char* password = "";

const int LED_ROJO = 13;
const int TEMPERATURA_MAX = 32;
void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(LED_ROJO, OUTPUT);

  Serial.println("=== reto: led de emergencia cuando pasa los 32 grados y envío de la emergencia por wifi ===\n");
  //Configuración del sensor en el pin 15
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
  //pausa para estabilizar
  delay(2000);
  //Conexión WiFi
  Serial.print("Conectando a WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  int intentos = 0;
  while(WiFi.status()!=WL_CONNECTED&&intentos<20){
    delay(500);
    Serial.print(".");
    intentos++;
  }
  if(WiFi.status()==WL_CONNECTED){
    Serial.println("\n👍¡Conectado a WiFi!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
  }else{
    Serial.println("\n ⚠️No se pudo conectar al WiFi");
  }
  Serial.println("\nEnviando datos simulados a la nube... \n");
}

void loop() {
  //Leer temperatura y humedad
  TempAndHumidity data = dhtSensor.getTempAndHumidity();
  float temperatura = data.temperature;
  float humedad = data.humidity;

  //Verificar si la lectura fué exitosa
  if(isnan(temperatura) || isnan(humedad)){
    Serial.println("Error al leer el sensor DHT22");
  }else{
    //Formato simulado de envío IoT (como a ThingSpeak, MQTT, etc.)
    if(temperatura<=TEMPERATURA_MAX){
      Serial.println("--- Envío de datos IoT");
      Serial.print("Temperatura: ");
      Serial.print(temperatura, 1);
      Serial.println("C");
      Serial.print("Humedad: ");
      Serial.print(humedad, 1);
      Serial.println("%");
      Serial.printf("Timestamp: %lu ms\n", millis());
      Serial.println("Enviando a plataforma IoT...");
      Serial.println("------------\n");
      digitalWrite(LED_ROJO, LOW);
    }else{
      Serial.println("--- Envío de datos IoT");
      Serial.println("Alerta de temperatura alta");
      Serial.print("Temperatura: ");
      Serial.print(temperatura);
      Serial.println("C");
      digitalWrite(LED_ROJO, HIGH);
    }
  }
  //Enviar cada 5 segundos
  delay(5000);
}