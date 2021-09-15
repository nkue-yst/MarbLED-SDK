/**
 * @file    Image_24x16.cpp
 * @brief   Drawing image from file
 * @author  Yoshito Nakaue
 * @date    2021/09/28
 */

#include "TLL.h"

int main()
{
    tll::init(24, 16);
    tll::Simulation::start();

    tll::Image img = tll::loadImage("./example/image/img_9.png");
    img.resize(16, 16);
    img.draw(0, 0);

    while (tll::loop())
    {
    }

    tll::Simulation::quit();
    tll::quit();
}