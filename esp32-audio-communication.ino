#include <esp_now.h>
#include "Audioi2s.h"
#include "transport.h"

bool sendOver=1;//发送完成标志位
bool recOver=0;//接受完成标志位
bool speakOut;//0代表对外讲话，1代表收听

void setup(void)
{
  Serial.begin(115200);
  Serial.println("start!");
  InitESPNow();//ESP-NOW初始化，用来传输音频
  esp_now_register_send_cb(OnDataSent);//绑定发射和接受回调函数
  esp_now_register_recv_cb(OnDataRecv);
  Serial.println("InitESPNow over!");
  I2SInit();//I2S初始化 
  Serial.println("I2SInit over!");
  
  Serial.println("init end!");
  pinMode(BTN, INPUT_PULLUP);//按键
  pinMode(LED, OUTPUT);//指示灯
  digitalWrite(LED,HIGH);
}
bool  BtnisPressed(void)//按键是否按下
{
  bool key=digitalRead(BTN);
  if(1==key)
  {
    return 0;
  }
  else
  {
    return 1 ;
  }
}
void loop(void)
{
  if(BtnisPressed())//按下按键发射数据
  {
    speakOut=0;
    digitalWrite(LED,HIGH);//发射时开灯
    int samples_read = I2Sread(samples_16bit,128);//读取数据
    covert_bit(samples_16bit,samples_8bit,samples_read);//发送时转换为8位
    sendData(samples_8bit,samples_read);//发射数据
  }
  else//接收数据，接受部分在回调函数中
  {
    delay(28);//经过一段延时再判断，接收数据并且播放也需要时间
    speakOut=1;
    if(recOver)
    {
      recOver=0;
      if(digitalRead(LED))//接受数据时闪烁LED
      {
          digitalWrite(LED,LOW);
      }
      else
      {
          digitalWrite(LED,HIGH);
      }
    }
    else
    {
      digitalWrite(LED,LOW);//没有接收到消息，也没有发射，关灯
      i2s_zero_dma_buffer(SPK_I2S_PORT);//清空DMA中缓存的数据，你可以尝试一下不清空（注释这行）是什么效果
    }
  }
}
