/**
 * @file    TextRenderer.cpp
 * @brief   TextRenderer class
 * @author  Yoshito Nakaue
 * @date    2021/10/18
 */

#include "TextRenderer.hpp"
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
        }
    }

    void TextRenderer::destroy()
    {
        delete pInstance_;
        pInstance_ = nullptr;
    }

    void TextRenderer::init()
    {
        ft2_ = cv::freetype::createFreeType2();

        loadFont();
    }

    void TextRenderer::quit()
    {

    }

    void TextRenderer::drawText(const char* str, uint32_t x, uint32_t y)
    {
        uint32_t width = PanelManager::getInstance()->getWidth() * 10;
        uint32_t height = PanelManager::getInstance()->getHeight() * 10;

        cv::String text = str;
        uint32_t thickness  = -1;
        uint32_t line_style = 8;

        cv::Mat img(height, width, CV_8UC3, cv::Scalar::all(0));

        int32_t baseline = 0;

        cv::Size text_size = ft2_->getTextSize(text, font_size_, thickness, &baseline);

        cv::Point text_org((img.cols - text_size.width) / 2, (img.rows + text_size.height) / 2);

        ft2_->putText(img, text, text_org, font_size_, cv::Scalar::all(255), thickness, line_style, true);

        Image img_dest(img);
        img_dest.resize(height / 10, width / 10);
        img_dest.draw(0, 0);

        //cv::imwrite("PrintedText.png", img);
    }

    void TextRenderer::loadFont(const char* font_file_path)
    {
        ft2_->loadFontData(font_file_path, 0);
    }

}
