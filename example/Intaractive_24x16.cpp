/**
 * @file    Intaractive_24x16.cpp
 * @brief   Draw rectangle when mouse clocked.
 * @author  Yoshito Nakaue
 * @date    2021/09/22
 */

#include "TLL.h"

using namespace tll;

int main()
{
    init(24, 16);
    Simulation::start();

    while (loop())
    {
    }

    Simulation::quit();
    quit();
}