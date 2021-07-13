/**
 * @file PanelBase.cpp
 * @brief LEDパネルの基底クラスの実装
 * @author Yoshito Nakaue
 * @date 2021/07/14
 */

#include "PanelBase.hpp"
#include <Wire.h>
#include <utility>

PanelBase::PanelBase(uint16_t width, uint16_t height)
{   
    width_ = width;
    height_ = height;

    Wire.begin();
    Wire.setClock(400000L);

    /* 8x16のLEDを初期化 */
    Wire.beginTransmission(0x70);
    Wire.write(0x00);
    for (int i = 0; i < 8; i++)
    {
        Wire.write(0b00000000);
        Wire.write(0b00000000);
    }
    Wire.endTransmission();
}

void PanelBase::update()
{
    uint8_t colors[8] = {
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000
    };
    
    for (int i = 0; i < height_ * width_; i++)
    {
        if (pixels_info_[i].type_ == EChipType::LED)
        {
            if (pixels_info_[i].color_)
            {
                colors[i / width_] |= 1 << i % width_;
            }
            else
            {
                colors[i / width_] &= ~(1 << i % width_);
            }
        }
    }
    
    Wire.beginTransmission(0x70);
    Wire.write((uint8_t)0x00);
    
    for (int i = 0; i < 8; i++)
    {
        Wire.write(colors[i] & 0xFF);
        Wire.write(colors[i] >> 8);
    }
    Wire.endTransmission();
}
