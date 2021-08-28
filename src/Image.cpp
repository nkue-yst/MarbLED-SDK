/**
 * @file    Image.cpp
 * @brief   Image class
 * @author  Yoshito Nakaue
 * @date    2021/08/28
 */

#include "Image.hpp"
#include "PanelManager.hpp"

namespace tll
{
    Image::Image()
    {
        img_surface_ = nullptr;
    }

    void Image::loadBMP(const char* file)
    {
        img_surface_ = SDL_LoadBMP(file);
    }

    void Image::draw()
    {
        
        SDL_Surface* temp_surface
            = SDL_CreateRGBSurface(
                0,
                PanelManager::getInstance()->getWidth(),
                PanelManager::getInstance()->getHeight(),
                16,
                0,
                0,
                0,
                0
            );

        SDL_BlitScaled(img_surface_, NULL, temp_surface, NULL);

        SDL_LockSurface(temp_surface);

        SDL_PixelFormat* fmt;
        uint8_t r, g, b;

        SDL_GetRGB(temp_surface->format, fmt, r, g, b);

        SDL_UnlockSurface(temp_surface);
        SDL_FreeSurface(temp_surface);
    }
}
