#include "send_osc.h"

void sendOscMessage(const char* address)
{
    UdpTransmitSocket transmitSocket(IpEndpointName(OSC_IP_ADDR, OSC_PORT));
    
    char buff[BUFF_SIZE];
    osc::OutboundPacketStream p(buff, BUFF_SIZE);
    
    p << osc::BeginBundleImmediate << osc::BeginMessage(address) << osc::EndMessage << osc::EndBundle;
    transmitSocket.Send(p.Data(), p.Size());
}
