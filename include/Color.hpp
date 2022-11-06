/**
 * @file    Color.hpp
 * @brief   Color information class
 * @author  Yoshito Nakaue
 * @date    2022/08/22
 */

#ifndef __COLOR_HPP__
#define __COLOR_HPP__

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace tll
{

    /* 色関連を扱う構造体 */
    struct Color
    {
    public:
        constexpr Color(uint8_t r, uint8_t g, uint8_t b) noexcept
            : r_(r)
            , g_(g)
            , b_(b)
        {}

        constexpr Color() noexcept
            : r_(0)
            , g_(0)
            , b_(0)
        {}

        // 2色のユークリッド距離を計算する
        static uint32_t calcDiff(Color c1, Color c2) noexcept;

        uint8_t r_;
        uint8_t g_;
        uint8_t b_;
    };


    /* 名前付きの色を定義 */
    namespace Palette
    {
        constexpr tll::Color Aqua  {   0, 255, 255 };
        constexpr tll::Color Red   { 255,   0,   0 };
        constexpr tll::Color White { 255, 255, 255 };
    }

}

#endif
