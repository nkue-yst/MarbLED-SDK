/**
 * @file OscHandler.hpp
 * @author Y.Nakaue
 */

#ifndef __OSC_HANDLER_HPP__
#define __OSC_HANDLER_HPP__

#include <iostream>

#include "ip/IpEndpointName.h"
#include "ip/UdpSocket.h"

#include "osc/OscReceivedElements.h"
#include "osc/OscPacketListener.h"
#include "osc/OscOutboundPacketStream.h"

namespace tll
{

    /* OSCメッセージ受信クラス */
    class OscHandler : public osc::OscPacketListener
    {
    public:
        OscHandler() noexcept {}
        OscHandler(class BaseApp* base_app) noexcept :app_ref(base_app) {}
        ~OscHandler() noexcept {}

        // OSCメッセージを送信する
        static void sendMessage(const char* address, const char* dst_ip = "127.0.0.1", int port = 7000);

        // int型の引数付きでOSCメッセージを送信する
        static void sendMessageWithInt32(const char* address, int32_t value, const char* dst_ip = "127.0.0.1", int port = 7000);

        // float型の引数付きでOSCメッセージを送信する
        static void sendMessageWithFloat(const char* address, float value, const char* dst_ip = "127.0.0.1", int port = 7000);

        // string型の引数付きでOSCメッセージを送信する
        static void sendMessageWithString(const char* address, std::string value, const char* dst_ip = "127.0.0.1", int port = 7000);

    protected:
        // 受信したOSCメッセージを解析する
        virtual void ProcessMessage(const osc::ReceivedMessage& msg, const IpEndpointName& remote_end_pt) override;

        class BaseApp* app_ref;
    };

    // OSCメッセージ受信スレッドの起動
    void runOscReceiveThread(class BaseApp* base_app);
}

#endif
