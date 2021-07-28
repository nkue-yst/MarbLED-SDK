/**
 * @file    Color.cpp
 * @brief   Color information class
 * @author  Yoshito Nakaue
 * @date    2021/08/04
 */

#include "Color.hpp"

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

}
