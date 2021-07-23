/**
 * @file    Simulator.cpp
 * @brief   シミュレータークラスの実装
 * @author  Yoshito Nakaue
 * @date    2021/07/24
 */

#include "Simulator.hpp"
#include "PanelManager.hpp"

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

        window_ = SDL_CreateWindow(
            "TouchLED-Simulator",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            1280,
            720,
            SDL_WINDOW_SHOWN
        );

        renderer_ = SDL_CreateRenderer(window_, -1, 0);

        update();
    }

    void Simulator::update()
    {
        SDL_SetRenderDrawColor(renderer_, 0, 255, 0, 255);
        SDL_RenderClear(renderer_);
        SDL_RenderPresent(renderer_);
    }

    void Simulator::quit()
    {
        SDL_DestroyRenderer(renderer_);
        SDL_DestroyWindow(window_);
        SDL_Quit();
    }
    
}
