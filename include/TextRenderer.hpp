/**
 * @file    TextRenderer.hpp
 * @brief   TextRenderer class
 * @author  Yoshito Nakaue
 * @date    2021/10/18
 */

#ifndef TEXT_RENDERER_HPP
#define TEXT_RENDERER_HPP

#include <opencv2/freetype.hpp>

#include <cstdint>
#include <string>

namespace tll
{

    /**
     * @brief  TextRenderer class
     */
    class TextRenderer
    {
    public:
        /**
         * @fn      static TextRenderer* getInstance()
         * @brief   Get instance of text renderer
         * @return  Instance of text renderer
         */
        static TextRenderer* getInstance()
        {
            return pInstance_;
        }

        /**
         * 
         */
        static void create();

        /**
         * 
         */
        static void destroy();

        /**
         * @fn     void init()
         * @brief  Initialize text renderer class
         */
        void init();

        /**
         * @fn     void quit()
         * @brief  Quit text renderer class
         */
        void quit();

        /**
         * @fn     void drawText(std::string str, uint32_t x, uint32_t y)
         * @brief  Drawing text
         */
        void drawText(std::string str, uint8_t c, uint32_t x, uint32_t y);

    protected:
        TextRenderer()
            : font_size_(5)
        {
        }

        // Instance for singleton
        static TextRenderer* pInstance_;

    private:
        /**
         * @fn  void loadFont(const char* font_file_path)
         */
        void loadFont(const char* font_file_path = "./font/4x4kanafont.ttf");

        /// freetype object
        cv::Ptr<cv::freetype::FreeType2> ft2_;

        /// Font size
        uint32_t font_size_;
    };

}

#endif
