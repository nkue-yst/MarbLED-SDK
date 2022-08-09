/********************************************
 ** This file is generated by AppGenerator **
 ********************************************/

#pragma once

#include "AppInterface.hpp"

#include <cstdint>
#include <memory>

class OscTestApp : public tll::AppInterface
{
public:
    OscTestApp();
    ~OscTestApp();

    void init() override;
    void run() override;
    void terminate() override;

    void onTouched(uint32_t x, uint32_t y) override;
    void onMoved(uint32_t x, uint32_t y) override;
    void onReleased() override;

    void procOscMessage(const osc::ReceivedMessage& msg) override;
};

/* Required to use in loading application file */
extern "C"
{
    std::unique_ptr<tll::AppInterface> create()
    {
        return std::unique_ptr<tll::AppInterface>(new OscTestApp);
    }
}
