#include "../../Adafruit_ADS1X15_RasPi/Adafruit_ADS1X15.h"
#include <iostream>
#include <unistd.h>

int main()
{
    Adafruit_ADS1115 ads1115;
    uint16_t adc0;

    ads1115.begin(0x48);
    while (true)
    {
        adc0 = ads1115.readADC_SingleEnded(0);
        std::cout << adc0 << std::endl;
        usleep(1000);
    }
}
