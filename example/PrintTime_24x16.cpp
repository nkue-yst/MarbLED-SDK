/**
 * @file    PrintTime_24x16.cpp
 * @brief   Print current time example
 * @author  Yoshito Nakaue
 * @date    2021/11/1
 */

#include "TLL.h"

int main()
{
    tll::init(24, 16);
    tll::Simulation::start();

    std::string time_pre("");
    std::string time_now("");

    while (tll::loop())
    {
        time_pre = time_now;
        time_now = tll::timeToString();
        
        if (time_pre != time_now)
        {
            tll::clear();
            tll::print(time_now, tll::Palette::color("Red"));
        }
    }

    tll::Simulation::quit();
    tll::quit();
}
