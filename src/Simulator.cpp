/**
 * @file    Simulator.cpp
 * @brief   シミュレータークラスの実装
 * @author  Yoshito Nakaue
 * @date    2021/07/27
 */

#include "Simulator.hpp"
#include "PanelManager.hpp"

#include <algorithm>

namespace tll
{

    Simulator* Simulator::pInstance_ = nullptr;

    void Simulator::create()
    {
        if (!pInstance_)
        {
            pInstance_ = new Simulator();
        }
    }

    void Simulator::destroy()
    {
        delete pInstance_;
        pInstance_ = nullptr;
    }

    void Simulator::start()
    {
        SDL_Init(SDL_INIT_VIDEO);

        /* ディスプレイのサイズを取得 */
        SDL_Rect disp_info;
        SDL_GetDisplayUsableBounds(0, &disp_info);
        int disp_width  = disp_info.w;
        int disp_height = disp_info.h;

        // 1ピクセルのサイズをいい感じに設定
        pixel_size = std::min(disp_width / PanelManager::getInstance()->getWidth(),
            disp_height / PanelManager::getInstance()->getHeight()) * 0.5;
        blank_size = pixel_size / 3;

        window_ = SDL_CreateWindow(
            "TouchLED-Simulator",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            pixel_size * PanelManager::getInstance()->getWidth()  + (PanelManager::getInstance()->getWidth()  + 1) * blank_size,
            pixel_size * PanelManager::getInstance()->getHeight() + (PanelManager::getInstance()->getHeight() + 1) * blank_size,
            SDL_WINDOW_SHOWN
        );

        renderer_ = SDL_CreateRenderer(window_, -1, 0);

        update();
    }

    void Simulator::update()
    {
        /* Clear the screen with black */
        SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
        SDL_RenderClear(renderer_);

        /* Draw the LED matrix 
         * on the color information of each pixel.
         */
        SDL_Rect pixel;
        pixel.w = pixel.h = pixel_size;
        for (int y = 0; y < PanelManager::getInstance()->getHeight(); y++)
        {
            for (int x = 0; x < PanelManager::getInstance()->getWidth(); x++)
            {
                pixel.x = (pixel_size * x) + ((x + 1) * blank_size);
                pixel.y = (pixel_size * y) + ((y + 1) * blank_size);

                if (PanelManager::getInstance()->getColor(x, y) == 1)
                {
                    SDL_SetRenderDrawColor(renderer_, 255, 0, 0, 255);
                }
                else
                {
                    SDL_SetRenderDrawColor(renderer_, 20, 20, 20, 255);
                }

                SDL_RenderFillRect(renderer_, &pixel);
            }
        }

        SDL_RenderPresent(renderer_);
    }

    void Simulator::quit()
    {
        SDL_DestroyRenderer(renderer_);
        SDL_DestroyWindow(window_);
        SDL_Quit();
    }
    
}
