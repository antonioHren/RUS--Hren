#include <Arduino.h>
#define BUTTON_PIN 4
#define LED_PIN 2

volatile bool buttonFlag = false;
volatile bool timerFlag = false;
volatile bool uartFlag = false;

portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

String interrupt = "";

hw_timer_t *timer = NULL;

bool ledState = false;

String uartString = "";

void IRAM_ATTR buttonISR(){
  buttonFlag = true;
}

void IRAM_ATTR onTimer(){
  timerFlag = true;
}

void toggleLED(){
  ledState = !ledState;
  digitalWrite(LED_PIN, ledState);
  ledState = !ledState;
  digitalWrite(LED_PIN, ledState);
}

void setup(){
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, FALLING );

  timer = timerBegin(1000000);
  timerAttachInterrupt(timer, &onTimer);
  timerAlarm(timer, 1000000, true, 0);

}

void loop(){
  
  if(Serial.available()){
    uartString = Serial.readStringUntil('\n');
    uartFlag = true;
  }

  if(buttonFlag){
    buttonFlag = false;

    portENTER_CRITICAL(&mux);
    interrupt = "Button interrupt";
    portEXIT_CRITICAL(&mux);

    Serial.println(interrupt);
    toggleLED();
  }
  else if(uartFlag){
    uartFlag = false;

    portENTER_CRITICAL(&mux);
    interrupt = "UART interrupt";
    portEXIT_CRITICAL(&mux);

    Serial.println(interrupt);
    Serial.println(uartString);
    toggleLED();
  }
  else if(timerFlag){
    timerFlag = false;

    portENTER_CRITICAL(&mux);
    interrupt = "Timer interrupt";
    portEXIT_CRITICAL(&mux);

    Serial.println(interrupt);
    toggleLED();
  }
}
