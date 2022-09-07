/**
 * @file    PanelManager.cpp
 * @brief   パネル情報管理クラスの実装
 * @author  Yoshito Nakaue
 * @date    2022/08/18
 */

#include "PanelManager.hpp"

#include <iostream>
#include <cstdlib>

#include "Common.hpp"

namespace tll
{

    IPanelManager* IPanelManager::create()
    {
        return new PanelManager();
    }

    PanelManager::PanelManager()
    {
        printLog("Create Panel manager");
    }

    PanelManager::~PanelManager()
    {
        printLog("Destroy Panel manager");
    }

    void PanelManager::init(uint16_t width, uint16_t height) noexcept
    {
        this->width_  = width;
        this->height_ = height;

        // Initialize color info with 0 (Black)
        for (int i = 0; i < this->width_ * this->height_; i++)
        {
            this->color_.push_back(Color());
        }
    }

    inline void PanelManager::drawPixel(uint16_t x, uint16_t y, Color c) noexcept
    {
        if (x >= this->width_ || y >= this->height_)
            return;

        this->color_[y * width_ + x] = c;
    }

    void PanelManager::drawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, Color c) noexcept
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

    void PanelManager::drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, Color c) noexcept
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

        if (y1 < y2) stepY = 1;
        else         stepY = -1;

        for (int32_t x = x1; x <= x2; x++)
        {
            if (steep)
            {
                this->drawPixel(y, x, c);
            }
            else
            {
                this->drawPixel(x, y, c);
            }

            error = error - deltaY;
            if (error < 0)
            {
                y = y + stepY;
                error = error + deltaX;
            }
        }
    }

    void PanelManager::drawCircle(uint16_t x, uint16_t y, uint16_t rad, Color c) noexcept
    {
        auto draw = [this](int32_t pos_x, int32_t pos_y, int32_t xC, int32_t yC, Color c)
        {
            this->drawPixel(xC + pos_x, yC + pos_y, c);
            this->drawPixel(xC + pos_x, yC - pos_y, c);
            this->drawPixel(xC - pos_x, yC + pos_y, c);
            this->drawPixel(xC - pos_x, yC - pos_y, c);
            this->drawPixel(xC + pos_y, yC + pos_x, c);
            this->drawPixel(xC - pos_y, yC + pos_x, c);
            this->drawPixel(xC + pos_y, yC - pos_x, c);
            this->drawPixel(xC - pos_y, yC - pos_x, c);
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

    void PanelManager::clear() noexcept
    {
        for (int y = 0; y < height_; y++)
        {
            for (int x = 0; x < width_; x++)
            {
                color_[y * width_ + x] = Color();
            }
        }
    }

}
