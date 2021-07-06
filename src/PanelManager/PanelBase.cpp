/**
 * @file PanelBase.cpp
 * @brief LEDパネルの基底クラスの実装
 * @author Yoshito Nakaue
 * @date 2021/07/05
 */

#include "PanelBase.hpp"

PanelBase::PanelBase(uint16_t width, uint16_t height)
    : GFXcanvas1(width, height)
{   
    width_ = width;
    height_ = height;

    int matrix_num = width * height;
    for (int i = 0; i < matrix_num; i++)
        color_data_.push_back(0);

    color_data_[10] = 1;
}

void PanelBase::update()
{
    this->clear();
    
    for (int y = 0; y < height_; y++)
    {
        for (int x = 0; x < width_; x++)
        {
            if (color_data_[y * width_ + x] == 1)
            {
                Serial.print("x: ");
                Serial.println(x);
                Serial.print("y: ");
                Serial.println(y);

                this->drawPixel(calcX(x), calcY(y), 1);
            }
        }
    }
    
    this->writeDisplay();
}
