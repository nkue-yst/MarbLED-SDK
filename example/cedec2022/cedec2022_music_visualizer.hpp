#pragma once

#include "cedec2022_demo.hpp"
#include "send_osc.h"
#include "demo_app_base.hpp"

#include <iostream>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <vector>

#include "TLL.h"
#include <TuioListener.h>
#include <UdpReceiver.h>
#include <TuioClient.h>

#include "osc/OscReceivedElements.h"
#include "osc/OscPacketListener.h"
#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"
#include "ip/IpEndpointName.h"

using namespace tll;
using namespace TUIO;

class MusicVisualizer : public AppBase
{
public:
    MusicVisualizer() {}
    ~MusicVisualizer() {}

    void run() override;

    void beatNotified() override;
    void receiveValue() override;

private:
    std::chrono::system_clock::time_point pre_pre_tp;
    std::chrono::system_clock::time_point pre_tp;

    double pre_pre_elapse = 0.0;
    double pre_elapse     = 0.0;
};
