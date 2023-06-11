/**
 * @file    Event.cpp
 * @brief   Event handling
 * @author  Yoshito Nakaue
 * @date    2021/08/28
 */

#include "Event.hpp"

#include <cstdio>
#include <fcntl.h>
#include <iostream>
#include <termios.h>
#include <unistd.h>

#include "Common.hpp"
#include "OscHandler.hpp"
#include "PanelManager.hpp"

#include "TuioTime.h"

namespace tll
{
    IEventHandler* IEventHandler::create()
    {
        return new EventHandlerTuio();
    }

    EventHandlerTuio::EventHandlerTuio() noexcept
    {
        printLog("Create Event handler with TUIO");
    }

    EventHandlerTuio::~EventHandlerTuio() noexcept
    {
        printLog("Destroy Event handler with TUIO");
    }

    void EventHandlerTuio::init()
    {
        this->sender_ = new TUIO::UdpSender();
        this->server_ = new TUIO::TuioServer(this->sender_);

        this->server_->initFrame(TUIO::TuioTime::getSystemTime());

        std::thread osc_thread(threadListen);
        osc_thread.detach();
    }

    int EventHandlerTuio::kbhit()
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

    void EventHandlerTuio::updateState()
    {
        // Initialize frame for TUIO
        this->server_->initFrame(TUIO::TuioTime::getSessionTime());

        if (this->kbhit())
        {
            int ch = getchar();

            if (ch == 27)
            {
                this->setQuitFlag(true);
            }
            /* キー入力による即時アプリ切り替え処理 */
            else if (ch == '1')
            {
                OscHandler::sendMessageWithString("/tll/switch", "home", "127.0.0.1", 44101);
            }
            else if (ch == '2')
            {
                OscHandler::sendMessageWithString("/tll/switch", "TouchPoints", "127.0.0.1", 44101);
            }
            else if (ch == '3')
            {
                OscHandler::sendMessageWithString("/tll/switch", "Rain", "127.0.0.1", 44101);
            }
            else if (ch == '4')
            {
                OscHandler::sendMessageWithString("/tll/switch", "MultiTouchLine", "127.0.0.1", 44101);
            }
            else if (ch == '5')
            {
                OscHandler::sendMessageWithString("/tll/switch", "CockroachShooting", "127.0.0.1", 44101);
            }
            else if (ch == '6')
            {
                OscHandler::sendMessageWithString("/tll/switch", "Theremin", "127.0.0.1", 44101);
            }
            else if (ch == '7')
            {
                OscHandler::sendMessageWithString("/tll/switch", "MusicVisualizer", "127.0.0.1", 44101);
            }
            else if (ch == '8')
            {
                OscHandler::sendMessageWithString("/tll/switch", "ADIR01P_Light", "127.0.0.1", 44101);
            }
        }
    }

    void EventHandlerTuio::addTouchedPoint(uint32_t id, int32_t x, int32_t y)
    {
        this->server_->initFrame(TUIO::TuioTime::getSessionTime());

        if (this->tobj_list_[id] == nullptr)
        {
            TUIO::TuioObject* tobj = this->server_->addTuioObject(id, x, y, 0);
            this->tobj_list_[id] = tobj;
        }
        else
        {
            this->updateTouchedPoint(id, x, y);
        }

        this->server_->commitFrame();
    }

    void EventHandlerTuio::updateTouchedPoint(uint32_t id, int32_t x, int32_t y)
    {
        this->server_->updateTuioObject(this->tobj_list_[id], x, y, 0);
    }

    void EventHandlerTuio::removeTouchedPoint(uint32_t id)
    {
        this->server_->removeTuioObject(this->tobj_list_[id]);
        this->server_->commitFrame();

        this->tobj_list_.erase(id);
    }

    void EventHandlerTuio::addTouchedBlob(uint32_t id, int32_t x, int32_t y, int32_t w, int32_t h)
    {
        this->server_->initFrame(TUIO::TuioTime::getSessionTime());

        if (this->tblob_list_[id] == nullptr)
        {
            TUIO::TuioBlob* tblob = this->server_->addTuioBlob(x, y, 0, w, h, w * h);
            this->tblob_list_[id] = tblob;
        }
        else
        {
            this->updateTouchedBlob(id, x, y, w, h);
        }

        this->server_->commitFrame();
    }

    void EventHandlerTuio::updateTouchedBlob(uint32_t id, int32_t x, int32_t y, int32_t w, int32_t h)
    {
        this->server_->updateTuioBlob(this->tblob_list_[id], x, y, 0, w, h, w * h);
    }

    void EventHandlerTuio::removeTouchedBlob(uint32_t id)
    {
        this->server_->removeTuioBlob(this->tblob_list_[id]);
        this->server_->commitFrame();

        this->tblob_list_.erase(id);
    }

    uint32_t EventHandlerTuio::getTouchedNum()
    {
        return this->tobj_list_.size();
    }

    void OscReceiver::ProcessMessage(const osc::ReceivedMessage& msg, const IpEndpointName& remote_end_pt)
    {
        std::lock_guard<std::mutex> lock(this->osc_mutex_);

        (void)remote_end_pt;

        try
        {
            osc::ReceivedMessage::const_iterator arg = msg.ArgumentsBegin();
            std::vector<std::string> words = this->split(msg.AddressPattern());    // OSCメッセージを分割する

            /****************
             * タッチ点処理 *
             ****************/
            if (words.at(0) == "touch" && words.at(2) == "point")    // タッチ点が追加・更新された場合
            {
                int32_t x = (arg++)->AsInt32();
                int32_t y = (arg++)->AsInt32();

                TLL_ENGINE(EventHandler)->addTouchedPoint(std::atoi(words.at(1).c_str()), x, y);
            }
            else if (words.at(0) == "touch" && words.at(2) == "delete")    // タッチ点が削除された場合
            {
                TLL_ENGINE(EventHandler)->removeTouchedPoint(std::atoi(words.at(1).c_str()));
            }
            /******************
             * タッチ領域処理 *
             ******************/
            else if (words.at(0) == "blob" && words.at(2) == "bbox1")    // タッチ領域が追加・更新された場合
            {
                int32_t x = (arg++)->AsInt32();
                int32_t y = (arg++)->AsInt32();
                int32_t w = (arg++)->AsInt32();
                int32_t h = (arg++)->AsInt32();

                TLL_ENGINE(EventHandler)->addTouchedBlob(std::atoi(words.at(1).c_str()), x, y, w, h);
            }
            else if (words.at(0) == "blob" && words.at(2) == "delete")    // タッチ領域が削除された場合
            {
                TLL_ENGINE(EventHandler)->removeTouchedBlob(std::atoi(words.at(1).c_str()));
            }
        }
        catch (osc::Exception& e)
        {
            std::cout << "OSC error" << std::endl;
        }
    }

    std::vector<std::string> OscReceiver::split(const std::string msg)
    {
        std::vector<std::string> words;
        size_t start;
        size_t end = 0;

        // スラッシュごとに分割
        while ((start = msg.find_first_not_of('/', end)) != std::string::npos)
        {
            end = msg.find('/', start);
            words.push_back(msg.substr(start, end - start));
        }

        return words;
    }

    void threadListen()
    {
        OscReceiver receiver;
        UdpListeningReceiveSocket sock(IpEndpointName(IpEndpointName::ANY_ADDRESS, 9000), &receiver);

        sock.Run();
    }

}
