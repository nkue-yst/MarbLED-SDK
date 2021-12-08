/**
 * @file    Intaractive_24x16.cpp
 * @brief   ---
 * @author  Yoshito Nakaue
 * @date    2021/12/08
 */

#include <unistd.h>

#include "TLL.h"
#include <TuioListener.h>
#include <UdpReceiver.h>
#include <TuioClient.h>

using namespace tll;
using namespace TUIO2;

class App : public TuioListener
{
public:
    App()
    {
        this->receiver = new UdpReceiver();
        this->client   = new TuioClient(this->receiver);
        this->client->addTuioListener(this);
        this->client->connect();
    };

    void tuioAdd(TuioObject *tobj) override {}
    void tuioUpdate(TuioObject *tobj) override {}
    void tuioRemove(TuioObject *tobj) override {}
    void tuioRefresh(TuioTime ftime) override {}

    void run()
    {
        init(24, 16);
        Simulation::start();

        Simulation::quit();
        quit();
    }

private:
    TuioClient* client;
    OscReceiver* receiver;
};

int main()
{
    App* app = new App();

    app->run();

    delete app;
}