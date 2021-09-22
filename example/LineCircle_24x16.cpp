/**
 * @file    LineCircle_24x16.cpp
 * @brief   Drawing line and circle. 
 * @author  Yoshito Nakaue
 * @date    2021/10/05
 */

#include "TLL.h"
#include <iostream>

int main()
{
    tll::init(24, 16);
    tll::Simulation::start();

    tll::drawLine( 1,  2,  1, 10, tll::Palette::color("Red"));
    tll::drawLine(10,  7,  3,  1, tll::Palette::color("Orange"));
    tll::drawLine( 3, 14, 10,  8, tll::Palette::color("Yellow"));

    tll::drawCircle(16, 7, 4, tll::Palette::color("Blue"));

    while (tll::loop())
    {
    }

    tll::Simulation::quit();
    tll::quit();
}
