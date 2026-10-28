#include <Arduino.h>
#include "info.h"


void printInfo() {
  Serial.println("\n=== KOMPLETNI DIAGNOSTIKA ESP32 ===");
  
  // 1. Hardware and procesor
  Serial.printf("Model cipu: %s\n", ESP.getChipModel());
  Serial.printf("Pocet jader procesoru: %d\n", ESP.getChipCores());
  Serial.printf("Rychlost procesoru: %d MHz\n", ESP.getCpuFreqMHz());
  Serial.printf("Teplota cipu: %.1f C\n", temperatureRead());
  
  // 2. MAC adress (Wi-Fi)
  Serial.printf("MAC adresa (Wi-Fi): %s\n", WiFi.macAddress().c_str());

  // 3. Info about the loaded program (sketch)
  // Sketch is the program that is currently running on the ESP32. It is stored in the flash memory of the chip.
  Serial.printf("Velikost nahraneho programu: %d KB\n", ESP.getSketchSize() / 1024);
  Serial.printf("Zbyva mista pro program: %d KB\n", ESP.getFreeSketchSpace() / 1024);

  // 4. Current memory usage (RAM and PSRAM)
  // RAM is the memory that is used by the program while it is running. It is used to store variables, data, and other information that the program needs to run.
  // PSRAM is the external memory that can be used by the program to store data that is not needed immediately. It is slower than RAM, but it is larger and can be used to store data that is not needed immediately.
  Serial.printf("Volna rychla RAM (Heap): %d KB\n", ESP.getFreeHeap() / 1024);
  Serial.printf("Volna velka PSRAM: %d KB\n", ESP.getFreePsram() / 1024);

  // 5. Current SDK version (ESP-IDF)
  Serial.printf("Verze SDK (ESP-IDF): %s\n", ESP.getSdkVersion());
  
  Serial.println("===================================");
  

}