/**
 * @file    Event.cpp
 * @brief   Event handling
 * @author  Yoshito Nakaue
 * @date    2021/08/28
 */

#include "Event.hpp"
#include "Common.hpp"
#include "PanelManager.hpp"

#include "TuioTime.h"

#include <iostream>

#include <cstdio>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

namespace tll
{
    EventHandler* EventHandler::pInstance_ = nullptr;

    void EventHandler::create()
    {
        if (!pInstance_)
        {
            pInstance_ = new EventHandler();

            printLog("Create Event handler");
        }
    }

    void EventHandler::destroy()
    {
        delete pInstance_;
        pInstance_ = nullptr;

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

    void EventHandler::quit()
    {
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

    void threadListen()
    {
        OscReceiver receiver;
        UdpListeningReceiveSocket sock(IpEndpointName(IpEndpointName::ANY_ADDRESS, 9000), &receiver);

        //std::cout << "Start osc listen thread." << std::endl;
        sock.Run();
    }

}
