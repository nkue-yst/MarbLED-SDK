/**
 * @file    Color.hpp
 * @brief   Color information class
 * @author  Yoshito Nakaue
 * @date    2022/08/22
 */

#ifndef COLOR_HPP
#define COLOR_HPP

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace tll
{

    /**
     * @brief  Color information
     */
    struct Color
    {
    public:
        constexpr Color(uint16_t r, uint16_t g, uint16_t b) noexcept
            : r_(r)
            , g_(g)
            , b_(b)
        {}

        constexpr Color() noexcept
            : r_(0)
            , g_(0)
            , b_(0)
        {}

        uint16_t r_;
        uint16_t g_;
        uint16_t b_;
    };


    /**
     * @brief 名前付きの色を定義
     * 
     */
    namespace Palette
    {
        constexpr tll::Color Aqua  {   0, 255, 255 };
        constexpr tll::Color Red   { 255,   0,   0 };
        constexpr tll::Color White { 255, 255, 255 };
    }

}

#endif
