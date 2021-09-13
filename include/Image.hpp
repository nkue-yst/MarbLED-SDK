/**
 * @file    Image.hpp
 * @brief   Image class
 * @author  Yoshito Nakaue
 * @date    2021/09/07
 */

#include <opencv2/opencv.hpp>

namespace tll
{
    /**
     * @brief  Loaded image class
     */
    class Image
    {
    public:
        Image();
        Image(cv::Mat img_data);

        /**
         * @fn     void draw()
         * @brief  Resize and draw image
         */
        void draw();

        /**
         * @fn     void resize(uint32_t height, uint32_t width)
         * @brief  Resize image size
         */
        void resize(uint32_t height, uint32_t width);

    private:
        /// Image data
        cv::Mat img_data_;
    };
}
