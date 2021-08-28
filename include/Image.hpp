/**
 * @file    Image.hpp
 * @brief   Image class
 * @author  Yoshito Nakaue
 * @date    2021/08/28
 */

#include <SDL.h>

namespace tll
{
    /**
     * @brief  Loaded image class
     */
    class Image
    {
    public:
        Image();

        /**
         * @fn     void loadImage(const char* file)
         * @brief  Load bmp file
         * @param  file  BMP file path
         */
        void loadBMP(const char* file);

        /**
         * @fn     void draw()
         * @brief  Resize and draw image
         */
        void draw();

    private:
        /// Image data
        SDL_Surface* img_surface_;
    };
}
