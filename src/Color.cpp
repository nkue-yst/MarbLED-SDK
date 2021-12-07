/**
 * @file    Color.cpp
 * @brief   Color information class
 * @author  Yoshito Nakaue
 * @date    2021/09/28
 */

#include "Color.hpp"
#include <iostream>
#include <cmath>

namespace tll
{

    ColorPalette* ColorPalette::pInstance_ = nullptr;

    void ColorPalette::create()
    {
        if (!pInstance_)
        {
            pInstance_ = new ColorPalette();
        }
    }

    void ColorPalette::destroy()
    {
        delete pInstance_;
        pInstance_ = nullptr;
    }

    void ColorPalette::addColor(Color color)
    {
        palette_data_.push_back(color);
/*
        std::cout << color.color_name_ << std::endl;
        std::cout << "  "   << "R:"   << color.r_
                            << ", G:" << color.g_
                            << ", B:" << color.b_ << std::endl;
*/ 
    }

    uint8_t ColorPalette::getIDFromName(std::string color_name)
    {
        for (uint8_t i = 0; i < palette_data_.size(); i++)
        {
            if (!color_name.compare(palette_data_[i].color_name_))
            {
                return i;
            }
        }

        return 0;
    }

    Color ColorPalette::getColorFromID(uint8_t color_id)
    {
        return palette_data_.at(color_id);
    }

    inline uint32_t calcDiff(Color c1, Color c2)
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

    uint8_t ColorPalette::getIDFromRGB(uint16_t r, uint16_t g, uint16_t b)
    {
        Color base_color = Color(r, g, b);
        uint8_t target_ID = 0;

        uint32_t min_diff;
        min_diff = calcDiff(base_color, palette_data_[0]);

        for (std::size_t i = 1; i < palette_data_.size(); i++)
        {
            uint32_t diff = calcDiff(base_color, palette_data_[i]);

            if (diff < min_diff)
            {
                min_diff = diff;
                target_ID = i;
            }
        }

        return target_ID;
    }

}
