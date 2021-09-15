/**
 * @file    MovingRect_24x16.cpp
 * @brief   Drawing moving rectangle.
 * @author  Yoshito Nakaue
 * @date    2021/09/22
 */

#include "TLL.h"
#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    tll::init(24, 16);
    tll::Simulation::start();

    int i = 0;
    while (i < 100)
    {
        tll::clear();

        tll::drawRect(i % 24, i % 16, 2, 2, tll::Palette::color("Red"));
        tll::Simulation::update();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        i++;
    }

    tll::Simulation::quit();
    tll::quit();
}
