/**
 * @file    cedec2022_demo.cpp
 * @brief   ---
 * @author  Yoshito Nakaue
 * @date    2022/07/20
 */

#include "cedec2022_demo.hpp"
#include "cedec2022_music_visualizer.hpp"
#include "send_osc.h"

#include "ip/UdpSocket.h"
#include "ip/IpEndpointName.h"

CedecDemo::CedecDemo()
{
    this->receiver = new UdpReceiver();
    this->client   = new TuioClient(this->receiver);
    this->client->addTuioListener(this);
    this->client->connect();
}

CedecDemo::~CedecDemo()
{
    this->client->disconnect();
    delete this->client;
    delete this->receiver;
}

void CedecDemo::run()
{
    init(64, 32, "HUB75", false);
    sendOscMessage("/tll/init");

    this->running_app = new MusicVisualizer();

    while (loop())
    {
        this->running_app->run();
    }

    delete this->running_app;

    sendOscMessage("/tll/terminate");
    quit();
}

void runOscReceivingThread(CedecDemo* app)
{
    // Initialize socket for osc
    OscHandler osc_receiver(app);
    UdpListeningReceiveSocket osc_sock(IpEndpointName(IpEndpointName::ANY_ADDRESS, 44101), &osc_receiver);
    osc_sock.Run();
}

int main()
{
    CedecDemo* app = new CedecDemo();

    std::thread th_osc_recv(runOscReceivingThread, app);
    th_osc_recv.detach();

    app->run();
    delete app;
}
