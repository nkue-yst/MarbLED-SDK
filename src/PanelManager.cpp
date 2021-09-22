/**
 * @file    PanelManager.cpp
 * @brief   パネル情報管理クラスの実装
 * @author  Yoshito Nakaue
 * @date    2021/08/30
 */

#include "PanelManager.hpp"

#include <iostream>
#include <cstdlib>

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

    void PanelManager::drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t c)
    {
        bool steep = std::abs(y2 - y1) > std::abs(x2 - x1);
        if (steep)
        {
            std::swap(x1, y1);
            std::swap(x2, y2);
        }
        
        if (x1 > x2)
        {
            std::swap(x1, x2);
            std::swap(y1, y2);
        }

        int32_t deltaX = x2 - x1;
        int32_t deltaY = std::abs(y2 - y1);
        int32_t error  = deltaX / 2;
        int32_t stepY;
        int32_t y = y1;

        if (y1 < y2)
        {
            stepY = 1;
        }
        else
        {
            stepY = -1;
        }

        for (int32_t x = x1; x <= x2; x++)
        {
            if (steep)
            {
                PanelManager::getInstance()->drawPixel(y, x, c);
            }
            else
            {
                PanelManager::getInstance()->drawPixel(x, y, c);
            }

            error = error - deltaY;
            if (error < 0)
            {
                y = y + stepY;
                error = error + deltaX;
            }
        }
    }

    void PanelManager::drawCircle(uint16_t x, uint16_t y, uint16_t rad, uint8_t c)
    {
        auto draw = [](int32_t pos_x, int32_t pos_y, int32_t xC, int32_t yC, uint8_t c)
        {
            PanelManager::getInstance()->drawPixel(xC + pos_x, yC + pos_y, c);
            PanelManager::getInstance()->drawPixel(xC + pos_x, yC - pos_y, c);
            PanelManager::getInstance()->drawPixel(xC - pos_x, yC + pos_y, c);
            PanelManager::getInstance()->drawPixel(xC - pos_x, yC - pos_y, c);
            PanelManager::getInstance()->drawPixel(xC + pos_y, yC + pos_x, c);
            PanelManager::getInstance()->drawPixel(xC - pos_y, yC + pos_x, c);
            PanelManager::getInstance()->drawPixel(xC + pos_y, yC - pos_x, c);
            PanelManager::getInstance()->drawPixel(xC - pos_y, yC - pos_x, c);
        };

        int p = 1 - rad;
        int drawX = 0;
        int drawY = rad;

        draw(drawX, drawY, x, y, c);

        while (drawX <= drawY)
        {
            drawX++;
            if (p < 0)
            {
                p += 2 * drawX + 1;
            }
            else
            {
                p += 2 * (drawX - drawY) + 1;
                drawY--;
            }
            draw(drawX, drawY, x, y, c);
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
