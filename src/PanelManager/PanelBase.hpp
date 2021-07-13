/**
 * @file PanelBase.hpp
 * @brief LEDパネルの基底クラス
 * @author Yoshito Nakaue
 * @date 2021/07/14
 */

#ifndef PANEL_BASE_HPP
#define PANEL_BASE_HPP

#include "PixelInfo.hpp"
#include <vector>

/**
 * @brief  1枚のLEDパネルを表すクラス
 */
class PanelBase
{
public:
    /**
     * @brief  矩形マトリクスLED用コンストラクタ
     */
    PanelBase(uint16_t width = 8, uint16_t height = 8);

    /**
     * @brief  LED全体の点灯状態を更新する
     */
    void update();

protected:
    /**
     * @brief  マトリクスの各ピクセルの情報を登録する
     */
    virtual void registerMatrixInfo() = 0;

    //! 各ピクセルの情報を格納する配列
    std::vector<PixelInfo> pixels_info_;

private:
    /**
     * @brief  指定したいx座標をLEDパネル上のx座標に変換する
     * @param  x  修正前のx座標
     */
    int calcX(int x) { return x; }

    /**
     * @brief  指定したいy座標をLEDパネル上のy座標に変換する
     * @param  y  修正前のy座標
     */
    int calcY(int y) { return (y + 1) % height_; }

    //! パネル全体の横幅
    uint16_t width_;
    
    //! パネル全体の高さ
    uint16_t height_;
};

#endif
