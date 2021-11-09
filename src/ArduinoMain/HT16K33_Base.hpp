/**
 * @file HT16K33_Base.hpp
 * @brief Base class of HT16K33
 * @author Yoshito Nakaue
 * @date 2021/11/09
 */

#ifndef HT16K33_BASE_HPP
#define HT16K33_BASE_HPP

#include "PanelBase.hpp"

/**
 * @brief  Base class of HT16K33
 */
class HT16K33_Base : public PanelBase
{
public:
    /**
     * @brief  矩形マトリクスLED用コンストラクタ
     */
    HT16K33_Base(uint16_t width = 8, uint16_t height = 8, uint16_t num_driver = 1);

    /**
     * @fn init()
     * @brief LED制御モジュールを扱うアドレスを指定して初期化
     */
    void init(uint16_t addr = 0x70) override;

    /**
     * @brief  LED全体の点灯状態を更新する
     */
    void update() override;

private:
    //! 8x8(1)用描画用バッファ
    uint16_t disp_buff1[8] = {};

    //! 8x8(2)用描画用バッファ
    uint16_t disp_buff2[8] = {};
};

#endif
