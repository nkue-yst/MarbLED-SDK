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
#include <random>
#include <vector>

#include "TLL.h"
#include <TuioListener.h>
#include <UdpReceiver.h>
#include <TuioClient.h>

using namespace tll;
using namespace TUIO;

#define FISH_NUM 3

class Fish
{
public:
    int x, y;
    bool left, up;
    int skip_move = 1;
    uint8_t color;

    Fish(int X, int Y, bool Left, bool Up, uint8_t Color)
        : x(X)
        , y(Y)
        , left(Left)
        , up(Up)
        , color(Color)
    {}

    void draw()
    {
        drawCircle(x, y, 1, color);

        if (left && up)
            drawLine(x, y, x + 2, y + 1, color);
        else if (!left && up)
            drawLine(x, y, x - 2, y + 1, color);
        else if (left && !up)
            drawLine(x, y, x + 2, y - 1, color);
        else
            drawLine(x, y, x - 2, y - 1, color);
    }

    void move()
    {
        if (skip_move != 0)
        {
            skip_move = (skip_move + 1) % 2;
            return;
        }
        skip_move++;

        // Move x
        if (left && x > 2)
        {
            x--;
        }
        else if (left && x == 2)
        {
            left = false;
        }
        else if (!left && x < 61)
        {
            x++;
        }
        else if (!left && x == 61)
        {
            left = true;
        }
        else
        {
            std::cout << "Error" << std::endl;
        }

        // Move y
        if (up && y > 2)
        {
            y--;
        }
        else if (up && y == 2)
        {
            up = false;
        }
        else if (!up && y < 30)
        {
            y++;
        }
        else if (!up && y == 30)
        {
            up = true;
        }
        else
        {
            std::cout << "Error" << std::endl;
        }
    }
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

    void addTuioObject(TuioObject *tobj) override{}
    void updateTuioObject(TuioObject *tobj) override {}
    void removeTuioObject(TuioObject *tobj) override {}

    void addTuioCursor(TuioCursor *tcur) override {}
    void updateTuioCursor(TuioCursor *tcur) override {}
    void removeTuioCursor(TuioCursor *tcur) override {}
    
    void addTuioBlob(TuioBlob *tblb) override {}
    void updateTuioBlob(TuioBlob *tblb) override {}
    void removeTuioBlob(TuioBlob *tblb) override {}

    void refresh(TuioTime ftime) override {}

    void drawAllFish()
    {
        for (int i = 0; i < FISH_NUM; i++)
        {
            this->fish[i]->draw();
        }
    }

    virtual void run()
    {
        init(64, 32, "HUB75", false);
        Simulation::start(MARBLE);

        fish[0] = new Fish(10, 5, false, false, Palette::color("White"));
        fish[1] = new Fish(50, 20, true, true, Palette::color("White"));
        fish[2] = new Fish(20, 12, false, true, Palette::color("Aqua"));

        std::random_device rnd1, rnd2, rnd3;
        int rand_value1_x = rnd1() % 10 + 50;
        int rand_value1_y = rnd1() % 20 + 50;
        int rand_value2_x = rnd2() % 20 + 50;
        int rand_value2_y = rnd2() % 40 + 50;
        int rand_value3_x = rnd3() % 30 + 50;
        int rand_value3_y = rnd3() % 60 + 50;
        long frame = 0;

        while (loop())
        {
            frame++;

            if (frame % rand_value1_x == 0)
            {
                fish[0]->left = !fish[0]->left;
                rand_value1_x = rnd1() % 10 + 50;
            }

            if (frame % rand_value1_y == 0)
            {
                fish[0]->up = !fish[0]->up;
                rand_value1_y = rnd1() % 20 + 50;
            }

            if (frame % rand_value2_x == 0)
            {
                fish[1]->left = !fish[1]->left;
                rand_value2_x = rnd2() % 20 + 50;
            }

            if (frame % rand_value2_y == 0)
            {
                fish[1]->up = !fish[1]->up;
                rand_value2_y = rnd2() % 40 + 50;
            }

            if (frame % rand_value3_x == 0)
            {
                fish[2]->left = !fish[2]->left;
                rand_value3_x = rnd3() % 30 + 50;
            }

            if (frame % rand_value3_y == 0)
            {
                fish[2]->up = !fish[2]->up;
                rand_value3_y = rnd3() % 60 + 50;
            }

            fish[0]->move();
            fish[1]->move();
            fish[2]->move();

            clear();
            drawAllFish();

            std::this_thread::sleep_for(std::chrono::milliseconds(30));
        }

        Simulation::quit();
        quit();
    }

    Fish* fish[FISH_NUM];

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
