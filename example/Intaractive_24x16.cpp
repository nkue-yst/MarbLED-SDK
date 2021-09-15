/**
 * @file    Intaractive_24x16.cpp
 * @brief   Draw rectangle when mouse clocked.
 * @author  Yoshito Nakaue
 * @date    2021/09/22
 */

#include "TLL.h"

using namespace tll;

int main()
{
    init(24, 16);
    Simulation::start();

    // Add touching event by lambda
    auto touched_event = []()
    {
        drawRect(Event::getTouchedX(), Event::getTouchedY(), 3, 3, Palette::color("Red"));
    };
    Event::addFunction(Event::TouchDown, touched_event);

    auto reset = []()
    {
        clear();
    };
    Event::addFunction(Event::TouchUp, reset);

    while (loop())
    {
    }

    Simulation::quit();
    quit();
}