/**
 * @file Panel_24x16.cpp
 * @brief 24x16サイズのLEDパネルクラス
 * @author Yoshito Nakaue
 * @date 2021/09/21
 */

#include "Panel_24x16.hpp"

Panel_24x16::Panel_24x16()
    : PanelBase(24, 16, 3)
{
    registerMatrixInfo();
}

void Panel_24x16::registerMatrixInfo()
{
    for (int i = 0; i < 24 * 16; i++)
    {
        PixelInfo pixel_info = PixelInfo(EChipType::LED, 0);
        pixels_info_.push_back(pixel_info);
    }
}
