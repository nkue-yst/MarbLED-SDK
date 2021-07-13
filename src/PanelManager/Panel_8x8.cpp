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
    /*for (int i = 0; i < 64; i++)
    {
        PixelInfo pixel_info = PixelInfo(EChipType::LED, 0, i);
        pixels_info_.push_back(pixel_info);
    }*/

    int led_id = 0;
    for (int i = 0; i < 64; i++)
    {
        if (i == 9 || i == 18 || i == 35 || i == 60)
        {
            PixelInfo pixel_info = PixelInfo(EChipType::LED, 1, led_id);
            led_id++;
            pixels_info_.push_back(pixel_info);
        }
        else if (i == 0 || i == 6 || i == 27 || i == 48 || i == 54)
        {
            PixelInfo pixel_info = PixelInfo(EChipType::IR_LED);
            pixels_info_.push_back(pixel_info);            
        }
        else if (i == 3 || i == 24 || i == 30 || i == 51)
        {
            PixelInfo pixel_info = PixelInfo(EChipType::IR_RCV);
            pixels_info_.push_back(pixel_info);            
        }
        else
        {
            PixelInfo pixel_info = PixelInfo(EChipType::LED, 0, led_id);
            led_id++;
            pixels_info_.push_back(pixel_info);
        }
    }

    /* テスト点灯用処理 - 01
    pixels_info_[3].color_  = 1;
    pixels_info_[12].color_ = 1;
    */

    /* テスト点灯用処理 - 02
    pixels_info_[0].color_ = pixels_info_[9].color_ = pixels_info_[18].color_
        = pixels_info_[27].color_ = pixels_info_[36].color_ = pixels_info_[45].color_
        = pixels_info_[54].color_ = pixels_info_[63].color_ = 1;
    */
}
