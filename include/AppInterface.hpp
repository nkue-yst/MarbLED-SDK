#pragma once

#include <cstdint>
#include <memory>

#include "OscHandler.hpp"
#include "TouchInfo.hpp"

#include "osc/OscReceivedElements.h"

namespace tll
{

    typedef std::unique_ptr<class AppInterface> createApp();

    /* アプリ実装用インターフェースクラス */
    class AppInterface
    {
    public:
        virtual ~AppInterface() = default;

        /* Common */
        virtual void init() = 0;
        virtual void run() = 0;
        virtual void terminate() = 0;

        /* Single touch event */
        virtual void onTouched(TouchInfo ti) = 0;
        virtual void onMoved(TouchInfo ti) = 0;
        virtual void onReleased(TouchInfo ti) = 0;

        /* OSC process */
        virtual void procOscMessage(const osc::ReceivedMessage& msg) {}
    };

}
