/**
 * @file    Event.hpp
 * @brief   Event handling
 * @author  Yoshito Nakaue
 * @date    2021/08/28
 */

#ifndef __EVENT_HPP__
#define __EVENT_HPP__

#include "TLL.h"

#include <cstdint>
#include <functional>
#include <vector>
#include <thread>
#include <mutex>

#include "tllEngine.hpp"

#include "TuioServer.h"
#include "UdpSender.h"

#include "osc/OscReceivedElements.h"
#include "osc/OscPacketListener.h"
#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"
#include "ip/IpEndpointName.h"

namespace tll
{

    /**
     * @brief  Event handling class
     */
    class IEventHandler
    {
    public:
        virtual ~IEventHandler() = default;

        // イベントハンドラを作成
        static IEventHandler* create();

        // イベントハンドラを初期化
        virtual void init() = 0;

        // タッチ状態を最新情報に更新する
        virtual void updateState() = 0;

        // 終了フラグの状態を取得
        bool getQuitFlag() { return quit_flag_; }

        // 終了フラグを更新｀
        void setQuitFlag(bool new_flag) { quit_flag_ = new_flag; }

        /// OscSender
        TUIO::OscSender* sender_;

        /// TuioServer
        TUIO::TuioServer* server_;

        /// Tuio object list
        std::vector<TUIO::TuioObject*> tobj_list_;

    private:
        /// Quit flag
        bool quit_flag_ = false;

        /// Previous state of mouse right button (for test)
        bool is_down_right_button = false;

        /// Previous state of mouse left button (for test)
        bool is_down_left_button = false;
    };

    class EventHandler : public IEventHandler
    {
    public:
        EventHandler();
        ~EventHandler() override;

        // イベントハンドラを初期化
        void init() override;

        // タッチ状態を最新情報に更新する
        void updateState() override;
    };
    
    class OscReceiver : public osc::OscPacketListener
    {
    public:
        OscReceiver() {}
        ~OscReceiver() {}

    protected:
        virtual void ProcessMessage(const osc::ReceivedMessage& msg, const IpEndpointName& remote_end_pt) override;

        std::mutex osc_mutex_;
    };

    void threadListen();
}

#endif
