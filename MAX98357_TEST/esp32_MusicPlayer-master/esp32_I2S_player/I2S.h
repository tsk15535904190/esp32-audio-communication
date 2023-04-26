#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2s.h"
#include "esp_system.h"
#define SAMPLE_RATE (20000)
#define PIN_I2S_BCLK 26
#define PIN_I2S_LRC 22
#define PIN_I2S_DOUT 25

// 44100Hz, 16bit, stereo
void I2S_Init();
void I2S_Write(char* data, int numData);
