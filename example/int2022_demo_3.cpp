/**
 * @file    int2022_demo_3.cpp
 * @brief   ---
 * @author  Yoshito Nakaue
 * @date    2022/02/23
 */

#include <iostream>
#include <unistd.h>
#include <thread>

#include "TLL.h"
#include <TuioListener.h>
#include <UdpReceiver.h>
#include <TuioClient.h>

using namespace tll;
using namespace TUIO;

uint32_t pos[3] = {5, 16, 27};

enum class EStone : uint8_t
{
    NONE,
    MARU,
    BATSU,
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
        this->put(tobj->getX(), tobj->getY());
    }

    void updateTuioObject(TuioObject *tobj) override
    {
    }

    void removeTuioObject(TuioObject *tobj) override
    {
    }

    void addTuioCursor(TuioCursor *tcur) override {}
    void updateTuioCursor(TuioCursor *tcur) override {}
    void removeTuioCursor(TuioCursor *tcur) override {}
    
    void addTuioBlob(TuioBlob *tblb) override {}
    void updateTuioBlob(TuioBlob *tblb) override {}
    void removeTuioBlob(TuioBlob *tblb) override {}

    void refresh(TuioTime ftime) override {}

    virtual void run()
    {
        init(32, 32, "HUB75", false);
        Simulation::start(CHIP);

        drawBoard();

        while (loop())
        {
        }

        Simulation::quit();
        quit();
    }

private:
    bool checkGameOver()
    {
        EStone cp = this->current_player;

        return ((stones[0][0] == cp && stones[1][0] == cp && stones[2][0] == cp) ||
                (stones[0][1] == cp && stones[1][1] == cp && stones[2][1] == cp) ||
                (stones[0][2] == cp && stones[1][2] == cp && stones[2][2] == cp) ||
                (stones[0][0] == cp && stones[0][1] == cp && stones[0][2] == cp) ||
                (stones[1][0] == cp && stones[1][1] == cp && stones[1][2] == cp) ||
                (stones[2][0] == cp && stones[2][1] == cp && stones[2][2] == cp) ||
                (stones[0][0] == cp && stones[1][1] == cp && stones[2][2] == cp) ||
                (stones[0][2] == cp && stones[1][1] == cp && stones[2][0] == cp));
    }

    void drawBoard()
    {
        drawLine(10,  0, 10, 31, Palette::color("White"));
        drawLine(21,  0, 21, 31, Palette::color("White"));
        drawLine( 0, 10, 31, 10, Palette::color("White"));
        drawLine( 0, 21, 31, 21, Palette::color("White"));

        for (uint32_t y = 0; y < 3; y++)
        {
            for (uint32_t x = 0; x < 3; x++)
            {
                if (this->stones[x][y] == EStone::MARU)
                {
                    drawCircle(pos[x], pos[y], 3, Palette::color("Yellow"));
                }
                else if (this->stones[x][y] == EStone::BATSU)
                {
                    drawLine(pos[x] - 3, pos[y] - 3, pos[x] + 3, pos[y] + 3, Palette::color("Aqua"));
                    drawLine(pos[x] - 3, pos[y] + 3, pos[x] + 3, pos[y] - 3, Palette::color("Aqua"));
                }
            }
        }
    }

    void put(uint32_t x, uint32_t y)
    {
        uint8_t X;
        uint8_t Y;

        if (0 <= x && x <= 9)
            X = 0;
        else if (11 <= x && x <= 20)
            X = 1;
        else if (22 <= x && x <= 31)
            X = 2;
        else
            return;

        if (0 <= y && y <= 9)
            Y = 0;
        else if (11 <= y && y <= 20)
            Y = 1;
        else if (22 <= y && y <= 31)
            Y = 2;
        else
            return;

        if (this->stones[X][Y] != EStone::NONE)
            return;

        this->stones[X][Y] = current_player;
        this->drawBoard();

        if (this->checkGameOver())
        {
            std::cout << "Winner is " << ((this->current_player == EStone::MARU) ? "MARU" : "BATSU") << std::endl;
            return;
        }

        if (current_player == EStone::MARU)
            current_player = EStone::BATSU;
        else
            current_player = EStone::MARU;
    }

    EStone stones[3][3] = {
        {EStone::NONE, EStone::NONE, EStone::NONE},
        {EStone::NONE, EStone::NONE, EStone::NONE},
        {EStone::NONE, EStone::NONE, EStone::NONE}
    };

    EStone current_player = EStone::MARU;

    TuioClient* client;
    OscReceiver* receiver;
};

int main()
{
    App* app = new App();
    app->run();
    delete app;
}
