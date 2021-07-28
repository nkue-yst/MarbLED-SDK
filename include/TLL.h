/**
 * @file    TLL.h
 * @brief   API公開用ヘッダファイル
 * @author  Yoshito Nakaue
 * @date    2021/08/04
 */

#ifndef _TLL_H_
#define _TLL_H_

#include <cstdint>
#include <string>

/**
 * @namespace  tll
 * @brief  TouchLED-Libraryの名前空間
 */
namespace tll
{
    /// Monochrome LED is lit.
    constexpr int ON = 1;

    /// Monochrome LED is unlit.
    constexpr int OFF = 0;

    /**
     * @fn  void init(uint16_t width, uint16_t height)
     * @brief  システム全体の初期化
     * @param  width  パネルの横幅
     * @param  height  パネルの高さ
     */
    void init(uint16_t width, uint16_t height);

    /**
     * @fn  void quit()
     * @brief  システム全体を終了
     */
    void quit();

    /**
     * @fn     void drawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
     * @brief  Draw rectangle.
     * @param  x  The x location of the rectangle's upper left corner
     * @param  y  The y location of the rectangle's upper left corner
     * @param  w  The width of the rectangle
     * @param  h  The height of the rectangle
     * @param  c  The color of the rectangle
     */
    void drawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t c);

    /**
     * @namespace  Palette
     * @brief      Color palette
     */
    namespace Palette
    {
        uint8_t color(std::string color_name);
    }

    /**
     * @namespace  Simulation
     * @brief      シミュレーター用名前空間
     */
    namespace Simulation
    {
        /**
         * @fn     void start()
         * @brief  シミュレーションを開始
         */
        void start();

        /**
         * @fn     void update()
         * @brief  シミュレーションを更新
         */
        void update();

        /**
         * @fn     void quit()
         * @brief  シミュレーションを終了
         */
        void quit();
    }
}

#endif
