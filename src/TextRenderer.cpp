/**
 * @file    TextRenderer.cpp
 * @brief   TextRenderer class
 * @author  Yoshito Nakaue
 * @date    2021/10/18
 */

#include "TextRenderer.hpp"
#include "Common.hpp"
#include "Image.hpp"
#include "PanelManager.hpp"

#include <opencv2/opencv.hpp>

#include <iostream>

namespace tll
{

    TextRenderer* TextRenderer::pInstance_ = nullptr;

    void TextRenderer::create()
    {
        if (!pInstance_)
        {
            pInstance_ = new TextRenderer();

            printLog("Create Text renderer");
        }
    }

    void TextRenderer::destroy()
    {
        delete pInstance_;
        pInstance_ = nullptr;

        printLog("Destroy Text renderer");
    }

    void TextRenderer::init()
    {
        ft2_ = cv::freetype::createFreeType2();

        loadFont();
    }

    void TextRenderer::quit()
    {

    }

    void TextRenderer::drawText(std::string str, uint8_t c, uint32_t x, uint32_t y)
    {
        uint32_t width = PanelManager::getInstance()->getWidth();
        uint32_t height = PanelManager::getInstance()->getHeight();

        cv::String text = str;
        uint32_t thickness  = -1;
        uint32_t line_style = 8;

        cv::Mat img(height, width, CV_8UC3, cv::Scalar::all(0));

        int32_t baseline = 0;

        cv::Size text_size = ft2_->getTextSize(text, font_size_, thickness, &baseline);

        cv::Point text_org((img.cols - text_size.width) / 2, (img.rows + text_size.height) / 2);

        ft2_->putText(img, text, text_org, font_size_, cv::Scalar::all(255), thickness, line_style, true);

        for (int32_t y = 0; y < img.rows; y++)
        {
            for (int32_t x = 0; x < img.cols; x++)
            {
                if (img.at<cv::Vec3b>(y, x)[2] != 0
                 && img.at<cv::Vec3b>(y, x)[1] != 0
                 && img.at<cv::Vec3b>(y, x)[0] != 0)
                {
                    PanelManager::getInstance()->drawPixel(x, y, c);
                }
            }
        }

        // cv::resize(img, img, cv::Size(), 50, 50);
        // cv::imwrite("PrintedText.png", img);
    }

    void TextRenderer::loadFont(const char* font_file_path)
    {
        ft2_->loadFontData(font_file_path, 0);
    }

}
