/**
 * @file PixelInfo.cpp
 * @brief 各ピクセルの情報を格納する構造体の実装
 * @author Yoshito Nakaue
 * @date 2021/07/09
 */

#include "PixelInfo.hpp"

PixelInfo::PixelInfo(EChipType type, int color)
{
    type_   = type;
    color_  = color;
}
