#include "transport.h"
extern bool sendOver;
extern bool recOver;
extern bool speakOut;

void InitESPNow(void) {//esp-now初始化
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  esp_wifi_set_promiscuous(true);
  esp_wifi_set_channel((wifi_second_chan_t)3, WIFI_SECOND_CHAN_NONE);
  esp_wifi_set_promiscuous(false);
  if (esp_now_init() == ESP_OK) {
    Serial.println("ESPNow Init Success");
  }
  else {
    Serial.println("ESPNow Init Failed");
    ESP.restart();
  }
  esp_now_peer_info_t peerInfo = {};
  memcpy(&peerInfo.peer_addr, broadcastAddress, 6);
  if (!esp_now_is_peer_exist(broadcastAddress))
  {
    esp_err_t result;
    result = esp_now_add_peer(&peerInfo);
    if (result != ESP_OK)
    {
      Serial.printf("Failed to add broadcast peer: %s\n", esp_err_to_name(result));
    }
  }
}

void sendData(const uint8_t  *data, uint16_t len) {
  while (0 == sendOver) {//必须得等待上次发送完毕
    delay(1);
  }
  sendOver = 0;
  esp_now_send(broadcastAddress, data, len);
}

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {//数据发送完成回调函数
  sendOver = 1;
  //  if(status == ESP_NOW_SEND_SUCCESS )
  //  {
  //    Serial.println("Delivery success");
  //  }
  //  else
  //  {
  //    Serial.println("Delivery success");
  //  }
}
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len) {//数据接受完成回调函数，将数据写入到扬声器I2S中

  if(0==speakOut)
  {
    return;  
  }
  recOver = 1;
  for (int i = 0; i < data_len; i++)//接收到信息后转换为16bit，补充左右声道，写入到I2S
  {
    recive_16bit[i] = (data[i] - 128) << 5;
    output_16bit[i * 2 ] = recive_16bit[i];
    output_16bit[i * 2 + 1] = recive_16bit[i];
  }
  I2Swrite(output_16bit,data_len);
}
