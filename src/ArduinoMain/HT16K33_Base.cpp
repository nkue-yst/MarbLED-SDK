/**
 * @file HT16K33_Base.cpp
 * @brief Base class of HT16K33
 * @author Yoshito Nakaue
 * @date 2021/11/09
 */

#include "PanelBase.hpp"
#include "HT16K33_Base.hpp"

#include <Arduino.h>
#include <Wire.h>

HT16K33_Base::HT16K33_Base(uint16_t width, uint16_t height, uint16_t num_driver)
    : PanelBase(width, height, num_driver)
{
}

void HT16K33_Base::init(uint16_t addr)
{
    addr_ = addr;
  
    Wire.begin();

    /* Setting of pin for I2C communication */
    for (int i = 0; i < num_driver_; i++)
    {
        Wire.beginTransmission(addr_ + i);
        Wire.write(0x21);
        Wire.endTransmission();
    }

    /* Setting of blink rate */
    for (int i = 0; i < num_driver_; i++)
    {
        Wire.beginTransmission(addr_ + i);
        Wire.write(0x80 | 0x01 | (0 << 1));
        Wire.endTransmission();
    }

    /* Setting of brightness */
    for (int i = 0; i < num_driver_; i++)
    {
        Wire.beginTransmission(addr_ + i);
        Wire.write(0xE0 | 5);
        Wire.endTransmission();
    }

    /* Initialize LED with 'OFF'  */
    for (int i = 0; i < num_driver_; i++)
    {
        Wire.beginTransmission(addr_ + i);
        Wire.write(0b00000000);
        for (int i = 0; i < 8; i++)
        {
            Wire.write(0b00000000);
            Wire.write(0b00000000);
        }
        Wire.endTransmission();
    }
}

void HT16K33_Base::update()
{
    int rcv_num = 0;
    while (rcv_num != width_ * height_)
    {
        if (Serial.available())
        {
            char c = Serial.read();
    
            pixels_info_[rcv_num].color_ = c;
            rcv_num++;
        }
    }
                                                                                                                                                                                                                                                                                                                                                  
    for (int Y = 0; Y < static_cast<int>((height_ - 1) / 16) + 1; Y++)
    {
        for (int X = 0; X < static_cast<int>((width_ - 1) / 8) + 1; X++)
        {
            for (int y = 0; y < 16; y++)
            {
                for (int x = 0; x < 8; x++)
                {
                    PixelInfo target_pixel = pixels_info_[(X * 8) + (Y * 8 * 16) + (y * width_) + x];

                    if (y < 8)
                    {
                        if (target_pixel.type_ == EChipType::LED && target_pixel.color_ != 0)
                        {
                            disp_buff1[y] |= (1 << x);
                        }
                        else
                        {
                            disp_buff1[y] &= ~(1 << x);
                        }
                    }
                    else
                    {
                        if (target_pixel.type_ == EChipType::LED && target_pixel.color_ != 0)
                        {
                            disp_buff2[y - 8] |= (1 << x);                            
                        }
                        else
                        {
                            disp_buff2[y - 8] &= ~(1 << x);
                        }
                    }
                }
            }
               
            // Serial.println(addr_ + (Y * static_cast<int>((width_ - 1) / 8 + 1)) + X);

            Wire.beginTransmission(addr_ + (Y * static_cast<int>((width_ - 1) / 8 + 1)) + X);
            Wire.write(0b00000000);
    
            for (int i = 0; i < 8; i++)
            {
                Wire.write(disp_buff1[i]);
                Wire.write(disp_buff2[i]);
            }
            Wire.endTransmission();
        }
    }
}
