/**
 * @file HT16K33_8x16.cpp
 * @brief 8x16サイズのLEDパネルクラス
 * @author Yoshito Nakaue
 * @date 2021/11/09
 */

#include "HT16K33_8x16.hpp"

HT16K33_8x16::HT16K33_8x16()
    : HT16K33_Base(8, 16, 1)
{
    registerMatrixInfo();
}

void HT16K33_8x16::registerMatrixInfo()
{
    for (int i = 0; i < 128; i++)
    {
        PixelInfo pixel_info = PixelInfo(EChipType::LED, 0);
        pixels_info_.push_back(pixel_info);
    }
}
