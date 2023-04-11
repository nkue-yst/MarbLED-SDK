/**
 * @file    TextRenderer.cpp
 * @brief   TextRenderer class
 * @author  Yoshito Nakaue
 * @date    2021/10/18
 */

#include "TextRenderer.hpp"

#include <iostream>

#include "tllEngine.hpp"
#include "Common.hpp"
#include "Image.hpp"
#include "PanelManager.hpp"

#include <opencv2/opencv.hpp>

namespace tll
{

    ITextRenderer* ITextRenderer::create()
    {
        return new TextRenderer();
    }

    TextRenderer::TextRenderer() noexcept
    {
        this->font_size_ = 22;
        printLog("Create Text renderer");
    }

    TextRenderer::~TextRenderer() noexcept
    {
        printLog("Destroy Text renderer");
    }

    void TextRenderer::init()
    {
        this->ft2_ = cv::freetype::createFreeType2();

        this->loadFont();
    }

    void TextRenderer::drawText(std::string str, Color color, uint32_t x, uint32_t y, uint16_t size)
    {
        uint32_t width  = TLL_ENGINE(PanelManager)->getWidth();
        uint32_t height = TLL_ENGINE(PanelManager)->getHeight();

        this->font_size_ = size;

        cv::String text = str;
        uint32_t thickness  = -1;
        uint32_t line_style = 8;

        cv::Mat img(height, width, CV_8UC3, cv::Scalar::all(0));

        int32_t baseline = 0;

        cv::Size text_size = ft2_->getTextSize(text, font_size_, thickness, &baseline);

        cv::Point text_org((img.cols - text_size.width) / 2, (img.rows + text_size.height) / 2);

        ft2_->putText(img, text, text_org, font_size_, cv::Scalar::all(255), thickness, line_style, true);

        for (int32_t Y = 0; Y < img.rows; Y++)
        {
            for (int32_t X = 0; X < img.cols; X++)
            {
                if (img.at<cv::Vec3b>(Y, X)[2] != 0
                 && img.at<cv::Vec3b>(Y, X)[1] != 0
                 && img.at<cv::Vec3b>(Y, X)[0] != 0)
                {
                    TLL_ENGINE(PanelManager)->drawPixel(x + X, y + Y, color);
                }
            }
        }
    }

    void TextRenderer::loadFont(const char* font_file_path)
    {
        this->ft2_->loadFontData(font_file_path, 0);
    }

}
