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
