#pragma once
#include <cstdint>
#include "osc/OscReceivedElements.h"

#define emptyFuncError __FILE__ << "#" << __LINE__ << " " << __PRETTY_FUNCTION__ << "  --> 実装されていない関数です."

class AppBase
{
public:
    AppBase() {}
    virtual ~AppBase() {};

    /* Common */
    template<class App>
    static App* load() { return new App(); }

    virtual void init() = 0;
    virtual void run() = 0;
    virtual void terminate() = 0;

    virtual void procMessage(const osc::ReceivedMessage& msg) = 0;

    /* Touch event */
    virtual void onTouched(uint32_t x, uint32_t y) = 0;
    virtual void onMoved(uint32_t x, uint32_t y) = 0;
    virtual void onReleased() = 0;

protected:
    bool is_running = false;    // run()の終了判定
};
