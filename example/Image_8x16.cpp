/**
 * @file    Image_8x16.cpp
 * @brief   Test draw from image file.
 * @author  Yoshito Nakaue
 * @date    2021/09/08
 */

#include "TLL.h"

int main()
{
    tll::init(8, 16);
    tll::Simulation::start();

    tll::Image img = tll::loadImage("./image/img_9.png");

    while (tll::loop())
    {
    }

    tll::Simulation::quit();
    tll::quit();
}
