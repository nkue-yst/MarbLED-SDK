/**
 * @file Panel_24x16.hpp
 * @brief 24x16サイズのLEDパネルクラス
 * @author Yoshito Nakaue
 * @date 2021/09/21
 */

#ifndef PANEL_24X16_HPP
#define PANEL_24X16_HPP

#include "PanelBase.hpp"

/**
 * @brief  24x16サイズのLEDパネルクラス
 */
class Panel_24x16 : public PanelBase
{
public:
    /**
     * @brief  24x16すべてがLEDのパネルとして初期化
     */
    Panel_24x16();

private:
    /**
     * @brief  24x16すべてがLEDとしてチップ情報を登録
     */
    void registerMatrixInfo() override;
};

#endif
