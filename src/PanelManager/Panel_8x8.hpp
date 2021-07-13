/**
 * @file Panel_8x8.hpp
 * @brief 8x8サイズのLEDパネルクラス
 * @author Yoshito Nakaue
 * @date 2021/07/11
 */

#ifndef PANEL_8X8_HPP
#define PANEL_8X8_HPP

#include "PanelBase.hpp"

/**
 * @brief  8x8サイズのLEDパネルクラス
 */
class Panel_8x8 : public PanelBase
{
public:
    /**
     * @brief  8x8すべてがLEDのパネルとして初期化
     */
    Panel_8x8();

private:
    /**
     * @brief  8x8すべてがLEDとしてチップ情報を登録
     */
    void registerMatrixInfo() override;
};

#endif
