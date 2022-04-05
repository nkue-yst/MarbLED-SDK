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
    int32_t app_id;

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

        case 3:
            system("./example/int2022_demo_3");
            break;

        case 4:
            system("./example/int2022_demo_4");
            break;

        case 5:
            system("./example/int2022_demo_5");
            break;

        case 6:
            system("./example/int2022_demo_6");
            break;

        case 7:
            system("./example/int2022_demo_7");
            break;
        
        default:
            std::cout << "Invalid app ID" << std::endl;
            break;
        }
    }
}
