/**
 * @file HT16K33_24x16.cpp
 * @brief 24x16サイズのLEDパネルクラス
 * @author Yoshito Nakaue
 * @date 2021/11/09
 */

#include "HT16K33_24x16.hpp"
#include <Arduino.h>

HT16K33_24x16::HT16K33_24x16()
    : HT16K33_Base(24, 16, 3)
{
    registerMatrixInfo();
}

void HT16K33_24x16::registerMatrixInfo()
{
    for (int i = 0; i < 24 * 16; i++)
    {
        PixelInfo pixel_info = PixelInfo(EChipType::LED, 0);
        pixels_info_.push_back(pixel_info);
    }
}
