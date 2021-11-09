/**
 * @file    PrintText_24x16.cpp
 * @brief   Print text example
 * @author  Yoshito Nakaue
 * @date    2021/10/18
 */

#include "TLL.h"

int main()
{
    tll::init(24, 16);
    tll::Simulation::start();

    tll::print("あかさたな", tll::Palette::color("Red"));

    while (tll::loop())
    {
    }

    tll::Simulation::quit();
    tll::quit();
}
