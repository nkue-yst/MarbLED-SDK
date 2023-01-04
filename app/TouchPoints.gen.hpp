/********************************************
 ** This file is generated by AppGenerator **
 ********************************************/

#pragma once

#include "AppInterface.hpp"

#include <cstdint>
#include <memory>
#include <vector>

class TouchPoints : public tll::AppInterface
{
public:
    TouchPoints();
    ~TouchPoints();

    void init() override;
    void run() override;
    void terminate() override;

    void onTouched(tll::TouchInfo ti) override;
    void onMoved(tll::TouchInfo ti) override;
    void onReleased(tll::TouchInfo ti) override;

private:
    tll::TouchInfo points[5];
};

/* Required to use in loading application file */
extern "C"
{
    std::unique_ptr<tll::AppInterface> create()
    {
        return std::unique_ptr<tll::AppInterface>(new TouchPoints);
    }
}
