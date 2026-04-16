#define BLYNK_TEMPLATE_ID "TMPL3xXaLaFM_"
#define BLYNK_TEMPLATE_NAME "Smart Irrigation System with ESP32"
#define BLYNK_AUTH_TOKEN "alYR0KiQkRSxslzZPkIFNGhdg-vhTHbS"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#define sensorPin 34
#define relayPin 26
#define PUMP_SWITCH V6

int threshold = 2500;

char ssid[] = "Cathiiee's M14";
char pass[] = "dietmountaindew";

BlynkTimer timer;

bool manualPump = false;

void checkSoilMoisture() {

  int moistureValue = analogRead(sensorPin);
  

  Serial.print("Moisture Value: ");
  Serial.println(moistureValue);

int moisturePercent = map(moistureValue, 3500, 1500, 0, 100);
moisturePercent = constrain(moisturePercent, 0, 100);
Blynk.virtualWrite(V5, moisturePercent);

  if (!manualPump) {
    if (moistureValue > threshold) {
      digitalWrite(relayPin, LOW);   // pump ON
    } else {
      digitalWrite(relayPin, HIGH);  // pump OFF
    }
  }
}

BLYNK_WRITE(PUMP_SWITCH) {

  manualPump = param.asInt();

  if (manualPump == 1) {
    digitalWrite(relayPin, LOW);
    Serial.println("Pump ON (Manual)");
  } 
  else {
    digitalWrite(relayPin, HIGH);
    Serial.println("Pump OFF (Manual)");
  }
}

void setup() {

  Serial.begin(115200);

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(2000L, checkSoilMoisture);
}

void loop() {

  Blynk.run();
  timer.run();
}