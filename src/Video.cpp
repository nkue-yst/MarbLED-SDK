/**
 * @file    Video.cpp
 * @brief   Video class
 * @author  Yoshito Nakaue
 * @date    2021/10/19
 */

#include "Video.hpp"
#include "Color.hpp"
#include "PanelManager.hpp"
#include "SerialManager.hpp"
#include "Simulator.hpp"
#include "TLL.h"

#include <thread>
#include <chrono>
#include <unistd.h>
#include <iostream>

namespace tll
{

    Video::Video()
    {
    }

    Video::Video(cv::VideoCapture video)
    {
        video_data_ = video;
    }

    void Video::play(uint32_t pos_x, uint32_t pos_y, uint32_t size_rate)
    {
        uint32_t width = static_cast<uint32_t>(video_data_.get(cv::CAP_PROP_FRAME_WIDTH));
        uint32_t height = static_cast<uint32_t>(video_data_.get(cv::CAP_PROP_FRAME_HEIGHT));

        cv::Mat frame(cv::Size(width, height), CV_8UC3);  // Image object for a frame

        double end_frame = video_data_.get(cv::CAP_PROP_FRAME_COUNT);

        cv::Mat dst = cv::Mat::ones(height / size_rate, width / size_rate, CV_8U);

        for (uint32_t i = 0; i < static_cast<uint32_t>(end_frame); i++)
        {
            video_data_ >> frame;

            if (i % 5 != 0)
                continue;

            cv::resize(frame, dst, dst.size());

            for (int32_t y = 0; y < dst.rows; y++)
            {
                for (int32_t x = 0; x < dst.cols; x++)
                {
                    PanelManager::getInstance()->drawPixel(
                        x + pos_x,
                        y + pos_y,
                        ColorPalette::getInstance()->getIDFromRGB(
                            dst.at<cv::Vec3b>(y, x)[2],
                            dst.at<cv::Vec3b>(y, x)[1],
                            dst.at<cv::Vec3b>(y, x)[0]
                        )
                    );
                }
            }

            SerialManager::getInstance()->sendColorData();
            std::this_thread::sleep_for(std::chrono::milliseconds(16));
            Simulator::getInstance()->update();
        }

        tll::clear();
    }

}
