/**
 * @file    int2022_demo_4.cpp
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
        Simulation::start(NONE);

        img = loadImage("./example/image/Arrow2.png");
        img.resize(32, 32);
        img.draw(0, 0);

        img2 = loadImage("./example/image/img_9.png");
        img2.resize(32, 32);
        img2.draw(32, 0); 

        while (loop())
        {
        }

        Simulation::quit();
        quit();
    }

private:
    int i = 0;
    Image img;
    Image img2;

    TuioClient* client;
    OscReceiver* receiver;
};

int main()
{
    App* app = new App();
    app->run();
    delete app;
}
