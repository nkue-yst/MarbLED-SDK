/**
 * @file    cedec2022_demo.cpp
 * @brief   ---
 * @author  Yoshito Nakaue
 * @date    2022/07/20
 */

#include "cedec2022_demo.hpp"
#include "MusicVisualizer.gen.hpp"
#include "send_osc.h"

#include "ip/UdpSocket.h"
#include "ip/IpEndpointName.h"

#define demo_main main

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

    this->running_app = MusicVisualizer::load();
    this->running_app->init();

    while (loop())
    {
        this->running_app->run();
    }

    this->running_app->terminate();
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

int demo_main()
{
    CedecDemo* app = new CedecDemo();

    std::thread th_osc_recv(runOscReceivingThread, app);
    th_osc_recv.detach();

    app->run();
    delete app;
}
