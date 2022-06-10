/**
 * @file    int2022_demo_1.cpp
 * @brief   ---
 * @author  Yoshito Nakaue
 * @date    2022/02/22
 */

#include <iostream>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <vector>

#include "TLL.h"
#include <TuioListener.h>
#include <UdpReceiver.h>
#include <TuioClient.h>

using namespace tll;
using namespace TUIO;

#define BPM 100
#define DURATION 10

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
        this->x = tobj->getX();
        this->y = tobj->getY();
    }

    void updateTuioObject(TuioObject *tobj) override
    {
        this->x = tobj->getX();
        this->y = tobj->getY();    
    }

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

        std::chrono::system_clock::time_point current_time = std::chrono::system_clock::now();
        std::chrono::system_clock::time_point pre_time;
        double elapse;
        bool is_beated = false;

        while (loop())
        {
            current_time = std::chrono::system_clock::now();
            elapse = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - pre_time).count();

            if (60.0 / BPM * 1000 <= elapse)
            {
                pre_time = current_time;
                std::cout << "Beat: " << elapse << "ms" << std::endl;
                clear();
                drawCircle(this->x, this->y, 6, Palette::color("White"));
                drawCircle(this->x, this->y, 7, Palette::color("Aqua"));
                std::this_thread::sleep_for(std::chrono::milliseconds(DURATION));
                clear();
                drawCircle(this->x, this->y, 7, Palette::color("White"));
                drawCircle(this->x, this->y, 8, Palette::color("Aqua"));
                std::this_thread::sleep_for(std::chrono::milliseconds(DURATION));
                clear();
                drawCircle(this->x, this->y, 8, Palette::color("White"));
                drawCircle(this->x, this->y, 9, Palette::color("Aqua"));
                std::this_thread::sleep_for(std::chrono::milliseconds(DURATION));
                clear();
                drawCircle(this->x, this->y, 9, Palette::color("White"));
                drawCircle(this->x, this->y, 10, Palette::color("Aqua"));
                std::this_thread::sleep_for(std::chrono::milliseconds(DURATION));
                clear();
                drawCircle(this->x, this->y, 10, Palette::color("White"));
                drawCircle(this->x, this->y, 11, Palette::color("Aqua"));
                std::this_thread::sleep_for(std::chrono::milliseconds(DURATION));
                clear();
                drawCircle(this->x, this->y, 11, Palette::color("White"));
                drawCircle(this->x, this->y, 12, Palette::color("Aqua"));
                std::this_thread::sleep_for(std::chrono::milliseconds(DURATION));
                clear();
                drawCircle(this->x, this->y, 12, Palette::color("White"));
                drawCircle(this->x, this->y, 13, Palette::color("Aqua"));
                std::this_thread::sleep_for(std::chrono::milliseconds(DURATION));
                clear();
                drawCircle(this->x, this->y, 13, Palette::color("White"));
                drawCircle(this->x, this->y, 14, Palette::color("Aqua"));
                std::this_thread::sleep_for(std::chrono::milliseconds(DURATION));
                clear();
                drawCircle(this->x, this->y, 14, Palette::color("White"));
                drawCircle(this->x, this->y, 15, Palette::color("Aqua"));
                std::this_thread::sleep_for(std::chrono::milliseconds(DURATION));

                is_beated = true;
            }
            else if (is_beated)
            {
                clear();
                drawCircle(this->x, this->y, 14, Palette::color("White"));
                drawCircle(this->x, this->y, 15, Palette::color("Aqua"));
                std::this_thread::sleep_for(std::chrono::milliseconds(DURATION));
                clear();
                drawCircle(this->x, this->y, 13, Palette::color("White"));
                drawCircle(this->x, this->y, 14, Palette::color("Aqua"));
                std::this_thread::sleep_for(std::chrono::milliseconds(DURATION));
                clear();
                drawCircle(this->x, this->y, 12, Palette::color("White"));
                drawCircle(this->x, this->y, 13, Palette::color("Aqua"));
                std::this_thread::sleep_for(std::chrono::milliseconds(DURATION));
                clear();
                drawCircle(this->x, this->y, 11, Palette::color("White"));
                drawCircle(this->x, this->y, 12, Palette::color("Aqua"));
                std::this_thread::sleep_for(std::chrono::milliseconds(DURATION));
                clear();
                drawCircle(this->x, this->y, 10, Palette::color("White"));
                drawCircle(this->x, this->y, 11, Palette::color("Aqua"));
                std::this_thread::sleep_for(std::chrono::milliseconds(DURATION));
                clear();
                drawCircle(this->x, this->y, 9, Palette::color("White"));
                drawCircle(this->x, this->y, 10, Palette::color("Aqua"));
                std::this_thread::sleep_for(std::chrono::milliseconds(DURATION));
                clear();
                drawCircle(this->x, this->y, 8, Palette::color("White"));
                drawCircle(this->x, this->y, 9, Palette::color("Aqua"));
                std::this_thread::sleep_for(std::chrono::milliseconds(DURATION));
                clear();
                drawCircle(this->x, this->y, 7, Palette::color("White"));
                drawCircle(this->x, this->y, 8, Palette::color("Aqua"));
                std::this_thread::sleep_for(std::chrono::milliseconds(DURATION));
                clear();
                drawCircle(this->x, this->y, 6, Palette::color("White"));
                drawCircle(this->x, this->y, 7, Palette::color("Aqua"));
                std::this_thread::sleep_for(std::chrono::milliseconds(DURATION));

                is_beated = false;           
            }
        }

        Simulation::quit();
        quit();
    }

private:
    uint32_t x = 25;
    uint32_t y = 16;

    TuioClient* client;
    OscReceiver* receiver;
};

int main()
{
    App* app = new App();
    app->run();
    delete app;
}
