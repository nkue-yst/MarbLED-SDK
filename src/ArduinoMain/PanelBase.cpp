/**
 * @file PanelBase.cpp
 * @brief Base class of LED panel
 * @author Yoshito Nakaue
 * @date 2021/11/09
 */

#include "PanelBase.hpp"

PanelBase::PanelBase(uint16_t width, uint16_t height, uint16_t num_driver)
{   
    width_ = width;
    height_ = height;

    num_driver_ = num_driver;
}
