/**
 * @file Panel_8x8.hpp
 * @brief 8x8サイズのLEDパネルクラス
 * @author Yoshito Nakaue
 * @date 2021/07/11
 */

#include "Panel_8x8.hpp"

Panel_8x8::Panel_8x8()
    : PanelBase(8, 8)
{
    registerMatrixInfo();
}

void Panel_8x8::registerMatrixInfo()
{
    for (int i = 0; i < 64; i++)
    {
        PixelInfo pixel_info = PixelInfo(EChipType::LED, 0);
        pixels_info_.push_back(pixel_info);
    }
}
