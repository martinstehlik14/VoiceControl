#include <Arduino.h>
#include <WiFi.h>
#include "microphone.h"
#include "info.h"

// put function declarations here:
int myFunction(int, int);



void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);
  delay(5000);
  printInfo();
  Serial.println("Hello, ESP32!");
  Serial.printf("BCLK=%d LRCL=%d DOUT=%d\n", I2S_BCLK, I2S_LRCL, I2S_DOUT);
  setupMicrophone();
}

void loop() {
    readMicrophoneData();
    delay(200);
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}


