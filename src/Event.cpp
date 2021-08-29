/**
 * @file    Event.cpp
 * @brief   Event handling
 * @author  Yoshito Nakaue
 * @date    2021/08/28
 */

#include "Event.hpp"

#include "SDL.h"
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

    void EventHandler::updateState()
    {
        ///////////////////////////////////////
        // 状態の変化を取得 addTouchedPoint()等 //
        ///////////////////////////////////////

        // For test using mouse button
        SDL_PumpEvents();
        if (!is_down_left_button && SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(1))
        {
            addTouchedPoint(Point(3, 3, 0));
            is_down_left_button = true;
        }
        else if (is_down_left_button && !(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(1)))
        {
            removeTouchedPoint(0);
            is_down_left_button = false;
        }
        
        if (!is_down_right_button && SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(3))
        {
            is_down_right_button = true;
            quit_flag_ = true;
        }
    }

    void EventHandler::addTouchedPoint(Point point)
    {
        touched_points_.push_back(point);

        event_x_ = point.x_;
        event_y_ = point.y_;

        for (size_t i = 0; i < touch_down_events_.size(); ++i)
        {
            touch_down_events_[i]();
        }
    }

    void EventHandler::removeTouchedPoint(uint32_t id)
    {
        Point iter;

        for (unsigned int i = 0; i < touched_points_.size(); i++)
        {
            iter = touched_points_[i];

            if (iter.id_ == id)
            {
                event_x_ = iter.x_;
                event_y_ = iter.y_;

                for (size_t j = 0; j < touch_up_events_.size(); ++j)
                {
                    touch_up_events_[j]();
                }

                touched_points_.erase(touched_points_.begin() + i);
            }
        }
    }

    void EventHandler::addFunction(uint8_t type, std::function<void(void)> func)
    {
        if (type == 0)
        {
            touch_down_events_.push_back(func);
        }
        else if (type == 2)
        {
            touch_up_events_.push_back(func);
        }
    }

}
