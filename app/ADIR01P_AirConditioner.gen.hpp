/********************************************
 ** This file is generated by AppGenerator **
 ********************************************/

#pragma once

#include "AppInterface.hpp"

#include <cstdint>
#include <memory>

class ADIR01P_AirConditioner : public tll::AppInterface
{
public:
    ADIR01P_AirConditioner();
    ~ADIR01P_AirConditioner();

    void init() override;
    void run() override;
    void terminate() override;

    void onTouched(tll::TouchInfo ti) override;
    void onMoved(tll::TouchInfo ti) override;
    void onReleased(tll::TouchInfo ti) override;

    float temperature_;

    bool power_on_;

    bool pressed_[3];
};

/* Required to use in loading application file */
extern "C"
{
    std::unique_ptr<tll::AppInterface> create()
    {
        return std::unique_ptr<tll::AppInterface>(new ADIR01P_AirConditioner);
    }
}
