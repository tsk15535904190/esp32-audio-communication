#ifndef AUDIOI2S
#define AUDIOI2S

#include <stdint.h>
#include <Arduino.h>
#include <driver/i2s.h>

#define BTN 0
#define LED 2
#define SAMPLE_RATE 16000

#define CHECK(err)   if (err != ESP_OK) {Serial.printf("Failed installing driver: %d\n", err);while (true);}

const i2s_port_t REC_I2S_PORT = I2S_NUM_0;
const i2s_port_t SPK_I2S_PORT = I2S_NUM_1;

extern int32_t *samples_32bit;//读出来的原始32位数据，长度128
extern int16_t *samples_16bit;//转换后的16位数据，长度128
extern uint8_t *samples_8bit ;//转换后的8位数据，长度128
extern int16_t *recive_16bit;//接收后转换的16位数据，长度128
extern int16_t *output_16bit;//发送给扬声器的16位数据，长度256



void I2SInit();
int I2Sread(int16_t *samples, int count);
void covert_bit(int16_t *temp_samples_16bit,uint8_t*temp_samples_8bit,uint8_t len );
void I2Swrite(int16_t *samples, int count);

#endif
