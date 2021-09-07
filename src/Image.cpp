/**
 * @file    Image.cpp
 * @brief   Image class
 * @author  Yoshito Nakaue
 * @date    2021/09/07
 */

#include "Image.hpp"
#include "PanelManager.hpp"

namespace tll
{
    Image::Image()
    {
        img_surface_ = nullptr;
    }

    void Image::loadImage(const char* file)
    {
        cv::imread(file);
    }

    void Image::draw()
    {
        
    }
}
