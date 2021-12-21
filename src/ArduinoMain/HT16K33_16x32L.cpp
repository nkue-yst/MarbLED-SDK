/**
 * @file 
 * @brief 
 * @author Yoshito Nakaue
 * @date 
 */

#include "HT16K33_16x32L.hpp"
#include <Arduino.h>

HT16K33_16x32L::HT16K33_16x32L()
    : HT16K33_Base(16, 32, 3)
{
    registerMatrixInfo();
}

void HT16K33_16x32L::registerMatrixInfo()
{
    for (int y = 0; y < 32; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            PixelInfo p = PixelInfo(EChipType::LED, ((x % 3 == 0) ? 1 : 0));
            pixels_info_.push_back(p);  
        }
    }
}
