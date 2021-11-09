/**
 * @file HT16K33_8x16.hpp
 * @brief 8x1サイズのLEDパネルクラス
 * @author Yoshito Nakaue
 * @date 2021/11/09
 */

#ifndef HT16K33_8X16_HPP
#define HT16K33_8X16_HPP

#include "HT16K33_Base.hpp"

/**
 * @brief  8x16サイズのLEDパネルクラス
 */
class HT16K33_8x16 : public HT16K33_Base
{
public:
    /**
     * @brief  8x16すべてがLEDのパネルとして初期化
     */
    HT16K33_8x16();

private:
    /**
     * @brief  8x16すべてがLEDとしてチップ情報を登録
     */
    void registerMatrixInfo() override;
};

#endif
