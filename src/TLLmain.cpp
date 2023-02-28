/**
 * @file    TLLmain.cpp
 * @brief   公開APIの実装
 * @author  Yoshito Nakaue
 * @date    2022/08/22
 */

#include "TLL.h"

#include <chrono>
#include <csignal>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

#include "tllEngine.hpp"
#include "Color.hpp"
#include "Common.hpp"
#include "Event.hpp"
#include "PanelManager.hpp"
#include "SerialManager.hpp"
#include "TextRenderer.hpp"

#include <opencv2/opencv.hpp>

namespace tll
{
    void init(uint16_t width, uint16_t height, std::string LED_driver)
    {
        // エンジン，コンポーネントを初期化する
        tllEngine::get()->init(width, height, LED_driver);

        std::cout << std::endl;
    }

    bool loop() noexcept
    {
        auto quitSignal = [](int flag) {
            std::cout << std::endl;
            TLL_ENGINE(EventHandler)->setQuitFlag(true);
        };
        signal(SIGINT, quitSignal);

        TLL_ENGINE(EventHandler)->updateState();

        TLL_ENGINE(SerialManager)->sendColorData();

        return !TLL_ENGINE(EventHandler)->getQuitFlag();
    }

    void quit()
    {
        TLL_ENGINE(PanelManager)->clear();
        TLL_ENGINE(SerialManager)->sendColorData();

        tllEngine::get()->quit();
    }

    void drawPixel(uint16_t x, uint16_t y, Color color)
    {
        TLL_ENGINE(PanelManager)->drawPixel(x, y, color);
        //TLL_ENGINE(SerialManager)->sendColorData();
    }

    void drawPixels(std::vector<uint16_t> x, std::vector<uint16_t> y, Color color)
    {
        for (size_t i = 0; i < x.size(); i++)
        {
            TLL_ENGINE(PanelManager)->drawPixel(x.at(i), y.at(i), color);
        }
        //TLL_ENGINE(SerialManager)->sendColorData();
    }

    void drawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, Color color)
    {
        TLL_ENGINE(PanelManager)->drawRect(x, y, w, h, color);
        //TLL_ENGINE(SerialManager)->sendColorData();
    }

    void drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, Color color)
    {
        TLL_ENGINE(PanelManager)->drawLine(x1, y1, x2, y2, color);
        //TLL_ENGINE(SerialManager)->sendColorData();
    }

    void drawCircle(uint16_t x, uint16_t y, uint16_t rad, Color color)
    {
        TLL_ENGINE(PanelManager)->drawCircle(x, y, rad, color);
        //TLL_ENGINE(SerialManager)->sendColorData();
    }

    void print(std::string str, uint16_t x, uint16_t y, uint16_t size, Color color)
    {
        TLL_ENGINE(TextRenderer)->drawText(str, color, x, y, size);
        //TLL_ENGINE(SerialManager)->sendColorData();
    }

    void clear()
    {
        TLL_ENGINE(PanelManager)->clear();
        //TLL_ENGINE(SerialManager)->sendColorData();
    }

    tll::Image* loadImage(const char* file)
    {
        cv::Mat img = cv::imread(file);
        if (img.empty())
            std::cout << file << " is not found." << std::endl;

        return new tll::Image(img);
    }

    tll::Video loadVideo(const char* file)
    {
        cv::VideoCapture video;
        video.open(file);
        if (video.isOpened() == false)
            std::cerr << "[ERROR] Failed to load video file" << std::endl;

        return tll::Video(video);
    }

    std::string timeToString()
    {
        time_t now = std::time(NULL);
        struct tm *pnow = std::localtime(&now);

        std::string h = std::to_string(pnow->tm_hour);

        std::ostringstream m_str;
        m_str << std::setfill('0') << std::setw(2) << pnow->tm_min;
        std::string m = m_str.str();

        return h + ":" + m;
    }

    uint32_t getTouchedNum()
    {
        return TLL_ENGINE(EventHandler)->getTouchedNum();
    }

}
