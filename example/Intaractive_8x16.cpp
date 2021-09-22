/**
 * @file    Intaractive_8x16.cpp
 * @brief   Draw rectangle when mouse clicked.
 * @author  Yoshito Nakaue
 * @date    2021/08/30
 */

#include "TLL.h"

using namespace tll;

// Just call clear function.
void reset()
{
    clear();
}

int main()
{
    init(8, 16);
    Simulation::start();

    // Add touching event by lambda
    auto touched_event = []()
        {
            drawRect(Event::getTouchedX(), Event::getTouchedY(), 2, 2, Palette::color("Red"));
        };
    Event::addFunction(Event::TouchDown, touched_event);

    // Add releasing event by function pointer
    Event::addFunction(Event::TouchUp, *reset);

    while (loop())
    {
    }

    Simulation::quit();
    quit();
}