#include <iostream>
#include <vector>
#include "../serial/include/serial/serial.h"

int main()
{
    std::vector<serial::PortInfo> devices_found = serial::list_ports();
    std::vector<serial::PortInfo>::iterator iter = devices_found.begin();
    
    while (iter != devices_found.end())
    {
        serial::PortInfo device = *iter++;
        std::cout << device.port << ", " << device.description << ", " << device.hardware_id << std::endl;
    }

    return 0;
}
