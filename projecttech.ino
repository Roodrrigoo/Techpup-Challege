/*
   -- Techpuphugvest --

   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 3.1.13 or later version 
   download it at: http://remotexy.com/en/library/

   To connect using RemoteXY mobile app:
     - for ANDROID 4.15.01 or later
     - for iOS 1.12.1 or later

   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation.
*/

/////////////////////////////////////////////////
//             RemoteXY include library        //
/////////////////////////////////////////////////

// Enable debug logging to Serial at 115200 (optional for debugging)
// #define REMOTEXY__DEBUGLOG    

// Select connection mode and include RemoteXY library
#define REMOTEXY_MODE__SOFTSERIAL
#define REMOTEXY_MODE__HARDSERIAL
#define REMOTEXY_SERIAL Serial1
#define REMOTEXY_SERIAL_SPEED 9600

#include <RemoteXY.h>
#include <Servo.h>

/////////////////////////////////////////////////
//         RemoteXY GUI configuration          //
/////////////////////////////////////////////////

#pragma pack(push, 1)  
uint8_t RemoteXY_CONF[] = {
  255,1,0,8,0,102,0,19,0,0,0,0,8,1,106,200,2,1,0,4,
  0,1,39,123,24,24,0,2,31,0,129,7,7,91,12,64,17,84,101,99,
  104,112,117,112,72,117,103,118,101,115,116,0,68,7,27,98,89,17,8,36,
  131,32,167,40,14,2,17,2,31,80,97,103,101,0,6,1,0,71,9,59,
  86,86,56,0,2,24,135,0,0,0,0,0,0,200,66,0,0,160,65,0,
  0,32,65,0,0,0,64,24,0 
};
#pragma pack(pop)

// This structure defines all the variables and events of your control interface 
struct {
  // Input variables
  uint8_t button_01;           // =1 if button pressed, else =0

  // Output variables
  float onlineGraph_01_var1;   // Displays raw pulse signal
  float instrument_01;         // Displays BPM (0-100)

  // Other variable
  uint8_t connect_flag;        // =1 if wire connected, else =0
} RemoteXY;   

/////////////////////////////////////////////////
//          Pulse Sensor Setup                //
/////////////////////////////////////////////////

#define USE_ARDUINO_INTERRUPTS true
#define UMBRAL 50

#include <PulseSensorPlayground.h>

// Pin configuration
const int PULSE_SENSOR_PIN = A0;   // Pulse sensor connected to analog pin A0
const int LED_PIN = 5;             // LED connected to digital pin 5
const int THRESHOLD = 550;         // Threshold for detecting pulse
int servoPin = 4;                  // Servo motor pin

// PulseSensor object
PulseSensorPlayground pulseSensor;
Servo myServo;

// Button state
bool isButtonPressed = false;

// Graphing variables
const int GRAPH_SAMPLES = 10;
int graphData[GRAPH_SAMPLES];       // Buffer for graph data
int graphIndex = 0;                 // Current index in graph buffer
unsigned long lastGraphUpdate = 0;  // Time of last graph update

// Respiratory signal smoothing
const int RESP_WINDOW = 5;
int respValues[RESP_WINDOW];
int respIndex = 0;
int respSum = 0;

/////////////////////////////////////////////////
//                 SETUP                      //
/////////////////////////////////////////////////

void setup() {
  RemoteXY_Init();              // Initialize RemoteXY
  Serial.begin(9600);           // Begin serial monitor

  pinMode(LED_PIN, OUTPUT);     // Set LED pin as output
  digitalWrite(LED_PIN, LOW);   // Turn off LED initially

  // Setup pulse sensor
  pulseSensor.analogInput(PULSE_SENSOR_PIN);
  pulseSensor.setThreshold(THRESHOLD);

  // Initialize graph and respiratory data buffers
  for (int i = 0; i < GRAPH_SAMPLES; i++) graphData[i] = 0;
  for (int i = 0; i < RESP_WINDOW; i++) respValues[i] = 0;

  // Attach servo to its pin
  myServo.attach(servoPin);
}

/////////////////////////////////////////////////
//                  LOOP                      //
/////////////////////////////////////////////////

void loop() {
  RemoteXY_Handler();  // Process RemoteXY events

  // Handle button press from app to control LED and servo
  if (RemoteXY.button_01 == 1) {
    digitalWrite(LED_PIN, HIGH);  // Turn on LED
    isButtonPressed = true;

  } else {
    digitalWrite(LED_PIN, LOW);   // Turn off LED
    isButtonPressed = false;
  }

  // Servo control based on button press
  if (isButtonPressed) {
    myServo.write(180);    // Rotate servo to 180°
    delay(500);
    myServo.write(0);      // Rotate servo to 0°
    delay(500);
  } else {
    myServo.write(90);     // Set servo to neutral position when not pressed
  }

  // Read respiratory sensor value (could be a different sensor on A1)
  int valorSensor = analogRead(A1);

  // Smooth the respiratory signal using a moving average filter
  respSum = respSum - respValues[respIndex] + valorSensor;
  respValues[respIndex] = valorSensor;
  respIndex = (respIndex + 1) % RESP_WINDOW;

  int promedio = respSum / RESP_WINDOW;

  // Display smoothed value on the instrument widget
  RemoteXY.instrument_01 = map(valorSensor, 0, 120, 0, 90);
  Serial.println(valorSensor);  // For debugging: print value to Serial

  // Read pulse sensor value
  int rawSignal = analogRead(PULSE_SENSOR_PIN);

  // Update graph every 3 seconds
  if (millis() - lastGraphUpdate >= 3000) {
    lastGraphUpdate = millis();

    // Store current signal into buffer
    graphData[graphIndex] = rawSignal;
    graphIndex = (graphIndex + 1) % GRAPH_SAMPLES;

    // Send normalized value (0-100) to RemoteXY online graph
    RemoteXY.onlineGraph_01_var1 = map(rawSignal, 0, 1023, 0, 100);
  }

  
}
