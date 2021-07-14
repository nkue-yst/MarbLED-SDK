/**
 * @file PanelBase.cpp
 * @brief LEDパネルの基底クラスの実装
 * @author Yoshito Nakaue
 * @date 2021/07/14
 */

#include "PanelBase.hpp"
#include <Wire.h>

PanelBase::PanelBase(uint16_t width, uint16_t height)
{   
    width_ = width;
    height_ = height;
}

void PanelBase::init()
{
    Wire.begin();

    /* I2C に使うピンの設定 */
    Wire.beginTransmission(0x70);
    Wire.write(0x21);
    Wire.endTransmission();

    /* blink rate の設定 */
    Wire.beginTransmission(0x70);
    Wire.write(0x80 | 0x01 | (0 << 1));
    Wire.endTransmission();

    /* 8x16のLEDを初期化 */
    Wire.beginTransmission(0x70);
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
    for (int i = 0; i < height_ * width_; i++)
    {
        if (pixels_info_[i].type_ == EChipType::LED)
        {
            if (pixels_info_[i].color_)
            {
                disp_buff1[pixels_info_[i].led_ID_ / width_] |= 1 << (pixels_info_[i].led_ID_ % width_);
            }
            else
            {
                disp_buff1[pixels_info_[i].led_ID_ / width_] &= ~(1 << (pixels_info_[i].led_ID_ % width_));
            }
        }
    }
        
    Wire.beginTransmission(0x70);
    Wire.write(0b00000000);
    
    for (int i = 0; i < 8; i++)
    {
        Wire.write(disp_buff1[i]);
        Wire.write(disp_buff2[i]);
    }
    Wire.endTransmission();
}
