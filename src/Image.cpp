/**
 * @file    Image.cpp
 * @brief   Image class
 * @author  Yoshito Nakaue
 * @date    2022/08/18
 */

#include "Image.hpp"

#include <iostream>

#include "tllEngine.hpp"
#include "Color.hpp"
#include "PanelManager.hpp"
#include "SerialManager.hpp"

namespace tll
{
    Image::Image() noexcept
    {
    }

    Image::Image(cv::Mat img_data) noexcept
    {
        img_data_ = img_data;
    }

    void Image::draw(uint32_t x, uint32_t y)
    {
        // ピクセルごとに画像データの色を適用していく
        for (int Y = 0; Y < img_data_.rows; Y++)
        {
            for (int X = 0; X < img_data_.cols; X++)
            {
                TLL_ENGINE(PanelManager)->drawPixel(
                    x + X,
                    y + Y,
                    Color(
                        img_data_.at<cv::Vec3b>(Y, X)[2],
                        img_data_.at<cv::Vec3b>(Y, X)[1],
                        img_data_.at<cv::Vec3b>(Y, X)[0]
                    )
                );
            }
        }

        TLL_ENGINE(SerialManager)->sendColorData();
    }

    void Image::draw(uint32_t x, uint32_t y, tll::Color color)
    {
        for (int Y = 0; Y < img_data_.rows; Y++)
        {
            for (int X = 0; X < img_data_.cols; X++)
            {
                // 色の無いピクセルは黒を表示
                if (img_data_.at<cv::Vec3b>(Y, X)[2] == 0 &&
                    img_data_.at<cv::Vec3b>(Y, X)[1] == 0 &&
                    img_data_.at<cv::Vec3b>(Y, X)[0] == 0)
                {
                    TLL_ENGINE(PanelManager)->drawPixel(
                        x + X,
                        y + Y,
                        Color(0, 0, 0)
                    );
                }
                else    // 色の付いているピクセルは指定色で表示
                {
                    TLL_ENGINE(PanelManager)->drawPixel(
                        x + X,
                        y + Y,
                        Color(
                            color.r_,
                            color.g_,
                            color.b_
                        )
                    );
                }
            }
        }

        TLL_ENGINE(SerialManager)->sendColorData();
    }

    void Image::resize(uint32_t height, uint32_t width)
    {
        cv::Mat dst = cv::Mat::ones(height, width, CV_8U);

        cv::resize(img_data_, dst, dst.size());
        img_data_ = dst;
    }
}
