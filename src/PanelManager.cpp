/**
 * @file    PanelManager.cpp
 * @brief   パネル情報管理クラスの実装
 * @author  Yoshito Nakaue
 * @date    2021/08/05
 */

#include "PanelManager.hpp"
#include <iostream>

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

        // Initialize color info with 0 (Black)
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
                if ((x + j) < width_ && (y + i) < height_)
                {
                    color_[(y + i) * width_ + (x + j)] = c;
                }
            }
        }
    }

    void PanelManager::clear()
    {
        for (int y = 0; y < height_; y++)
        {
            for (int x = 0; x < width_; x++)
            {
                color_[y * width_ + x] = 0;
            }
        }
    }

}
