/**
 * @file Panel_8x16.hpp
 * @brief 8x1サイズのLEDパネルクラス
 * @author Yoshito Nakaue
 * @date 2021/07/19
 */

#ifndef PANEL_8X16_HPP
#define PANEL_8X16_HPP

#include "PanelBase.hpp"

/**
 * @brief  8x16サイズのLEDパネルクラス
 */
class Panel_8x16 : public PanelBase
{
public:
    /**
     * @brief  8x16すべてがLEDのパネルとして初期化
     */
    Panel_8x16();

private:
    /**
     * @brief  8x16すべてがLEDとしてチップ情報を登録
     */
    void registerMatrixInfo() override;
};

#endif
