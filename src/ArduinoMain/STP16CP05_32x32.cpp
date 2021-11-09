/**
 * @file STP16CP05_32x32.cpp
 * @brief 32x32サイズのLEDパネルクラス
 * @author Yoshito Nakaue
 * @date 2021/11/09
 */

#include "STP16CP05_32x32.hpp"

STP16CP05_32x32::STP16CP05_32x32()
    : STP16CP05_Base(32, 32, 1)
{
    registerMatrixInfo();
}

void STP16CP05_32x32::registerMatrixInfo()
{
    for (int i = 0; i < 24 * 16; i++)
    {
        PixelInfo pixel_info = PixelInfo(EChipType::LED, 0);
        pixels_info_.push_back(pixel_info);
    }
}
