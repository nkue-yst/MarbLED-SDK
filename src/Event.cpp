/**
 * @file    Event.cpp
 * @brief   Event handling
 * @author  Yoshito Nakaue
 * @date    2021/08/28
 */

#include "Event.hpp"
#include "PanelManager.hpp"
#include "Simulator.hpp"

#include "SDL.h"

#include "TuioTime.h"

#include <iostream>

namespace tll
{
    EventHandler* EventHandler::pInstance_ = nullptr;

    void EventHandler::create()
    {
        if (!pInstance_)
        {
            pInstance_ = new EventHandler();
        }
    }

    void EventHandler::destroy()
    {
        delete pInstance_;
        pInstance_ = nullptr;
    }

    void EventHandler::init()
    {
        this->sender_ = new TUIO::UdpSender();
        this->server_ = new TUIO::TuioServer(this->sender_);

        this->server_->initFrame(TUIO::TuioTime::getSystemTime());
    }

    void EventHandler::updateState()
    {
        // For test using mouse button
        SDL_PumpEvents();
        int32_t pos_x;
        int32_t pos_y;

        if (!is_down_left_button && SDL_GetMouseState(&pos_x, &pos_y) & SDL_BUTTON(1))
        {
            int32_t p_size = Simulator::getInstance()->getPixelSize();
            int32_t b_size = Simulator::getInstance()->getBlankSize();

            int32_t pre_x = b_size;
            int32_t pre_y = b_size;
            int32_t current_x, current_y;

            for (int32_t x = 0; x < PanelManager::getInstance()->getWidth(); x++)
            {
                current_x = pre_x + p_size;

                if (pre_x <= pos_x && pos_x <= current_x)
                    pos_x = x;

                pre_x = current_x + b_size;
            }

            for (int y = 0; y < PanelManager::getInstance()->getHeight(); y++)
            {
                current_y = pre_y + p_size;

                if (pre_y <= pos_y && pos_y <= current_y)
                    pos_y = y;

                pre_y = current_y + b_size;
            }

            TUIO::TuioObject* tobj = this->server_->addTuioObject(0, pos_x, pos_y, 0);
            this->server_->commitFrame();
            this->tobj_list_.push_back(tobj);
            is_down_left_button = true;
        }
        else if (is_down_left_button && !(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(1)))
        {
            this->server_->removeTuioObject(this->tobj_list_.back());
            this->server_->commitFrame();
            this->tobj_list_.pop_back();
            is_down_left_button = false;
        }
        
        // Mouse right click to quit
        if (!is_down_right_button && SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(3))
        {
            is_down_right_button = true;
            quit_flag_ = true;
        }
    }

}
