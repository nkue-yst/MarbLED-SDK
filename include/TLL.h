/**
 * @file    TLL.h
 * @brief   API公開用ヘッダファイル
 * @author  Yoshito Nakaue
 * @date    2022/08/22
 */

#ifndef __TLL_H__
#define __TLL_H__

#include <cstdint>
#include <functional>
#include <string>
#include <vector>

#include "Image.hpp"
#include "Video.hpp"

/**
 * @namespace  tll
 * @brief  TouchLED-Libraryの名前空間
 */
namespace tll
{
    [[maybe_unused]]
    static const char* version = "1.2.0";

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
    void init(uint16_t width, uint16_t height, std::string LED_driver = "HT16K33");

    /**
     * @fn     bool loop()
     * @brief  Main loop on the framework
     */
    bool loop() noexcept;

    /**
     * @fn  void quit()
     * @brief  システム全体を終了
     */
    void quit();

    void drawPixel(uint16_t x, uint16_t y, Color color);
    void drawPixels(std::vector<uint16_t> x, std::vector<uint16_t> y, Color color);

    /**
     * @fn     void drawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
     * @brief  Draw rectangle.
     * @param  x      The x location of the rectangle's upper left corner
     * @param  y      The y location of the rectangle's upper left corner
     * @param  w      The width of the rectangle
     * @param  h      The height of the rectangle
     * @param  color  The color of the rectangle
     */
    void drawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, Color color);

    /**
     * @fn     void drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t c)
     * @brief  Draw line
     * @param  x1     The x location of the starting line
     * @param  y1     The y location of the starting line
     * @param  x2     The x location of the ending line
     * @param  y2     The y location of the ending line
     * @param  color  The color of the line
     */
    void drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, Color color);

    /**
     * @fn     void drawCircle(uint16_t x, uint16_t y, uint16_t rad, uint16_t c)
     * @brief  Draw circle
     * @param  x      The x location of the center
     * @param  y      The y location of the center
     * @param  rad    The radian of the circle
     * @param  color  The color of the circle
     */
    void drawCircle(uint16_t x, uint16_t y, uint16_t rad, Color color);

    /**
     * @fn     void print(const char* str)
     * @brief  Print text
     * @param  std::string str  String to print
     * @param  color            Color to print string
     */
    void print(std::string str, uint16_t x, uint16_t y, uint16_t size, Color color);

    /**
     * @fn     void clear()
     * @brief  Clear panel with black.
     */
    void clear();

    /**
     * @fn      tll::Image* loadImage(const char* file)
     * @brief   Load image file
     * @param   file  Image file path
     * @return  Image class data
     */
    tll::Image* loadImage(const char* file);

    /**
     * @fn      tll::Video loadVideo(const char* file)
     * @brief   Load video file
     * @param   file  Video file path
     * @return  Video class data
     */
    tll::Video loadVideo(const char* file);

    /**
     * @fn      std::string timeToString()
     * @brief   Get current time (Hours and minutes)
     * @return  Current time (String)
     */
    std::string timeToString();

    /**
     * @brief 
     * 
     */
    uint32_t getTouchedNum();
}

#endif
