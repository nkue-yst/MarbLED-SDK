#pragma once

#include <iostream>

inline void printLog(const char* action, bool success = true)
{
    std::cout << (success ? "[\033[1;32mOK\033[m]: " : "[\033[1;31mNG\033[m]: ");
    std::cout << action << std::endl;
}
