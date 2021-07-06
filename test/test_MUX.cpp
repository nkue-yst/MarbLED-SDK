#include <wiringPi.h>
#include <iostream>

constexpr int s0 = 29;
constexpr int s1 = 31;
constexpr int s2 = 36;
constexpr int s3 = 37;

constexpr int INPUT_PIN = 16;

void initialize()
{
    wiringPiSetup();
    pinMode(s0, OUTPUT);
    pinMode(s1, OUTPUT);
    pinMode(s2, OUTPUT);
    pinMode(s3, OUTPUT);
    pinMode(INPUT_PIN, INPUT);

    digitalWrite(s0, LOW);
    digitalWrite(s1, LOW);
    digitalWrite(s2, LOW);
    digitalWrite(s3, LOW);
}

int main()
{
    initialize();

    while (true)
    {
        std::cout << analogRead(INPUT_PIN) << std::endl;
    }
}