/**
 * @file    Event.hpp
 * @brief   Event handling
 * @author  Yoshito Nakaue
 * @date    2021/08/28
 */

#ifndef EVENT_HPP
#define EVENT_HPP

#include <cstdint>
#include <vector>

namespace tll
{
    /**
     * @brief  Struct of touched point
     */
    struct Point
    {
    public:
        /// Point ID
        uint32_t id_;

        /// x-coordinate
        uint32_t x;

        /// y-coordinate
        uint32_t y;
    };


    /**
     * @brief  Event handling class
     */
    class Event
    {
    public:
        /**
         * @fn      static Event* getInstance()
         * @brief   Get instance of event class
         * @return  Instance of Event class
         */
        static Event* getInstance()
        {
            return pInstance_;
        }

        /**
         * @fn
         * @brief
         */
        static void create();

        /**
         * @fn
         * @brief
         */
        static void destroy();

        /**
         * @fn
         * @brief
         * @return
         */
        bool getQuitFlag() { return quit_flag_; }

        /**
         * @fn
         * @brief
         */
        void setQuitFlag(bool new_flag) { quit_flag_ = new_flag; }

    protected:
        Event() {}

        /// Instance for singleton
        static Event* pInstance_;

    private:
        /**
         * @fn     void addTouchedPoint(Point* point)
         * @brief  Add touched point
         */
        void addTouchedPoint(Point& point);

        /**
         * @fn     void removeTouchedPoint(uint32_t id)
         * @brief  Remove touched point
         */
        void removeTouchedPoint(uint32_t id);

        /// List of touched points
        std::vector<Point> touched_points_;

        /// Quit flag
        bool quit_flag_ = false;

    };
}

#endif
