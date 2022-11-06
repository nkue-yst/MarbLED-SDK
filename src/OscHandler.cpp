/**
 * @file OscHandler.cpp
 * @author Y.Nakaue
 */

#include "OscHandler.hpp"

#include "BaseApp.hpp"

namespace tll
{

    void OscHandler::sendMessage(const char* address, const char* dst_ip, int port)
    {
        UdpTransmitSocket transmitSocket(IpEndpointName(dst_ip, port));

        char buff[2048];
        osc::OutboundPacketStream p(buff, 2048);

        p << osc::BeginBundleImmediate << osc::BeginMessage(address) << osc::EndMessage << osc::EndBundle;
        transmitSocket.Send(p.Data(), p.Size());
    }

    void OscHandler::sendMessageWithInt32(const char* address, int32_t value, const char* dst_ip, int port)
    {
        UdpTransmitSocket transmitSocket(IpEndpointName(dst_ip, port));

        char buff[2048];
        osc::OutboundPacketStream p(buff, 2048);

        p << osc::BeginBundleImmediate << osc::BeginMessage(address) << value << osc::EndMessage << osc::EndBundle;
        transmitSocket.Send(p.Data(), p.Size());
    }

    void OscHandler::sendMessageWithFloat(const char* address, float value, const char* dst_ip, int port)
    {
        UdpTransmitSocket transmitSocket(IpEndpointName(dst_ip, port));

        char buff[2048];
        osc::OutboundPacketStream p(buff, 2048);

        p << osc::BeginBundleImmediate << osc::BeginMessage(address) << value << osc::EndMessage << osc::EndBundle;
        transmitSocket.Send(p.Data(), p.Size());
    }

    void OscHandler::sendMessageWithString(const char* address, std::string value, const char* dst_ip, int port)
    {
        UdpTransmitSocket transmitSocket(IpEndpointName(dst_ip, port));

        char buff[2048];
        osc::OutboundPacketStream p(buff, 2048);

        p << osc::BeginBundleImmediate << osc::BeginMessage(address) << value.c_str() << osc::EndMessage << osc::EndBundle;
        transmitSocket.Send(p.Data(), p.Size());
    }
    
    void OscHandler::ProcessMessage(const osc::ReceivedMessage& msg, const IpEndpointName& remote_end_pt)
    {
        if (!this->app_ref)
            return;

        try
        {
            if (strcmp(msg.AddressPattern(), "/tll/switch") == 0)
            {
                this->app_ref->switchApp(msg.ArgumentsBegin()->AsString());
            }
            else
            {
                this->app_ref->getRunningApp()->procOscMessage(msg);
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << "[OSC ERROR]: " << e.what() << '\n';
        }
    }

    void runOscReceiveThread(class BaseApp* base_app)
    {
        OscHandler osc_handler(base_app);
        UdpListeningReceiveSocket osc_sock(IpEndpointName(IpEndpointName::ANY_ADDRESS, 44101), &osc_handler);
        osc_sock.Run();
    }

}
