#include  <Arduino.h>
#include  "microphone.h"
#include <driver/i2s.h>
#include "debug.h"

#define I2S_PORT I2S_NUM_0 // Use I2S port 0


void setupMicrophone() {
    i2s_config_t i2s_config = {
      .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX), // Set I2S to master mode and receive mode
      .sample_rate = 16000,                                // Set sample rate to 16 kHz - this is a common sample rate for voice applications
      .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,        // Set bits per sample to 32 bits - SPH0645 microphone outputs 32-bit data
      .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,         // Set channel format to only left channel - this is a common format for I2S microphones, SEL is currently grounded
      .communication_format = I2S_COMM_FORMAT_STAND_I2S,   // Set communication format to standard I2S
      .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,            // Set interrupt allocation flags to level 1
      .dma_buf_count = 4,                                  // Set DMA buffer count to 4
      .dma_buf_len = 1024,                                 // Set DMA buffer length to 1024
      .use_apll = false,                                   // Do not use APLL as it is not necessary for this application              
      .tx_desc_auto_clear = false,                         // Do not auto clear TX descriptor as we are not transmitting data
      .fixed_mclk = 0                                      // Do not use a fixed MCLK as it is not necessary for this application
    };

    i2s_pin_config_t pin_config = {
      .mck_io_num = I2S_PIN_NO_CHANGE, // We are not using the MCK pin as it is not necessary for this application, causes a crash otherwise
      .bck_io_num = I2S_BCLK, // Bit Clock pin
      .ws_io_num = I2S_LRCL, // Word Select pin
      .data_out_num = I2S_PIN_NO_CHANGE, // We are not using the data out pin as we are only receiving data
      .data_in_num = I2S_DOUT, // Data In pin
       
  };    

    // Install and start the I2S driver with the specified configuration
    DBG("Microphone initialized.\n");
    esp_err_t err = i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
    DBG("install: %s\n", esp_err_to_name(err));
    err = i2s_set_pin(I2S_PORT, &pin_config);
    DBG("set_pin: %s\n", esp_err_to_name(err));


}

void debugMicrophone() {
    int32_t buf[2] = {0, 0};
    size_t n = 0;
    esp_err_t e = i2s_read(I2S_PORT, buf, sizeof(buf), &n, 1000);
    Serial.printf("err=%s bytes=%u  L=0x%08lX  R=0x%08lX\n",
                  esp_err_to_name(e), (unsigned)n,
                  (unsigned long)buf[0], (unsigned long)buf[1]);
}

//Funciton reads raw data from the I2S microphone and returns it as a 32-bit integer. 
//The function uses the i2s_read function to read data from the I2S port, and it waits indefinitely for data to be available. 
//The function assumes that the I2S microphone is configured to output 32-bit data.
int32_t readMicrophoneData() {

    int32_t sample = 0; //The raw sample data
    size_t bytes_read = 0; //The number of bytes read from the I2S port

    // Read 4 bytes (32 bits) from the I2S microphone
    [[maybe_unused]] esp_err_t e = i2s_read(I2S_PORT, &sample, sizeof(sample), &bytes_read, portMAX_DELAY);

    DBG("err = %s; Read %u bytes from I2S microphone: 0x%08lX\n", esp_err_to_name(e), (unsigned)bytes_read, (unsigned long)sample);
    if (e != ESP_OK || bytes_read != sizeof(sample)) {
        DBG("i2s_read failed: %s\n", esp_err_to_name(e));
        return 0;
    }
    //the I2S microphone outputs 32-bit data, but the actual audio data is only 18 bits. The remaining bits are padding.
    //To get the actual audio data, we need to shift the sample to the right by 14 bits.
    sample >>= 14;

    // Return the sample read from the microphone
    return sample;
}