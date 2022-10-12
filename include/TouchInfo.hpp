#ifndef __TOUCH_INFO_HPP__
#define __TOUCH_INFO_HPP__

#include <cstdint>

namespace tll
{

    struct TouchInfo
    {
    public:
        uint32_t id;
        int32_t x;
        int32_t y;

        bool operator==(const TouchInfo& rhs) const
        {
            return this->id == rhs.id;
        }
    };

}

#endif
