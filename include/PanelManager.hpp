/**
 * @file    PanelManager.hpp
 * @brief   パネル情報管理クラス
 * @author  Yoshito Nakaue
 * @date    2021/07/23
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
