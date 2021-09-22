/**
 * @file PanelBase.hpp
 * @brief Base class of LED panel
 * @author Yoshito Nakaue
 * @date 2021/09/21
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
    PanelBase(uint16_t width = 8, uint16_t height = 8, uint16_t num_driver = 1);

    /**
     * @brief  LED全体の点灯状態を更新する
     */
    void update();

    /**
     * @fn init()
     * @brief LED制御モジュールを扱うアドレスを指定して初期化
     */
    void init(uint16_t addr = 0x70);

protected:
    /**
     * @brief  マトリクスの各ピクセルの情報を登録する
     */
    virtual void registerMatrixInfo() = 0;

    //! 各ピクセルの情報を格納する配列
    std::vector<PixelInfo> pixels_info_;

private:
    //! 8x8(1)用描画用バッファ
    uint16_t disp_buff1[8] = {};

    //! 8x8(2)用描画用バッファ
    uint16_t disp_buff2[8] = {};

    //! パネル全体の横幅
    uint16_t width_;
    
    //! パネル全体の高さ
    uint16_t height_;

    //! I2C通信用アドレス
    uint16_t addr_;

    //! Number of LED driver
    uint16_t num_driver_;
};

#endif
