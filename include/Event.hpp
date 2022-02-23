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

#include "osc/OscReceivedElements.h"
#include "osc/OscPacketListener.h"
#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"
#include "ip/IpEndpointName.h"

#include <cstdint>
#include <functional>
#include <vector>

namespace tll
{
    class OscReceiver : public osc::OscPacketListener
    {
    public:
        OscReceiver() {}
        ~OscReceiver() {}

    protected:
        virtual void ProcessMessage(const osc::ReceivedMessage& msg, const IpEndpointName& remote_end_pt) override
        {
            (void)remote_end_pt;
            try
            {
                if (strcmp(msg.AddressPattern(), "/test1") == 0)
                {
                    std::cout << "Test" << std::endl;
                }
                else
                {
                }
            }
            catch (osc::Exception& e)
            {
                std::cout << "OSC error" << std::endl;
            }
        }
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
         */
        void init();

        void quit();

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

        /// Osc message receiver
        OscReceiver* osc_receiver_;

        /// UDP listener socket
        UdpListeningReceiveSocket* s_;

    public:
        /**
         * @fn     void updateState()
         * @brief  Update state of touch
         */
        void updateState();

        /// OscSender
        TUIO::OscSender* sender_;

        /// TuioServer
        TUIO::TuioServer* server_;

    private:
        /// Quit flag
        bool quit_flag_ = false;

        /// Previous state of mouse right button (for test)
        bool is_down_right_button = false;

        /// Previous state of mouse left button (for test)
        bool is_down_left_button = false;

        /// Tuio object list
        std::vector<TUIO::TuioObject*> tobj_list_;

    };

}

#endif
