/**
 * @file    Rectangles_8x16.cpp
 * @brief   Drawing colorful rectangles. 
 * @author  Yoshito Nakaue
 * @date    2021/08/05
 */

#include "TLL.h"
#include <iostream>

int main()
{
    tll::init(8, 16);
    tll::Simulation::start();

    tll::drawRect(0, 0, 3, 4, tll::Palette::color("Blue"));
    tll::drawRect(2, 3, 3, 4, tll::Palette::color("DeepSkyBlue"));
    tll::drawRect(4, 6, 3, 4, tll::Palette::color("Aqua"));
    tll::drawRect(6, 9, 3, 4, tll::Palette::color("ForestGreen"));

    tll::Simulation::update();

    std::cin.get();

    tll::Simulation::quit();
    tll::quit();
}
