/**
 * @file    Simulator.cpp
 * @brief   シミュレータークラスの実装
 * @author  Yoshito Nakaue
 * @date    2021/08/30
 */

#include "Simulator.hpp"
#include "PanelManager.hpp"
#include "Color.hpp"

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
        char window_title[] = "TouchLED-Simulator";

        /* Initialize the window for simulating the LED lighting state */
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
            window_title,
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
        if (!renderer_)
            return;

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

                uint8_t color_id = PanelManager::getInstance()->getColor(x, y);
                Color pixel_color = ColorPalette::getInstance()->getColorFromID(color_id);

                if (pixel_color.r_ == 0 && pixel_color.g_ == 0 && pixel_color.b_ == 0)
                {
                    SDL_SetRenderDrawColor(
                        renderer_,
                        20,
                        20,
                        20,
                        255
                    );
                }
                else
                {
                    SDL_SetRenderDrawColor(
                        renderer_,
                        pixel_color.r_,
                        pixel_color.g_,
                        pixel_color.b_,
                        255    
                    );
                }

                SDL_RenderFillRect(renderer_, &pixel);
            }
        }

        SDL_RenderPresent(renderer_);

        /* Update simulator for appearence simulation */
        this->simulator_img_ = cv::Mat(
            pixel_size * PanelManager::getInstance()->getHeight(),
            pixel_size * PanelManager::getInstance()->getWidth(),
            CV_8UC3,
            cv::Scalar(50, 50, 50)
        );

        for (int32_t y = 0; y < PanelManager::getInstance()->getHeight(); y++)
        {
            for (int32_t x = 0; x < PanelManager::getInstance()->getWidth(); x++)
            {
                Color p_color = ColorPalette::getInstance()->getColorFromID(PanelManager::getInstance()->getColor(x, y));

                if (!(p_color.r_ == 0 && p_color.g_ == 0 && p_color.b_ == 0))
                {
                    cv::circle(
                        this->simulator_img_,
                        cv::Point(
                            this->pixel_size * x + this->pixel_size / 2,
                            this->pixel_size * y + this->pixel_size / 2  
                        ),
                        pixel_size / 2 + pixel_size * 0.2f,
                        cv::Scalar(
                            ColorPalette::getInstance()->getColorFromID(PanelManager::getInstance()->getColor(x, y)).b_,
                            ColorPalette::getInstance()->getColorFromID(PanelManager::getInstance()->getColor(x, y)).g_,
                            ColorPalette::getInstance()->getColorFromID(PanelManager::getInstance()->getColor(x, y)).r_
                        ),
                        -1
                    );
                }
            }
        }

        cv::GaussianBlur(
            this->simulator_img_,
            this->simulator_img_,
            cv::Size(51, 51),
            0
        );

        cv::imshow("TouchLED-Simulator", this->simulator_img_);
        cv::waitKey(10);
    }

    void Simulator::quit()
    {
        SDL_DestroyRenderer(renderer_);
        SDL_DestroyWindow(window_);
    }
    
}
