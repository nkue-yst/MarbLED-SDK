/**
 * @file    Image.cpp
 * @brief   Image class
 * @author  Yoshito Nakaue
 * @date    2021/09/28
 */

#include "Image.hpp"
#include "Color.hpp"
#include "PanelManager.hpp"
#include "SerialManager.hpp"
#include "Simulator.hpp"

#include <iostream>

namespace tll
{
    Image::Image()
    {
    }

    Image::Image(cv::Mat img_data)
    {
        img_data_ = img_data;
    }

    void Image::draw(uint32_t x, uint32_t y)
    {
        for (int Y = 0; Y < img_data_.rows; Y++)
        {
            for (int X = 0; X < img_data_.cols; X++)
            {
                PanelManager::getInstance()->drawPixel(
                    x + X,
                    y + Y,
                    ColorPalette::getInstance()->getIDFromRGB(
                        img_data_.at<cv::Vec3b>(Y, X)[2],
                        img_data_.at<cv::Vec3b>(Y, X)[1],
                        img_data_.at<cv::Vec3b>(Y, X)[0]
                    )
                );
            }
        }

        SerialManager::getInstance()->sendColorData();
        Simulator::getInstance()->update();
    }

    void Image::resize(uint32_t height, uint32_t width)
    {
        cv::Mat dst = cv::Mat::ones(height, width, CV_8U);

        cv::resize(img_data_, dst, dst.size());
        img_data_ = dst;
    }
}
