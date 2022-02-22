/**
 * @file    Intaractive_24x16.cpp
 * @brief   ---
 * @author  Yoshito Nakaue
 * @date    2021/12/08
 */

#include <iostream>
#include <unistd.h>
#include <thread>

int main()
{
    bool loop = true;
    int32_t app_id = 1;

    while (loop)
    {
        std::cout << "App ID -> ";
        std::cin >> app_id;

        switch (app_id)
        {
        case 0:
            loop = false;
            break;

        case 1:
            system("./example/int2022_demo_1");
            break;

        case 2:
            system("./example/int2022_demo_2");
            break;
        
        default:
            std::cout << "Invalid app ID" << std::endl;
            break;
        }
    }
}
