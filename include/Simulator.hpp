/**
 * @file    Simulator.hpp
 * @brief   シミュレータークラス
 * @author  Yoshito Nakaue
 * @date    2021/07/24
 */

#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include "SDL.h"

namespace tll
{

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
        void start();

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

    protected:
        Simulator() {};

        /// Simulatorクラスインスタンス
        static Simulator* pInstance_;

    private:
        /// シミュレーション用ウィンドウ
        SDL_Window* window_;

        /// シミュレーション用レンダラー
        SDL_Renderer* renderer_;
    };

}

#endif
