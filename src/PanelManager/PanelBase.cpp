/**
 * @file PanelBase.cpp
 * @brief LEDパネルの基底クラスの実装
 * @author Yoshito Nakaue
 * @date 2021/07/05
 */

#include "PanelBase.hpp"
#include "PixelInfo.hpp"

PanelBase::PanelBase(uint16_t width, uint16_t height)
    : Adafruit_GFX(width, height)
{   
    width_ = width;
    height_ = height;

    int matrix_num = width * height;
    for (int i = 0; i < matrix_num; i++)
    {
        PixelInfo pixel_info = PixelInfo(EChipType::LED, 0);
        pixels_info_.push_back(pixel_info);
    }
}

void registerMatrixInfo()
{
    
}

void PanelBase::update()
{
    this->clear();
    
    for (int y = 0; y < height_; y++)
    {
        for (int x = 0; x < width_; x++)
        {
            if (pixels_info_[y * width_ + x].color_ == 1)
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

void PanelBase::drawPixel(int16_t x, int16_t y, uint16_t color)
{
    if ((y < 0) || (y >= height_))
        return;
    if ((x < 0) || (x >= width_))
        return;

    switch (getRotation())
    {
    case 1:
        _swap_int16_t(x, y);
        x = width_ - x - 1;
        break;
    case 2:
        x = width_ - x - 1;
        y = height_ - y - 1;
        break;
    case 3:
        _swap_int16_t(x, y);
        y = height_ - y - 1;
        break;
    default:
        break;
    }

    x += (width_ - 1);
    x %= width_;

    if (color)
    {
        displaybuffer[y] |= 1 << x;
    }
    else
    {
        displaybuffer[y] &= ~(1 << x);
    }
}
