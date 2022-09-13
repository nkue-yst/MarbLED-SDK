/**
 * @file    Image.hpp
 * @brief   Image class
 * @author  Yoshito Nakaue
 * @date    2022/08/17
 */

#ifndef __IMAGE_HPP__
#define __IMAGE_HPP__

#include "Color.hpp"

#include <opencv2/opencv.hpp>

namespace tll
{
    /* 画像クラス */
    class Image
    {
    public:
        Image() noexcept;
        Image(cv::Mat img_data) noexcept;

        // 指定座標に画像を表示
        void draw(uint32_t x, uint32_t y);

        // 指定座標に色を付けて画像を表示
        void draw(uint32_t x, uint32_t y, tll::Color color);

        // 指定サイズにリサイズ
        void resize(uint32_t height, uint32_t width);

    private:
        // 画像データ（OpenCVの形式を利用）
        cv::Mat img_data_;
    };
}

#endif
