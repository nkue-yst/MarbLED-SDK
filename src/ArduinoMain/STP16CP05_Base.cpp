/**
 * @file STP16CP05_Base.cpp
 * @brief Base class of STP16CP05
 * @author Yoshito Nakaue
 * @date 2021/11/09
 */

#include "PanelBase.hpp"
#include "STP16CP05_Base.hpp"

STP16CP05_Base::STP16CP05_Base(uint16_t width, uint16_t height, uint16_t num_driver)
    : PanelBase(width, height, num_driver)
{
}

void STP16CP05_Base::init(uint16_t addr)
{
}

void STP16CP05_Base::update()
{
}
