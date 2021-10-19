/**
 * @file    Video_24x16.cpp
 * @brief   Playing video from file
 * @author  Yoshito Nakaue
 * @date    2021/10/19
 */

#include "TLL.h"

int main()
{
    tll::init(24, 16);
    tll::Simulation::start();

    tll::Video video = tll::loadVideo("./example/video/SampleMovie.mp4");
    video.play(1, 2, 30);

    while (tll::loop())
    {
    }

    tll::Simulation::quit();
    tll::quit();
}