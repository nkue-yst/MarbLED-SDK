/**
 * @file PixelInfo.hpp
 * @brief 各ピクセルの情報を格納する構造体を定義
 * @author Yoshito Nakaue
 * @date 2021/07/13
 */

#ifndef PIXEL_INFO_HPP
#define PIXEL_INFO_HPP

#include <vector>

/**
 * @brief  LED、赤外線センサ等の列挙型
 */
enum class EChipType : uint8_t
{
    NONE,
    LED,
    IR_LED,
    IR_RCV,
};

/**
 * @brief  各ピクセル情報を格納する構造体
 */
struct PixelInfo
{
public:
    PixelInfo(EChipType type, int color = 0);

    //! パネル上に実装されている種類
    EChipType type_;

    //! LEDが実装されている場合の色(点灯状態)
    int color_;
};

#endif
