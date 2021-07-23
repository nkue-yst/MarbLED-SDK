/**
 * @file PanelBase.cpp
 * @brief LEDパネルの基底クラスの実装
 * @author Yoshito Nakaue
 * @date 2021/07/14
 */

#include "PanelBase.hpp"
#include <Arduino.h>
#include <Wire.h>

PanelBase::PanelBase(uint16_t width, uint16_t height)
{   
    width_ = width;
    height_ = height;
}

void PanelBase::init(uint8_t addr)
{
    addr_ = addr;
  
    Wire.begin();

    /* I2C に使うピンの設定 */
    Wire.beginTransmission(addr_);
    Wire.write(0x21);
    Wire.endTransmission();

    /* blink rate の設定 */
    Wire.beginTransmission(addr_);
    Wire.write(0x80 | 0x01 | (0 << 1));
    Wire.endTransmission();

    /* 明るさの設定 */
    Wire.beginTransmission(addr_);
    Wire.write(0xE0 | 5);
    Wire.endTransmission();

    /* 8x16のLEDを初期化 */
    Wire.beginTransmission(addr_);
    Wire.write(0b00000000);
    for (int i = 0; i < 8; i++)
    {
        Wire.write(0b00000000);
        Wire.write(0b00000000);
    }
    Wire.endTransmission();
}

void PanelBase::update()
{
    char x;
    char y;
    char c;
  
    // シリアル通信（受信待ち）
    if (Serial.available() >= 3)
    {
        x = Serial.read();
        y = Serial.read();
        c = Serial.read();
        Serial.println(x);
        Serial.println(y);
        Serial.println(c);

        pixels_info_[y * width_ + x].color_ = c;
    }

    /* 処理時間計測開始 */
    //unsigned long start = micros();
    
    for (int i = 0; i < height_ * width_; i++)
    {
        PixelInfo target_pixel = pixels_info_[i];
        
        if (target_pixel.type_ == EChipType::LED && target_pixel.color_ == 1)
            ((i < 64) ? disp_buff1[i / width_] : disp_buff2[(i - 64) / width_]) |= 1 << (i % width_);
        else
            ((i < 64) ? disp_buff1[i / width_] : disp_buff2[(i - 64) / width_]) &= ~(1 << (i % width_));
    }
        
    Wire.beginTransmission(addr_);
    Wire.write(0b00000000);
    
    for (int i = 0; i < 8; i++)
    {
        Wire.write(disp_buff1[i]);
        Wire.write(disp_buff2[i]);
    }
    Wire.endTransmission();

    /* 処理時間出力 */
    //Serial.print(micros() - start);
    //Serial.println(" μs");
}
