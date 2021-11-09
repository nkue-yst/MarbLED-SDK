/**
 * @file STP16CP05_Base.hpp
 * @brief Base class of STP16CP05
 * @author Yoshito Nakaue
 * @date 2021/11/09
 */

#ifndef STP16CP05_BASE_HPP
#define STP16CP05_BASE_HPP

#include "PanelBase.hpp"

/**
 * @brief  Base class of STP16CP05
 */
class STP16CP05_Base : public PanelBase
{
public:
    /**
     * @brief  矩形マトリクスLED用コンストラクタ
     */
    STP16CP05_Base(uint16_t width = 8, uint16_t height = 8, uint16_t num_driver = 1);

    /**
     * @fn init()
     * @brief LED制御モジュールを扱うアドレスを指定して初期化
     */
    void init(uint16_t addr = 0x70) override;

    /**
     * @brief  LED全体の点灯状態を更新する
     */
    void update() override;

};

#endif
