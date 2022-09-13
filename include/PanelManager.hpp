/**
 * @file    PanelManager.hpp
 * @brief   パネル情報管理クラス
 * @author  Yoshito Nakaue
 * @date    2022/08/18
 */

#ifndef __PANEL_MANAGER_HPP__
#define __PANEL_MANAGER_HPP__

#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "Color.hpp"

namespace tll
{

    /* LEDパネルの状態管理インターフェースクラス */
    class IPanelManager
    {
    public:
        virtual ~IPanelManager() = default;

        // インスタンスを作成
        static IPanelManager* create();

        // パネルサイズ・色を初期化する
        virtual void init(uint16_t width, uint16_t height) = 0;

        // 点を描画する
        virtual void drawPixel(uint16_t x, uint16_t y, Color c) = 0;

        // 矩形を描画する
        virtual void drawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, Color c) = 0;

        // 直線を描画する
        virtual void drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, Color c) = 0;

        // 円を描画する
        virtual void drawCircle(uint16_t x, uint16_t y, uint16_t rad, Color c) = 0;

        // 全ピクセルを黒で塗りつぶす
        virtual void clear() = 0;

        uint16_t getWidth()  noexcept { return width_;  }
        uint16_t getHeight() noexcept { return height_; }

        void setWidth(uint16_t width)   noexcept { this->width_ = width;   }
        void setHeight(uint16_t height) noexcept { this->height_ = height; }

        // ピクセル数を取得する
        uint16_t getPixelsNum() noexcept { return width_ * height_; }

        // 特定座標の現在の色を取得する
        Color getColor(int x, int y)
        {
            Color color;

            try
            {
                color = this->color_.at(y * width_ + x);
            }
            catch (std::out_of_range& e)
            {
                std::cerr << "[ERROR]: " << e.what() << std::endl;
            }

            return color;
        }

    protected:
        /// Color infomation for each pixel
        std::vector<Color> color_;

        /// Width of LED panel
        uint16_t width_;
        
        /// Height of LED panel
        uint16_t height_;
    };

    /* LEDパネルの状態管理クラス */
    class PanelManager : public IPanelManager
    {
    public:
        PanelManager();
        ~PanelManager() override;

        // パネルサイズ・色を初期化する
        void init(uint16_t width, uint16_t height) noexcept override;

        // 点を描画する
        void drawPixel(uint16_t x, uint16_t y, Color c) noexcept override;

        // 矩形を描画する
        void drawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, Color c) noexcept override;

        // 直線を描画する
        void drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, Color c) noexcept override;

        // 円を描画する
        void drawCircle(uint16_t x, uint16_t y, uint16_t rad, Color c) noexcept override;

        // 全ピクセルを黒で塗りつぶす
        void clear() noexcept override;
    };

}

#endif
