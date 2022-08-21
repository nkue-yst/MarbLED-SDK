/**
 * @file    int2022_demo_1.cpp
 * @brief   ---
 * @author  Yoshito Nakaue
 * @date    2022/08/22
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

struct Ripple
{
    int32_t x;
    int32_t y;
    int32_t r;
};

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

    void addTuioObject(TuioObject *tobj) override
    {
        if (this->ripples.size() >= 4)
        {
            this->ripples.erase(this->ripples.begin());
            this->ripples.erase(this->ripples.begin());
        }

        std::cout << "Test" << std::endl;

        struct Ripple r1 = {(int32_t)tobj->getX(), (int32_t)tobj->getY(), 1};
	    struct Ripple r2 = {(int32_t)tobj->getX(), (int32_t)tobj->getY(), 0};
        ripples.push_back(r1);
        ripples.push_back(r2);
    }

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

        while (loop())
        {
            this->updateRipples();
        }

        quit();
    }

private:
    void updateRipples()
    {
        clear();
        for (auto& ripple : this->ripples)
        {
            drawCircle(ripple.x, ripple.y, ripple.r, Palette::Aqua);
            ripple.r++;
            
            if (ripple.r >= 64)
                this->ripples.erase(this->ripples.begin());
        }
        std::this_thread::sleep_for(
            std::chrono::milliseconds(13)
        );
    }

    TuioClient* client;
    OscReceiver* receiver;

    std::vector<struct Ripple> ripples;
};

int main()
{
    App* app = new App();
    app->run();
    delete app;
}
