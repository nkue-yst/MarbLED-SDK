/**
 * @file    PanelManager.cpp
 * @brief   パネル情報管理クラスの実装
 * @author  Yoshito Nakaue
 * @date    2021/07/27
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

        for (int i = 0; i < width_ * height_; i++)
        {
            color_.push_back(0);
        }
    }

    void PanelManager::drawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t c)
    {
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++)
            {
                color_[(y + i) * width_ + (x + j)] = c;
            }
        }
    }

}
