/**
 * @file PixelInfo.hpp
 * @brief 各ピクセルの情報を格納する構造体を定義
 * @author Yoshito Nakaue
 * @date 2021/07/07
 */

#ifndef PIXEL_INFO_HPP
#define PIXEL_INFO_HPP

#include <vector>

/**
 * @enum EChipType
 * @brief LED、赤外線センサ等の列挙型
 */
enum class EChipType : uint8_t
{
    NONE,
    LED,
    IR_LED,
    IR_RCV,
};

/**
 * @struct PixelInfo
 * @brief 各ピクセル情報を格納する構造体
 */
struct PixelInfo
{
public:
    PixelInfo(EChipType type, int color);

    EChipType type_;
    int color_;
};

#endif
