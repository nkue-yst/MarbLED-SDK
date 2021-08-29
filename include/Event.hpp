/**
 * @file    Event.hpp
 * @brief   Event handling
 * @author  Yoshito Nakaue
 * @date    2021/08/28
 */

#ifndef EVENT_HPP
#define EVENT_HPP

#include <cstdint>
#include <functional>
#include <vector>

namespace tll
{
    /**
     * @brief  Struct of touched point
     */
    struct Point
    {
    public:
        Point(uint32_t x = 0, uint32_t y = 0, uint32_t id = 0)
        {
            x_  = x;
            y_  = y;
            id_ = id;
        }

        /// Point ID
        uint32_t id_;

        /// x-coordinate
        uint32_t x_;

        /// y-coordinate
        uint32_t y_;
    };


    /**
     * @brief  Event handling class
     */
    class EventHandler
    {
    public:
        /**
         * @fn      static Event* getInstance()
         * @brief   Get instance of event class
         * @return  Instance of Event class
         */
        static EventHandler* getInstance()
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
        EventHandler()
        : event_x_(0)
        , event_y_(0)
        {}

        /// Instance for singleton
        static EventHandler* pInstance_;

    public:
        /**
         * @fn     void updateState()
         * @brief  Update state of touch
         */
        void updateState();

        /**
         * @fn     void addTouchedPoint(Point* point)
         * @brief  Add touched point
         */
        void addTouchedPoint(Point point);

        /**
         * @fn     void removeTouchedPoint(uint32_t id)
         * @brief  Remove touched point
         */
        void removeTouchedPoint(uint32_t id);

        /**
         * @fn
         * @brief
         */
        void addFunction(uint8_t type, std::function<void(void)> func);

        /**
         * @fn     uint32_t getTouchedX()
         * @brief  Get x-coordinate of touched point
         */
        uint32_t getEventX() { return event_x_; }

        /**
         * @fn     uint32_t getTouchedY()
         * @brief  Get y-coordinate of touched point
         */
        uint32_t getEventY() { return event_y_; }

    private:
        /// List of touching event
        std::vector<std::function<void(void)>> touch_down_events_;

        /// List of releasing event
        std::vector<std::function<void(void)>> touch_up_events_;

        /// List of moving event
        std::vector<std::function<void(void)>> touch_move_events_;

        /// List of touched points
        std::vector<Point> touched_points_;

        /// x-coordinate for being used by user
        uint32_t event_x_;

        /// y-coordinate for being used by user
        uint32_t event_y_;

        /// Quit flag
        bool quit_flag_ = false;

        /// Previous state of mouse right button (for test)
        bool is_down_right_button = false;

        /// Previous state of mouse left button (for test)
        bool is_down_left_button = false;

    };

}

#endif
