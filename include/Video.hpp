/**
 * @file    Video.hpp
 * @brief   Video class
 * @author  Yoshito Nakaue
 * @date    2021/10/19
 */

#ifndef VIDEO_HPP
#define VIDEO_HPP

#include <opencv2/opencv.hpp>

namespace tll
{
    /**
     * @brief  Video class
     */
    class Video
    {
    public:
        Video();
        Video(cv::VideoCapture video);

        /**
         * @fn  void play()
         */
        void play(uint32_t pos_x, uint32_t pos_y, uint32_t size_rate = 1);

    private:
        /// Video data
        cv::VideoCapture video_data_;
    };
}

#endif
