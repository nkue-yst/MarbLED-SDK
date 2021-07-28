/**
 * @file    FillSingleColor_8x16.cpp
 * @brief   Fill panel with single color.
 * @author  Yoshito Nakaue
 * @date    2021/08/05
 */

#include "TLL.h"
#include <iostream>

int main()
{
    tll::init(8, 16);
    tll::Simulation::start();

    tll::drawRect(0, 0, 8, 16, tll::Palette::color("Blue"));

    tll::Simulation::update();

    std::cin.get();

    tll::Simulation::quit();
    tll::quit();
}
