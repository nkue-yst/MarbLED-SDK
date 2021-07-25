/**
 * @file    PanelManager.hpp
 * @brief   パネル情報管理クラス
 * @author  Yoshito Nakaue
 * @date    2021/07/27
 */

#ifndef PANEL_MANAGER_HPP
#define PANEL_MANAGER_HPP

#include <cstdint>
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
        uint8_t getColor(int x, int y) { return color_[y * width_ + x]; }

    protected:
        PanelManager() {}

        ///  シングルトン用インスタンス
        static PanelManager* pInstance_;

    private:
        /// パネル全体の横幅
        uint16_t width_;
        
        /// パネル全体の高さ
        uint16_t height_;

        /// 各ピクセルの色情報
        std::vector<uint8_t> color_;
    };


}

#endif
