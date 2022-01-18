/**
 * @file    Simulator.hpp
 * @brief   シミュレータークラス
 * @author  Yoshito Nakaue
 * @date    2021/07/27
 */

#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include "SDL.h"
#include <opencv2/opencv.hpp>

namespace tll
{
    const uint8_t NONE   = 0b00000000;
    const uint8_t CHIP   = 0b00000001;
    const uint8_t MARBLE = 0b00000010;
    const uint8_t ALL    = 0b11111111;

    /**
     * @brief  シミュレータークラス
     */
    class Simulator
    {
    public:
        /**
         * @fn      static Simulator* getInstance()
         * @brief   Simulatorクラスのインスタンスを取得
         * @return  Simulatorクラスのインスタンス
         */
        static Simulator* getInstance()
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
         * @fn     void start()
         * @brief  シミュレーションを開始する
         */
        void start(uint8_t simulate_mode);

        /**
         * @fn     void update()
         * @brief  シミュレーションを更新する
         */
        void update();

        /**
         * @fn     void quit()
         * @brief  シミュレーションを終了する
         */
        void quit();

        int getPixelSize() { return pixel_size; }
        int getBlankSize() { return blank_size; }

    protected:
        Simulator() {};

        /// Simulatorクラスインスタンス
        static Simulator* pInstance_;

    private:
        /// シミュレーション用ウィンドウ
        SDL_Window* window_;

        /// シミュレーション用レンダラー
        SDL_Renderer* renderer_;

        /// Renderer for appearence simulation
        cv::Mat simulator_img_;

        /// 各ピクセルのサイズ
        int pixel_size;

        int blank_size;

        /// Simulation mode
        uint8_t mode_;
    };

}

#endif
