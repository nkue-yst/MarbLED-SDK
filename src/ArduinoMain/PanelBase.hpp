/**
 * @file PanelBase.hpp
 * @brief Base class of LED panel
 * @author Yoshito Nakaue
 * @date 2021/11/09
 */

#ifndef PANEL_BASE_HPP
#define PANEL_BASE_HPP

#include "PixelInfo.hpp"
#include <vector>

/**
 * @brief  Type of LED driver
 */
enum EDriverName : uint16_t
{
    HT16K33,
    STP16CP05
};

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
    virtual void update() = 0;

    /**
     * @fn init()
     * @brief LED制御モジュールを扱うアドレスを指定して初期化
     */
    virtual void init(uint16_t addr = 0x70) = 0;

protected:
    /**
     * @brief  マトリクスの各ピクセルの情報を登録する
     */
    virtual void registerMatrixInfo() = 0;

    //! 各ピクセルの情報を格納する配列
    std::vector<PixelInfo> pixels_info_;

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
