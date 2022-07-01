#pragma once

#include <iostream>

inline void printLog(const char* action, bool success = true)
{
    std::cout << (success ? "[OK]: " : "[NG]: ");
    std::cout << action << std::endl;
}
