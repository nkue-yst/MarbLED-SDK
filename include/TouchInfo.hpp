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

    struct BlobInfo
    {
    public:
        uint32_t id;
        int32_t x;
        int32_t y;
        int32_t w;
        int32_t h;

        bool operator=(const BlobInfo& rhs) const
        {
            return this->id == rhs.id;
        }
    };

}

#endif
