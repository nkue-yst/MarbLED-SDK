/**
 * @file    Event.cpp
 * @brief   Event handling
 * @author  Yoshito Nakaue
 * @date    2021/08/28
 */

#include "Event.hpp"

namespace tll
{
    Event* Event::pInstance_ = nullptr;

    void Event::create()
    {
        if (!pInstance_)
        {
            pInstance_ = new Event();
        }
    }

    void Event::destroy()
    {
        delete pInstance_;
        pInstance_ = nullptr;
    }

    void Event::addTouchedPoint(Point& point)
    {
        touched_points_.push_back(point);
    }

    void Event::removeTouchedPoint(uint32_t id)
    {
        Point iter;

        for (unsigned int i = 0; i < touched_points_.size(); i++)
        {
            iter = touched_points_[i];

            if (iter.id_ == id)
            {
                touched_points_.erase(touched_points_.begin() + i);
            }
        }
    }
}
