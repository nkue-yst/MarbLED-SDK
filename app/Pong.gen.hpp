/********************************************
 ** This file is generated by AppGenerator **
 ********************************************/

#pragma once

#include "AppInterface.hpp"
#include "TLL.h"

#include <cstdint>
#include <memory>

class Player
{
public:
    Player(tll::Color color, uint32_t x, uint32_t y)
        : x(x)
        , y(y)
        , color(color)
    {}

    uint32_t x, y;
    tll::Color color;
};

class Pong : public tll::AppInterface
{
public:
    Pong();
    ~Pong();

    void init() override;
    void run() override;
    void terminate() override;

    void onTouched(tll::TouchInfo ti) override;
    void onMoved(tll::TouchInfo ti) override;
    void onReleased(tll::TouchInfo ti) override;

private:
    void drawBoard();
    void drawPlayers();

    Player* p1;
    Player* p2;
};

/* Required to use in loading application file */
extern "C"
{
    std::unique_ptr<tll::AppInterface> create()
    {
        return std::unique_ptr<tll::AppInterface>(new Pong);
    }
}