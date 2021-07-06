#include "../../Adafruit_ADS1X15_RasPi/Adafruit_ADS1X15.h"
#include <wiringPi.h>
#include <iostream>
#include <unistd.h>

constexpr int s0 = 29;
constexpr int s1 = 31;
constexpr int s2 = 36;
constexpr int s3 = 37;

void initialize()
{
    wiringPiSetup();
    pinMode(s0, OUTPUT);
    pinMode(s1, OUTPUT);
    pinMode(s2, OUTPUT);
    pinMode(s3, OUTPUT);

    digitalWrite(s0, LOW);
    digitalWrite(s1, LOW);
    digitalWrite(s2, LOW);
    digitalWrite(s3, LOW);
}

int main()
{
    initialize();
    Adafruit_ADS1115 adc;
    adc.begin(0x48);

    while (true)
    {
        std::cout << adc.readADC_SingleEnded(0) << std::endl;
        usleep(1000);
    }
}
