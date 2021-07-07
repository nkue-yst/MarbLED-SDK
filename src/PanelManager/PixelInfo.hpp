/**
 * @file PixelInfo.hpp
 * @brief 1ピクセルの情報を格納する構造体
 * @author Yoshito Nakaue
 * @date 2021/07/07
 */

#ifndef PIXEL_INFO_HPP
#define PIXEL_INFO_HPP

#include <vector>

enum class EChipType : uint8_t
{
    NONE,
    LED,
    IR_LED,
    IR_RCV,
}

struct PixelInfo
{
public:
    PixelInfo(EChipType type, int color);

    EChipType type_;
    int color_;
};

#endif
