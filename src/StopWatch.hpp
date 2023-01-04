#pragma once

#include <chrono>
#include <iostream>

namespace
{
    std::chrono::system_clock::time_point start;
    std::chrono::system_clock::time_point end;
    double elapse;
}

namespace tll
{
    class Clock
    {
    public:
        Clock(std::string processing)
            : processing_(processing)
        {
            this->start_ = std::chrono::system_clock::now();
        }

        ~Clock()
        {
            this->end_ = std::chrono::system_clock::now();
            double elapse = std::chrono::duration_cast<std::chrono::milliseconds>(this->end_ - this->start_).count();

            std::cout << this->processing_ << ": " << elapse << "ms" << std::endl;
        }

        static void startClock()
        {
            start = std::chrono::system_clock::now();
        }

        static void stopClock()
        {
            end = std::chrono::system_clock::now();
            elapse = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

            std::cout << elapse << "ms" << std::endl;
        }

    private:
        // Time point for clock
        std::chrono::system_clock::time_point start_, end_;

        // Processing name
        std::string processing_;
    };
}
