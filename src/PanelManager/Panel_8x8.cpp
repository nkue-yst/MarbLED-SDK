/**
 * @file Panel_8x8.cpp
 * @brief 8x8サイズのLEDパネルクラス
 * @author Yoshito Nakaue
 * @date 2021/07/14
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

    /* テスト点灯用処理
    pixels_info_[0].color_ = pixels_info_[9].color_ = pixels_info_[18].color_
        = pixels_info_[27].color_ = pixels_info_[36].color_ = pixels_info_[45].color_
        = pixels_info_[54].color_ = pixels_info_[63].color_ = 1;
    */
}
