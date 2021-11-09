/**
 * @file HT16K33_8x8.cpp
 * @brief 8x8サイズのLEDパネルクラス
 * @author Yoshito Nakaue
 * @date 2021/11/09
 */

#include "HT16K33_8x8.hpp"

HT16K33_8x8::HT16K33_8x8()
    : HT16K33_Base(8, 8, 1)
{
    registerMatrixInfo();
}

void HT16K33_8x8::registerMatrixInfo()
{
    for (int i = 0; i < 64; i++)
    {
        PixelInfo pixel_info = PixelInfo(EChipType::LED, 1);
        pixels_info_.push_back(pixel_info);
    }
}
