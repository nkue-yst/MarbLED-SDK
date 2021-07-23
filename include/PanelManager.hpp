/**
 * @file PanelManager.hpp
 * @brief パネル情報管理クラス
 * @author Yoshito Nakaue
 * @date 2021/07/23
 */

#ifndef PANEL_MANAGER_HPP
#define PANEL_MANAGER_HPP

namespace tll
{

/**
 * @brief  LEDパネルの状態を管理するクラス
 */
class PanelManager
{
public:
    /**
     * @fn  static PanelManager* getPanelManager()
     * @brief  シングルトンのインスタンスを取得
     * @return  Panel Managerのインスタンス
     */
    static PanelManager* getPanelManager()
    {
        return p_panel_manager_;
    }

    /**
     * @fn static void create()
     * @brief インスタンスを作成
     */
    static void create();

    /**
     * @fn static void destroy()
     * @brief インスタンスを破棄
     */
    static void destroy();

protected:
    PanelManager();

    ///  シングルトン用インスタンス
    static PanelManager* p_panel_manager_;
};


}

#endif
