/**
 * @file    TLL.h
 * @brief   API公開用ヘッダファイル
 * @author  Yoshito Nakaue
 * @date    2021/10/19
 */

#ifndef _TLL_H_
#define _TLL_H_

#include "Image.hpp"
#include "Video.hpp"

#include <cstdint>
#include <functional>
#include <string>
#include <vector>

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
     * @fn     bool loop()
     * @brief  Main loop on the framework
     */
    bool loop();

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
     * @fn     void drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t c)
     * @brief  Draw line
     * @param  x1  The x location of the starting line
     * @param  y1  The y location of the starting line
     * @param  x2  The x location of the ending line
     * @param  y2  The y location of the ending line
     * @param  c   The color of the line
     */
    void drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t c);

    /**
     * @fn     void drawCircle(uint16_t x, uint16_t y, uint16_t rad, uint16_t c)
     * @brief  Draw circle
     * @param  x    The x location of the center
     * @param  y    The y location of the center
     * @param  rad  The radian of the circle
     * @param  c    The color of the circle
     */
    void drawCircle(uint16_t x, uint16_t y, uint16_t rad, uint8_t c);

    /**
     * @fn     void print(const char* str)
     * @brief  Print text
     * @param  const char* str  String to print
     */
    void print(const char* str);

    /**
     * @fn     void clear()
     * @brief  Clear panel with black.
     */
    void clear();

    /**
     * @fn      tll::Image loadImage(const char* file)
     * @brief   Load image file
     * @param   file  Image file path
     * @return  Image class data
     */
    tll::Image loadImage(const char* file);

    /**
     * @fn      tll::Video loadVideo(const char* file)
     * @brief   Load video file
     * @param   file  Video file path
     * @return  Video class data
     */
    tll::Video loadVideo(const char* file);


    /**
     * @namespace  Palette
     * @brief      Color palette
     */
    namespace Palette
    {
        uint8_t color(std::string color_name);
    }


    /**
     * @brief  Struct of touched point
     */
    struct Point
    {
    public:
        Point(uint32_t x = 0, uint32_t y = 0, uint32_t id = 0)
        {
            x_  = x;
            y_  = y;
            id_ = id;
        }

        /// Point ID
        uint32_t id_;

        /// x-coordinate
        uint32_t x_;

        /// y-coordinate
        uint32_t y_;
    };


    /**
     * @namespace  Event
     * @brief      For handling event
     */
    namespace Event
    {
        enum Type : uint8_t
        {
            TouchDown,
            TouchMove,
            TouchUp,
        };

        /**
         * @fn     std::vector<tll::Event::Point> getTouchedPoints()
         * @brief  Get all touched points
         */
        std::vector<struct tll::Point> getTouchedPoints();

        /**
         * @fn      bool isTouched()
         * @brief   Return is touched
         * @return  Is touched at least one point
         */
        bool isTouched();

        uint32_t getTouchedX();
        uint32_t getTouchedY();

        void addFunction(Type event_type, std::function<void(void)>);
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
