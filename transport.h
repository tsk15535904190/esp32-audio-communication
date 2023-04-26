#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include "Audioi2s.h"

const uint8_t broadcastAddress[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0XFF};//广播地址

void InitESPNow(void);
void sendData(const uint8_t  *data,uint16_t len);
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
void OnDataRecv(const uint8_t *mac_addr,  const uint8_t *data, int data_len);
