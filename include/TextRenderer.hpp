/**
 * @file    TextRenderer.hpp
 * @brief   TextRenderer class
 * @author  Yoshito Nakaue
 * @date    2022/08/22
 */

#ifndef __TEXT_RENDERER_HPP__
#define __TEXT_RENDERER_HPP__

#include "Color.hpp"

#include <cstdint>
#include <string>

#include <opencv2/freetype.hpp>

namespace tll
{

    /* 文字列描画インターフェースクラス */
    class ITextRenderer
    {
    public:
        virtual ~ITextRenderer() = default;

        // インスタンスを作成
        static ITextRenderer* create();

        // テキストレンダラを初期化する
        virtual void init() = 0;

        // 文字列を描画する
        virtual void drawText(std::string str, Color color, uint32_t x, uint32_t y, uint16_t size) = 0;

    protected:
        // フォントデータを読み込む
        virtual void loadFont(const char* font_file_path = "NotoSansJP-Regular.otf") = 0;

        /// freetype object
        cv::Ptr<cv::freetype::FreeType2> ft2_;

        /// Font size
        uint32_t font_size_;
    };

    // 文字列描画クラス
    class TextRenderer : public ITextRenderer
    {
    public:
        TextRenderer() noexcept;
        ~TextRenderer() noexcept override;

        // テキストレンダラを初期化する
        void init() override;

        // 文字列を描画する
        void drawText(std::string str, Color color, uint32_t x, uint32_t y, uint16_t size) override;

    private:
        // フォントデータを読み込む
        void loadFont(const char* font_file_path = "NotoSansJP-Regular.otf") override;
    };

}

#endif
