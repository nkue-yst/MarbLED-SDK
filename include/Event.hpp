/**
 * @file    Event.hpp
 * @brief   Event handling
 * @author  Yoshito Nakaue
 * @date    2021/08/28
 */

#ifndef EVENT_HPP
#define EVENT_HPP

#include "TLL.h"

#include "TuioServer.h"
#include "UdpSender.h"

#include <cstdint>
#include <functional>
#include <vector>

namespace tll
{
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
        {}

        /// Instance for singleton
        static EventHandler* pInstance_;

    public:
        /**
         * @fn     void updateState()
         * @brief  Update state of touch
         */
        void updateState();

        /// Test of using tuio
        TUIO2::TuioServer tuio_server_;

    private:
        /// Quit flag
        bool quit_flag_ = false;

        /// Previous state of mouse right button (for test)
        bool is_down_right_button = false;

        /// Previous state of mouse left button (for test)
        bool is_down_left_button = false;

    };

}

#endif
