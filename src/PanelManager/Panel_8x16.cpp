/**
 * @file Panel_8x16.cpp
 * @brief 8x16サイズのLEDパネルクラス
 * @author Yoshito Nakaue
 * @date 2021/07/19
 */

#include "Panel_8x16.hpp"

Panel_8x16::Panel_8x16()
    : PanelBase(8, 16)
{
    registerMatrixInfo();
}

void Panel_8x16::registerMatrixInfo()
{
    for (int i = 0; i < 128; i++)
    {
        PixelInfo pixel_info = PixelInfo(EChipType::LED, 1);
        pixels_info_.push_back(pixel_info);
    }
}
