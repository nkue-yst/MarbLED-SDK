#ifndef APP_RUNNER_HPP
#define APP_RUNNER_HPP

#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"

#include <string>

#define OUTPUT_BUFFER_SIZE 1024

class AppRunner
{
public:
    AppRunner(const char* address = "127.0.0.1", int32_t port = 44101) noexcept
    {
        this->address = address;
        this->port = port;
    }

    void runApp(const char* app_name)
    {
        UdpTransmitSocket transmitSocket(IpEndpointName(this->address.c_str(), this->port));

        char buffer[OUTPUT_BUFFER_SIZE];
        osc::OutboundPacketStream p(buffer, OUTPUT_BUFFER_SIZE);
        
        p << osc::BeginBundleImmediate
            << osc::BeginMessage("/tll/switch")
                << app_name
            << osc::EndMessage
        << osc::EndBundle;
        
        transmitSocket.Send(p.Data(), p.Size());
    }

private:
    std::string address;
    int32_t port;
};

#endif
