#include "../thirdparty/serial/include/serial/serial.h"
#include <iostream>

int main()
{
    serial::Serial device("/dev/ttyUSB0", 115200, serial::Timeout::simpleTimeout(1000));

    if (device.isOpen())
        std::cout << "Success" << std::endl;
    else
        std::cout << "Failed" << std::endl;
}
