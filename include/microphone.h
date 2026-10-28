#pragma once
#include <Arduino.h>


#define I2S_BCLK 4 // Bit Clock
#define I2S_LRCL 5 // Word Select (Left/Right Clock)
#define I2S_DOUT 6 // Data Out

void setupMicrophone();
int32_t readMicrophoneData();
void debugMicrophone();
