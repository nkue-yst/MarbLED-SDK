/**
 * @file    int2022_demo_1.cpp
 * @brief   ---
 * @author  Yoshito Nakaue
 * @date    2022/02/22
 */

#include <iostream>
#include <unistd.h>
#include <thread>
#include <vector>

#include "TLL.h"

using namespace tll;

int main()
{
    init(64, 32, "HUB75", false);
    Simulation::start(NONE);

    Video video = loadVideo("./example/video/bomb.mp4");
    video.play(0, 0, 22);
    std::this_thread::sleep_for(std::chrono::milliseconds(20));

    video = loadVideo("./example/video/bomb.mp4");
    video.play(0, 0, 24);
    std::this_thread::sleep_for(std::chrono::milliseconds(20));

    video = loadVideo("./example/video/bomb.mp4");
    video.play(0, 0, 18);
    std::this_thread::sleep_for(std::chrono::milliseconds(20));

    while (loop())
    {
        break;
    }

    Simulation::quit();
    quit();
}
