#include <Arduino.h>
#define BUTTON_PIN 4
#define LED_PIN 2
#define DEBUG_BUTTON 18
#define DEBUG_UART 19
#define DEBUG_TIMER 21

/**
 * @mainpage Project Documentation
 *
 * @section intro Introduction
 * This project demonstrates interrupt handling using:
 * - Button interrupt
 * - UART interrupt
 * - Timer interrupt
 *
 * @section sim Simulation
 * Wokwi simulations and waveform results are available in:
 * - wokwi/tests/wokwi-logic.vcd
 *
 * These results verify correct system behavior.
 */

/// Flag set when button interrupt occurs
volatile bool buttonFlag = false;

/// Flag set when timer interrupt occurs
volatile bool timerFlag = false;

/// Flag set when UART data is received
volatile bool uartFlag = false;

portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

/// Stores the type of interrupt that occurred
String interrupt = "";

/// Hardware timer pointer
hw_timer_t *timer = NULL;

/// Current LED state
bool ledState = false;

/// Stores received UART string
String uartString = "";

/**
 * @brief Interrupt service routine for button press
 */
void IRAM_ATTR buttonISR(){
  buttonFlag = true;
}

/**
 * @brief Timer interrupt handler
 */
void IRAM_ATTR onTimer(){
  timerFlag = true;
}

/**
 * @brief Toggles the LED twice (on/off quickly)
 */
void toggleLED(){
  ledState = !ledState;
  digitalWrite(LED_PIN, ledState);
  ledState = !ledState;
  digitalWrite(LED_PIN, ledState);
}

/**
 * @brief Initializes serial communication, pins and interrupts
 */
void setup(){
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, FALLING );

  pinMode(DEBUG_BUTTON, OUTPUT);
  pinMode(DEBUG_UART, OUTPUT);
  pinMode(DEBUG_TIMER, OUTPUT);

  timer = timerBegin(1000000);
  timerAttachInterrupt(timer, &onTimer);
  timerAlarm(timer, 1000000, true, 0);

}

/**
 * @brief Main loop that processes interrupts and UART input
 */
void loop(){
  
  // Check for UART input
  if(Serial.available()){
    uartString = Serial.readStringUntil('\n');
    uartFlag = true;
  }

// Handle button interrupt - highest priority interrupt
  if(buttonFlag){
   digitalWrite(DEBUG_BUTTON, HIGH);

    buttonFlag = false;

    portENTER_CRITICAL(&mux);
    interrupt = "Button interrupt";
    portEXIT_CRITICAL(&mux);

    Serial.println(interrupt);
    toggleLED();
    digitalWrite(DEBUG_BUTTON, LOW);
  }
  // Handle button interrupt - second highest priority interrupt
  else if(uartFlag){
    digitalWrite(DEBUG_UART, HIGH);
    uartFlag = false;

    portENTER_CRITICAL(&mux);
    interrupt = "UART interrupt";
    portEXIT_CRITICAL(&mux);

    Serial.println(interrupt);
    Serial.println(uartString);
    toggleLED();
    digitalWrite(DEBUG_UART, LOW);
  }
  // Handle button interrupt - lowest priority interrupt
  else if(timerFlag){
    digitalWrite(DEBUG_TIMER, HIGH);
    timerFlag = false;

    portENTER_CRITICAL(&mux);
    interrupt = "Timer interrupt";
    portEXIT_CRITICAL(&mux);

    Serial.println(interrupt);
    toggleLED();
    digitalWrite(DEBUG_TIMER, LOW);
  }
}
