#pragma once

#include <cstdint>
#include <memory>

#include "osc/OscReceivedElements.h"

namespace tll
{
    typedef std::unique_ptr<class AppInterface> createAppFunc();

    /* アプリ実装用インターフェースクラス */
    class AppInterface
    {
    public:
        virtual ~AppInterface() = default;

        /* Common */
        virtual void init() = 0;
        virtual void run() = 0;
        virtual void terminate() = 0;

        /* Touch event */
        virtual void onTouched(uint32_t x, uint32_t y) = 0;
        virtual void onMoved(uint32_t x, uint32_t y) = 0;
        virtual void onReleased() = 0;

    protected:
        bool is_running = false;
    };

}
