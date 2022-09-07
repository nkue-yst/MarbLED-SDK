/**
 * @file    Color.cpp
 * @brief   Color information class
 * @author  Yoshito Nakaue
 * @date    2022/08/18
 */

#include "Color.hpp"

#include <iostream>
#include <cmath>

namespace tll
{

    inline uint32_t Color::calcDiff(Color c1, Color c2) noexcept
    {
        uint16_t r1 = c1.r_;
        uint16_t g1 = c1.g_;
        uint16_t b1 = c1.b_;

        uint16_t r2 = c2.r_;
        uint16_t g2 = c2.g_;
        uint16_t b2 = c2.b_;

        uint32_t dr, dg, db;
        dr = r2 - r1;
        dg = g2 - g1;
        db = b2 - b1;

        return static_cast<uint32_t>(std::sqrt(dr * dr + dg * dg + db * db));
    }

}
