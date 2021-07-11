/**
 * @file PanelBase.cpp
 * @brief LEDパネルの基底クラスの実装
 * @author Yoshito Nakaue
 * @date 2021/07/05
 */

#include "PanelBase.hpp"
#include <utility>

PanelBase::PanelBase(uint16_t width, uint16_t height)
    : Adafruit_GFX(width, height)
{   
    width_ = width;
    height_ = height;
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

    // 指定座標のチップがLEDでなければ何もしない
    if (pixels_info_[y * width_ + x].type_ != EChipType::LED)
        return;

    /* 独自パネル構成より座標を再変換する必要アリ */
    /* ここから */
    std::swap(x, y);
    y = height_ - y - 1;

    x += (width_ - 1);
    x %= width_;
    /* ここまで */

    if (color)
    {
        displaybuffer[y] |= 1 << x;
    }
    else
    {
        displaybuffer[y] &= ~(1 << x);
    }
}
