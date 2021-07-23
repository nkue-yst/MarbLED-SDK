/**
 * @file    PanelManager.cpp
 * @brief   パネル情報管理クラスの実装
 * @author  Yoshito Nakaue
 * @date    2021/07/23
 */

#include "PanelManager.hpp"

namespace tll
{

    PanelManager* PanelManager::pInstance_ = nullptr;

    void PanelManager::create()
    {
        if (!pInstance_)
        {
            pInstance_ = new PanelManager();
        }
    }

    void PanelManager::destroy()
    {
        delete pInstance_;
        pInstance_ = nullptr;
    }

    void PanelManager::init(uint16_t width, uint16_t height)
    {
        width_ = width;
        height_ = height;
    }

}
