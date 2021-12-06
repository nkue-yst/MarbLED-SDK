/**
 * @file    Image_192x192.cpp
 * @brief   Drawing image from file
 * @author  Yoshito Nakaue
 * @date    2021/12/06
 */

#include "TLL.h"

int main(int argc, char** argv)
{
    tll::init(192, 192);
    tll::Simulation::start();

    tll::Image img = tll::loadImage(argv[1]);
    img.resize(192, 192);
    img.draw(0, 0);

    while (tll::loop())
    {
    }

    tll::Simulation::quit();
    tll::quit();
}