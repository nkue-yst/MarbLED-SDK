/**
 * @file    Intaractive_8x16.cpp
 * @brief   Draw rectangle when mouse clicked.
 * @author  Yoshito Nakaue
 * @date    2021/08/30
 */

#include "TLL.h"

using namespace tll;

// Just call clear function.
void reset()
{
    clear();
}

int main()
{
    init(8, 16);
    Simulation::start();

    while (loop())
    {
    }

    Simulation::quit();
    quit();
}
