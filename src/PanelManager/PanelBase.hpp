/**
 * @file PanelBase.hpp
 * @brief LEDパネルの基底クラス
 * @author Yoshito Nakaue
 * @date 2021/07/13
 */

#ifndef PANEL_BASE_HPP
#define PANEL_BASE_HPP

#include "PixelInfo.hpp"
#include <vector>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

/**
 * @class PanelBase
 * @brief 1枚のLEDパネルを表すクラス
 */
class PanelBase : public Adafruit_LEDBackpack, public Adafruit_GFX
{
public:
    /**
     * @fn PanelBase(uint16_t width, uint16_t height)
     * @brief 矩形マトリクスLED用コンストラクタ
     */
    PanelBase(uint16_t width = 8, uint16_t height = 8);

    /**
     * @fn void update()
     * @brief メインループにてLED全体の点灯状態を更新する
     */
    void update();

    /**
     * @fn void drawPixel(int16_t x, int16_t y, uint16_t color)
     * @brief 指定座標を指定した色で点灯する（現状1bit）
     */
    void drawPixel(int16_t x, int16_t y, uint16_t color) override;

protected:
    /**
     * @fn void registerMatrixInfo()
     * @brief マトリクスの各ピクセルの情報を登録する
     */
    virtual void registerMatrixInfo() = 0;

    //! 各ピクセルの情報を格納する配列
    std::vector<PixelInfo> pixels_info_;

private:
    /**
     * @fn int calcX(int x)
     * @brief 指定したいx座標をLEDパネル上のx座標に変換する
     */
    int calcX(int x) { return x; }

    /**
     * @fn int calcY(int y)
     * @brief 指定したいy座標をLEDパネル上のy座標に変換する
     */
    int calcY(int y) { return (y + 1) % height_; }

    //! パネル全体の横幅
    uint16_t width_;
    
    //! パネル全体の高さ
    uint16_t height_;
};

#endif
