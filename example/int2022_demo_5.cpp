/**
 * @file    int2022_demo_1.cpp
 * @brief   ---
 * @author  Yoshito Nakaue
 * @date    2022/02/22
 */

#include <iostream>
#include <unistd.h>
#include <thread>
#include <vector>

#include "TLL.h"
#include <TuioListener.h>
#include <UdpReceiver.h>
#include <TuioClient.h>

using namespace tll;
using namespace TUIO;

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

    void addTuioObject(TuioObject *tobj) override {}
    void updateTuioObject(TuioObject *tobj) override {}
    void removeTuioObject(TuioObject *tobj) override {}

    void addTuioCursor(TuioCursor *tcur) override {}
    void updateTuioCursor(TuioCursor *tcur) override {}
    void removeTuioCursor(TuioCursor *tcur) override {}
    
    void addTuioBlob(TuioBlob *tblb) override {}
    void updateTuioBlob(TuioBlob *tblb) override {}
    void removeTuioBlob(TuioBlob *tblb) override {}

    void refresh(TuioTime ftime) override {}

    virtual void run()
    {
        init(64, 32, "HUB75", false);
        Simulation::start(ALL);
        
        std::string time_pre("");
        std::string time_now("");

        while (loop())
        {
            time_pre = time_now;
            time_now = tll::timeToString();

            if (time_pre != time_now)
            {
                tll::clear();
                tll::print(time_now, tll::Palette::color("White"));
            }
        }

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
