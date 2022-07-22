#pragma once
#include "ip/IpEndpointName.h"
#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"

#define OSC_IP_ADDR "127.0.0.1"
#define OSC_PORT 7000
#define BUFF_SIZE (1024 * 10)

void sendOscMessage(const char* address);
