# Alerta de temperatura alta

Este proyecto utiliza un ESP32 con un sensor DHT22 para monitorear la temperatura y la humedad. Cuando la temperatura supera los 32 °C, se activa un LED rojo para indicar una alerta.

## Descripción del proyecto

El sistema realiza lo siguiente:

- Lee datos de temperatura y humedad desde un sensor DHT22.
- Muestra la información por monitor serial.
- Activa un LED rojo cuando la temperatura supera el umbral configurado.
- Simula el envío de datos a una plataforma IoT mediante mensajes por serial.
- Intenta conectarse a una red WiFi para representar un entorno IoT real.

## Hardware utilizado

- ESP32 DevKit C V4
- Sensor DHT22
- LED rojo
- Resistencia de 220 Ω

## Conexiones

- DHT22: pin 15 del ESP32
- LED rojo: pin 13 del ESP32
- GND y 3.3V según la conexión del circuito

## Requisitos

- PlatformIO
- Visual Studio Code
- Biblioteca DHT para ESP32 incluida en la carpeta lib

## Estructura del proyecto

- src/main.cpp: lógica principal del programa
- platformio.ini: configuración del entorno PlatformIO
- diagram.json: diagrama de simulación para Wokwi
- lib/DHT_sensor_library_for_ESPx: biblioteca del sensor DHT

## Cómo ejecutar

1. Abre el proyecto en PlatformIO.
2. Compila y sube el firmware al ESP32.
3. Abre el monitor serial para ver los datos.
4. Si usas Wokwi, puedes ejecutar la simulación desde el archivo diagram.json.

## Configuración

El proyecto está preparado para funcionar en Wokwi con la red:

- SSID: Wokwi-GUEST
- Contraseña: vacía

Si deseas usarlo con una red real, modifica los valores de SSID y contraseña en el archivo src/main.cpp.

## Notas

El umbral de alerta está configurado en 32 °C. Puedes cambiarlo editando la constante TEMPERATURA_MAX en el código fuente.
