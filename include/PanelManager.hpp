/**
 * @file    PanelManager.hpp
 * @brief   パネル情報管理クラス
 * @author  Yoshito Nakaue
 * @date    2021/09/28
 */

#ifndef PANEL_MANAGER_HPP
#define PANEL_MANAGER_HPP

#include "Color.hpp"

#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace tll
{
    /**
     * @brief  LEDパネルの状態を管理するクラス
     */
    class PanelManager
    {
    public:
        /**
         * @fn      static PanelManager* getInstance()
         * @brief   シングルトンのインスタンスを取得
         * @return  Panel Managerのインスタンス
         */
        static PanelManager* getInstance()
        {
            return pInstance_;
        }

        /**
         * @fn     static void create()
         * @brief  インスタンスを作成
         */
        static void create();

        /**
         * @fn     static void destroy()
         * @brief  インスタンスを破棄
         */
        static void destroy();

        /**
         * @fn     void init(uint16_t width, uint16_t height)
         * @brief  パネル情報を初期化
         * @param  width  パネルの横幅
         * @param  height  パネルの高さ
         */
        void init(uint16_t width, uint16_t height);

        /**
         * 
        * @fn     void drawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
        * @brief  Draw rectangle.
        * @param  x  The x location of the rectangle's upper left corner
        * @param  y  The y location of the rectangle's upper left corner
        * @param  w  The width of the rectangle
        * @param  h  The height of the rectangl
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
         * 
         */
        void drawPixel(uint16_t x, uint16_t y, uint8_t color)
        {
            if (x >= width_ || y >= height_)
                return;

            color_[y * width_ + x] = color;
        }

        void drawPixelWithColor(uint16_t x, uint16_t y, tll::Color c)
        {
            if (x >= this->width_ || y >= this->height_)
                return;

            color_[y * this->width_ + x] = tll::ColorPalette::getInstance()->getIDFromRGB(c.r_, c.g_, c.b_);
        }

        /**
        * @fn     void clear()
        * @brief  Clear panel with black.
        */
        void clear();

        /**
         * @fn      uint16_t getWidth()
         * @brief   Get width of LED panel.
         * @return  Width of LED panel
         */
        uint16_t getWidth()  { return width_; }

        /**
         * @fn      uint16_t getHeight()
         * @brief   Get height of LED panel.
         * @return  Height of LED panel
         */
        uint16_t getHeight() { return height_; }

        /**
         * @fn      uint16_t getPixelsNum()
         * @brief   Get total number of pixels.
         * @return  Total number of pixels
         */
        uint16_t getPixelsNum() { return width_ * height_; }

        /**
         * @fn      uint8_t getColor(int x, int y)
         * @brief   Get color of the specified coordinates.
         * @return  Color of the specified coordinates
         */
        uint8_t getColor(int x, int y)
        {
            uint8_t color = 0;
            try {
                color = color_.at(y * width_ + x);
            }
            catch (std::out_of_range& e)
            {
                std::cerr << "[ERROR]: " << e.what() << std::endl;
            }

            return color;
        }

    protected:
        PanelManager() {}

        ///  シングルトン用インスタンス
        static PanelManager* pInstance_;

    private:
        /// Width of LED panel
        uint16_t width_;
        
        /// Height of LED panel
        uint16_t height_;

        /// Color infomation for each pixel
        std::vector<uint8_t> color_;
    };

}

#endif
