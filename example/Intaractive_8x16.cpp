/**
 * @file    Intaractive_8x16.cpp
 * @brief   Draw rectangle when mouse clicked.
 * @author  Yoshito Nakaue
 * @date    2021/08/29
 */

#include "TLL.h"
#include <SDL.h>
#include <iostream>

using namespace tll;

int main()
{
    init(8, 16);
    Simulation::start();

    // Add touching event.
    auto touched_event = []()
        {
            std::cout << "Run touched event." << std::endl;
        };
    Event::addFunction(Event::TouchDown, touched_event);

    // Add releasing event.
    auto released_event = []()
        {
            std::cout << "Run released event." << std::endl;
        };
    Event::addFunction(Event::TouchUp, released_event);

    while (loop())
    {
    }

    Simulation::quit();
    quit();
}
