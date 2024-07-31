const int NUM_SENSORS = 5;
const int SENSOR_PINS[NUM_SENSORS] = {A0, A1, A2, A3, A4};  // Pines analógicos para los sensores
const int LED_PIN = 13;  // Pin para el LED de encendido
const int BUZZER_PIN = 12;  // Pin para la bocina

// Umbrales para cada sensor (ajusta estos valores según tu setup)
const int THRESHOLDS[NUM_SENSORS] = {100, 200, 300, 400, 500};

void setup() {
  Serial.begin(9600);
  
  // Configurar pines de los sensores como entrada
  for (int i = 0; i < NUM_SENSORS; i++) {
    pinMode(SENSOR_PINS[i], INPUT);
  }
  
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Encender el LED para indicar que el sistema está activo
  digitalWrite(LED_PIN, HIGH);
}

void loop() {
  int waterLevel = 0;
  
  // Leer valores de todos los sensores
  for (int i = 0; i < NUM_SENSORS; i++) {
    int sensorValue = analogRead(SENSOR_PINS[i]);
    Serial.print("Sensor ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(sensorValue);
    
    // Si el valor del sensor supera su umbral, incrementar el nivel de agua
    if (sensorValue > THRESHOLDS[i]) {
      waterLevel++;
    }
  }
  
  // Mostrar el nivel de agua actual
  Serial.print("Nivel de agua: ");
  Serial.println(waterLevel);
  
  // Activar alarma si el nivel de agua es máximo
  if (waterLevel == NUM_SENSORS) {
    digitalWrite(LED_PIN, HIGH);  // Encender LED
    tone(BUZZER_PIN, 1000, 1000);  // Activar bocina (1kHz durante 1 segundo)
    Serial.println("¡ALERTA! Contenedor lleno");
  } else {
    digitalWrite(LED_PIN, LOW);  // Apagar LED si no está lleno
  }
  
  delay(1000);  // Esperar 1 segundo antes de la próxima lectura
}
