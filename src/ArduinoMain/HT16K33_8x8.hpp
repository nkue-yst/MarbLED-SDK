/**
 * @file HT16K33_8x8.hpp
 * @brief 8x8サイズのLEDパネルクラス
 * @author Yoshito Nakaue
 * @date 2021/11/09
 */

#ifndef HT16K33_8X8_HPP
#define HT16K33_8X8_HPP

#include "HT16K33_Base.hpp"

/**
 * @brief  8x8サイズのLEDパネルクラス
 */
class HT16K33_8x8 : public HT16K33_Base
{
public:
    /**
     * @brief  8x8すべてがLEDのパネルとして初期化
     */
    HT16K33_8x8();

private:
    /**
     * @brief  8x8すべてがLEDとしてチップ情報を登録
     */
    void registerMatrixInfo() override;
};

#endif
