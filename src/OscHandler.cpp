#include "OscHandler.hpp"
#include "BaseApp.hpp"

namespace tll
{

    void OscHandler::ProcessMessage(const osc::ReceivedMessage& msg, const IpEndpointName& remote_end_pt)
    {
        if (!this->app_ref)
            return;

        (void)remote_end_pt;

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

    void OscHandler::sendMessage(const char* address)
    {
        UdpTransmitSocket transmitSocket(IpEndpointName("127.0.0.1", 7000));

        char buff[2048];
        osc::OutboundPacketStream p(buff, 2048);

        p << osc::BeginBundleImmediate << osc::BeginMessage(address) << osc::EndMessage << osc::EndBundle;
        transmitSocket.Send(p.Data(), p.Size());
    }

    void OscHandler::sendMessageWithFloat(const char* address, float value)
    {
        UdpTransmitSocket transmitSocket(IpEndpointName("127.0.0.1", 7000));

        char buff[2048];
        osc::OutboundPacketStream p(buff, 2048);

        p << osc::BeginBundleImmediate << osc::BeginMessage(address) << value << osc::EndMessage << osc::EndBundle;
        transmitSocket.Send(p.Data(), p.Size());
    }

    void runOscReceiveThread(class BaseApp* base_app)
    {
        OscHandler osc_handler(base_app);
        UdpListeningReceiveSocket osc_sock(IpEndpointName(IpEndpointName::ANY_ADDRESS, 44101), &osc_handler);
        osc_sock.Run();
    }

}
