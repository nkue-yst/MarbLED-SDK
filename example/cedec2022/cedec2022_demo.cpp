/**
 * @file    cedec2022_demo.cpp
 * @brief   ---
 * @author  Yoshito Nakaue
 * @date    2022/07/20
 */

#include "cedec2022_demo.hpp"
#include "send_osc.h"

#include "MusicVisualizer.gen.hpp"
#include "VoiceRecognition.gen.hpp"
#include "Rain.gen.hpp"

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

    this->running_app = Rain::load();
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

void CedecDemo::switchApp(const char* app_name)
{
    this->running_app->terminate();
    delete this->running_app;

    if (strcmp(app_name, "music_visualizer") == 0)
    {
        this->running_app = MusicVisualizer::load();
        this->running_app->init();
    }
    else if (strcmp(app_name, "voice") == 0)
    {
        this->running_app = VoiceRecognition::load();
        this->running_app->init();
    }
    else if (strcmp(app_name, "rain") == 0)
    {
        this->running_app = Rain::load();
        this->running_app->init();
    }
    else
    {
        std::cout << "[ERROR]: Invalid app name" << std::endl;
    }
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
