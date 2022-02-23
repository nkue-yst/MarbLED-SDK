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
#include <thread>

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

        this->osc_receiver_ = new OscReceiver();
        this->s_ = new UdpListeningReceiveSocket(IpEndpointName(IpEndpointName::ANY_ADDRESS, 7000), this->osc_receiver_);
    }

    void EventHandler::quit()
    {
        delete this->s_;
        delete this->osc_receiver_;
    }

    void EventHandler::updateState()
    {
        // Initialize frame for TUIO
        this->server_->initFrame(TUIO::TuioTime::getSessionTime());

        // For test using mouse button
        SDL_PumpEvents();
        int32_t pos_x;
        int32_t pos_y;

        // if (!is_down_left_button && SDL_GetMouseState(&pos_x, &pos_y) & SDL_BUTTON(1))
        if (SDL_GetMouseState(&pos_x, &pos_y) & SDL_BUTTON(1))
        {
            int32_t p_size = Simulator::getInstance()->getPixelSize();
            int32_t b_size = Simulator::getInstance()->getBlankSize();

            int32_t pre_x = b_size;
            int32_t pre_y = b_size;
            int32_t current_x, current_y;

            // Calculate X coordinate
            for (int32_t x = 0; x < PanelManager::getInstance()->getWidth(); x++)
            {
                current_x = pre_x + p_size;

                if (pre_x <= pos_x && pos_x <= current_x)
                {
                    pos_x = x;
                    break;
                }
                else if (x == PanelManager::getInstance()->getWidth() - 1)
                {
                    pos_x = -1;
                }

                pre_x = current_x + b_size;
            }

            // Calculate Y coordinate
            for (int y = 0; y < PanelManager::getInstance()->getHeight(); y++)
            {
                current_y = pre_y + p_size;

                if (pre_y <= pos_y && pos_y <= current_y)
                {
                    pos_y = y;
                    break;
                }
                else if (y == PanelManager::getInstance()->getHeight() - 1)
                {
                    pos_y = -1;
                }

                pre_y = current_y + b_size;
            }

            if (pos_x < 0 || pos_y < 0)
                return;

            // Add point
            if (!is_down_left_button)
            {
                TUIO::TuioObject* tobj = this->server_->addTuioObject(0, pos_x, pos_y, 0);
                this->server_->commitFrame();
                this->tobj_list_.push_back(tobj);
                is_down_left_button = true;
            }
            // Update point
            else
            {
                this->server_->updateTuioObject(this->tobj_list_[0], pos_x, pos_y, 0);
                this->server_->commitFrame();
            }
        }
        // Remove point
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

        /***** Receive OSC message *****/
        //this->s_->Run();
    }

}
