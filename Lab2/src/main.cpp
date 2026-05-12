#include <Arduino.h>
#include "esp_sleep.h"


#define uS_TO_S_FACTOR 1000000ULL
#define TIME_TO_SLEEP 5


RTC_DATA_ATTR int bootCount = 0;
RTC_DATA_ATTR int measurementIndex = 0;

RTC_DATA_ATTR float temperatures[10];
RTC_DATA_ATTR float humidities[10];

float generateTemperature() {
  return random(180, 320) / 10.0;
}

float generateHumidity() {
  return random(400, 800) / 10.0;
}

void printMeasurements() {

  Serial.println();
  Serial.println("LAST 10 MEASUREMENTS");

  for (int i = 0; i < 10; i++) {

    Serial.print("Measurement ");
    Serial.print(i + 1);

    Serial.println();
    Serial.print("Temp: ");
    Serial.print(temperatures[i]);

    Serial.print(" C | Humidity: ");
    Serial.print(humidities[i]);
    Serial.println(" %");
  }

}

void setup() {

  Serial.begin(115200);

  delay(3000);
  

  bootCount++;

  Serial.println();
  Serial.println("ESP32 WAKEUP");

  delay(5000);

  Serial.print("Wake up number: ");
  Serial.println(bootCount);

  float temp = generateTemperature();
  float hum = generateHumidity();

  temperatures[measurementIndex] = temp;
  humidities[measurementIndex] = hum;

  Serial.print("Stored measurement: ");
  Serial.println(measurementIndex + 1);

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.println(" %");

  measurementIndex++;

  if (measurementIndex >= 10) {
    Serial.println();
    Serial.println("10 measurements collected!");
    printMeasurements();
    measurementIndex = 0;
  }

  Serial.println("Going to deep sleep");

  delay(5000);

  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);

  Serial.flush();

  esp_deep_sleep_start();
}

void loop() {

}
