/**
 * @file    Event.cpp
 * @brief   Event handling
 * @author  Yoshito Nakaue
 * @date    2021/08/28
 */

#include "Event.hpp"

#include <iostream>

#include <cstdio>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#include "Common.hpp"
#include "PanelManager.hpp"

#include "TuioTime.h"

namespace tll
{
    IEventHandler* IEventHandler::create()
    {
        return new EventHandler();
    }

    EventHandler::EventHandler()
    {
        printLog("Create Event handler");
    }

    EventHandler::~EventHandler()
    {
        printLog("Destroy Event handler");
    }

    void EventHandler::init()
    {
        this->sender_ = new TUIO::UdpSender();
        this->server_ = new TUIO::TuioServer(this->sender_);

        this->server_->initFrame(TUIO::TuioTime::getSystemTime());

        std::thread osc_thread(threadListen);
        osc_thread.detach();
    }

    int kbhit()
    {
        struct termios oldt, newt;
        int ch;
        int oldf;

        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

        ch = getchar();

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        fcntl(STDIN_FILENO, F_SETFL, oldf);

        if (ch != EOF)
        {
            ungetc(ch, stdin);
            return 1;
        }

        return 0;
    }

    void EventHandler::updateState()
    {
        // Initialize frame for TUIO
        this->server_->initFrame(TUIO::TuioTime::getSessionTime());

        if (kbhit())
        {
            if (getchar() == 27)
            {
                this->setQuitFlag(true);
            }
        }
    }

    void OscReceiver::ProcessMessage(const osc::ReceivedMessage& msg, const IpEndpointName& remote_end_pt)
    {
        std::lock_guard<std::mutex> lock(this->osc_mutex_);

        (void)remote_end_pt;
        try
        {
            //std::cout << "Received osc message" << std::endl;
            osc::ReceivedMessageArgumentStream args = msg.ArgumentStream();
            osc::ReceivedMessage::const_iterator arg = msg.ArgumentsBegin();

            if (strcmp(msg.AddressPattern(), "/touch/0/point") == 0 || strcmp(msg.AddressPattern(), "/touch/0/delete") == 0)
            {
                int32_t x = (arg++)->AsInt32();
                int32_t y = (arg++)->AsInt32();
                //std::cout << x << ", " << y << std::endl;

                if (x == -1 && y == -1)
                {
                    TLL_ENGINE(EventHandler)->server_->removeTuioObject(TLL_ENGINE(EventHandler)->tobj_list_.back());
                    TLL_ENGINE(EventHandler)->server_->commitFrame();
                    TLL_ENGINE(EventHandler)->tobj_list_.pop_back();
                }
                else if (TLL_ENGINE(EventHandler)->tobj_list_.empty())
                {
                    TLL_ENGINE(EventHandler)->server_->initFrame(TUIO::TuioTime::getSessionTime());
                    TUIO::TuioObject* tobj = TLL_ENGINE(EventHandler)->server_->addTuioObject(0, x, y, 0);
                    TLL_ENGINE(EventHandler)->tobj_list_.push_back(tobj);
                    TLL_ENGINE(EventHandler)->server_->commitFrame();
                }
                else if (!TLL_ENGINE(EventHandler)->tobj_list_.empty())
                {
                    TLL_ENGINE(EventHandler)->server_->initFrame(TUIO::TuioTime::getSessionTime());
                    TLL_ENGINE(EventHandler)->server_->updateTuioObject(TLL_ENGINE(EventHandler)->tobj_list_[0], x, y, 0);
                    TLL_ENGINE(EventHandler)->server_->commitFrame();
                }
            }
        }
        catch (osc::Exception& e)
        {
            std::cout << "OSC error" << std::endl;
        }
    }

    void threadListen()
    {
        OscReceiver receiver;
        UdpListeningReceiveSocket sock(IpEndpointName(IpEndpointName::ANY_ADDRESS, 9000), &receiver);

        sock.Run();
    }

}
