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
    }

    Image::Image(cv::Mat img_data)
    {
        img_data_ = img_data;
    }

    void Image::draw()
    {
        
    }

    void Image::resize(uint32_t height, uint32_t width)
    {
        cv::Mat dst = cv::Mat::ones(height, width, CV_8U);

        cv::resize(img_data_, dst, dst.size());
        img_data_ = dst;
    }
}
