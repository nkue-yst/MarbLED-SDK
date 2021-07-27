/**
 * @file    example01.cpp
 * @brief   サンプルプログラム-01
 * @author  Yoshito Nakaue
 * @date    2021/07/27
 */

#include "TLL.h"
#include <iostream>

int main()
{
    tll::init(8, 16);
    tll::Simulation::start();

    tll::drawRect(2, 3, 4, 5, 1);
    tll::Simulation::update();

    std::cin.get();

    tll::Simulation::quit();
    tll::quit();
}
