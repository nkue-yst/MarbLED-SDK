#pragma once

#include "ip/IpEndpointName.h"
#include "ip/UdpSocket.h"

#include "osc/OscReceivedElements.h"
#include "osc/OscPacketListener.h"
#include "osc/OscOutboundPacketStream.h"

#include <iostream>

namespace tll
{

    /**
     * @brief OSCメッセージ受信クラス
     */
    class OscHandler : public osc::OscPacketListener
    {
    public:
        OscHandler() {}
        OscHandler(class BaseApp* base_app) :app_ref(base_app) {}
        ~OscHandler() {}

        static void sendMessage(const char* address, const char* dst_ip = "127.0.0.1", int port = 7000);
        static void sendMessageWithFloat(const char* address, float value, const char* dst_ip = "127.0.0.1", int port = 7000);

    protected:
        virtual void ProcessMessage(const osc::ReceivedMessage& msg, const IpEndpointName& remote_end_pt) override;

        class BaseApp* app_ref;
    };

    // OSCメッセージ受信スレッドの起動
    void runOscReceiveThread(class BaseApp* base_app);

}