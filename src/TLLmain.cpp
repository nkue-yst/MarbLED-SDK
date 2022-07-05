/**
 * @file    TLLmain.cpp
 * @brief   公開APIの実装
 * @author  Yoshito Nakaue
 * @date    2021/10/19
 */

#include "TLL.h"
#include "Color.hpp"
#include "Common.hpp"
#include "Event.hpp"
#include "TextRenderer.hpp"
#include "PanelManager.hpp"
#include "SerialManager.hpp"

#include <opencv2/opencv.hpp>

#include <ctime>
#include <chrono>
#include <csignal>
#include <thread>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

namespace tll
{
    bool verbose = false;

    void init(uint16_t width, uint16_t height, std::string LED_driver, bool verbose_flag)
    {
        verbose = verbose_flag;
        startClock();

        ColorPalette::create();

        // Load color palette information from csv.
        std::string str;
        std::ifstream ifs("ColorPalette.csv");

        while (getline(ifs, str))
        {
            std::string color_name = "";
            std::string color_code = "";

            std::istringstream stream(str);

            std::string temp = "";
            int w_cnt = 1;
            while (getline(stream, temp, ','))
            {
                ((w_cnt % 2 != 0) ? color_name : color_code) = temp;
                w_cnt++;
            }

            uint32_t rgb = (uint32_t)(strtol((const char*)&color_code[1], NULL, 16));
            uint16_t r = (rgb >> 16) & 0xFF;
            uint16_t g = (rgb >>  8) & 0xFF;
            uint16_t b = (rgb >>  0) & 0xFF;

            ColorPalette::getInstance()->addColor(Color(color_name, r, g, b));
        }
        printLog("Load color palette data");

        /* Initialize singleton classes */
        TextRenderer::create();
        TextRenderer::getInstance()->init();

        PanelManager::create();
        PanelManager::getInstance()->init(width, height);

        SerialManager::create();
        SerialManager::getInstance()->init(LED_driver);

        EventHandler::create();
        EventHandler::getInstance()->init();

        std::cout << std::endl;

        endClock("tll::init()");
    }

    bool loop()
    {
        auto quitSignal = [](int flag) {
            std::cout << std::endl;
            EventHandler::getInstance()->setQuitFlag(true);
        };
        signal(SIGINT, quitSignal);

        EventHandler::getInstance()->updateState();
        //std::cout << "Loop" << std::endl;
        //std::this_thread::sleep_for(std::chrono::milliseconds(500));

        return !EventHandler::getInstance()->getQuitFlag();
    }

    void quit()
    {
        startClock();

        PanelManager::getInstance()->clear();
        SerialManager::getInstance()->sendColorData();
        EventHandler::getInstance()->quit();
        TextRenderer::getInstance()->quit();

        EventHandler::getInstance()->destroy();
        SerialManager::getInstance()->destroy();
        PanelManager::getInstance()->destroy();
        TextRenderer::getInstance()->destroy();
        ColorPalette::getInstance()->destroy();

        endClock("tll::quit()");
    }

    void drawPixel(uint16_t x, uint16_t y, uint8_t color)
    {
        PanelManager::getInstance()->drawPixel(x, y, color);
        SerialManager::getInstance()->sendColorData();
    }

    void drawPixels(std::vector<uint16_t> x, std::vector<uint16_t> y, uint8_t color)
    {
        for (int i = 0; i < x.size(); i++)
        {
            PanelManager::getInstance()->drawPixel(x.at(i), y.at(i), color);
        }
        SerialManager::getInstance()->sendColorData();
    }

    void drawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t c)
    {
        startClock();

        PanelManager::getInstance()->drawRect(x, y, w, h, c);
        SerialManager::getInstance()->sendColorData();

        endClock("tll::drawRect()");
    }

    void drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t c)
    {
        startClock();

        PanelManager::getInstance()->drawLine(x1, y1, x2, y2, c);
        SerialManager::getInstance()->sendColorData();

        endClock("tll::drawLine()");
    }

    void drawCircle(uint16_t x, uint16_t y, uint16_t rad, uint8_t c)
    {
        startClock();

        PanelManager::getInstance()->drawCircle(x, y, rad, c);
        SerialManager::getInstance()->sendColorData();

        endClock("tll::drawCircle()");
    }

    void print(std::string str, uint8_t c)
    {
        startClock();

        TextRenderer::getInstance()->drawText(str, c, 0, 0);
        SerialManager::getInstance()->sendColorData();

        endClock("tll::print()");
    }

    void clear()
    {
        startClock();

        PanelManager::getInstance()->clear();
        SerialManager::getInstance()->sendColorData();

        endClock("tll::clear()");
    }

    tll::Image loadImage(const char* file)
    {
        startClock();

        cv::Mat img = cv::imread(file);
        if (img.empty())
            std::cout << file << " is not found." << std::endl;

        endClock("tll::loadImage()");

        return tll::Image(img);
    }

    tll::Video loadVideo(const char* file)
    {
        startClock();

        cv::VideoCapture video;
        video.open(file);
        if (video.isOpened() == false)
            std::cerr << "[ERROR] Failed to load video file" << std::endl;

        endClock("tll::loadVideo()");

        return tll::Video(video);
    }

    std::string timeToString()
    {
        time_t now = std::time(NULL);
        struct tm *pnow = std::localtime(&now);

        std::string h = std::to_string(pnow->tm_hour);
        //std::string m = std::to_string(pnow->tm_min);

        std::ostringstream m_str;
        m_str << std::setfill('0') << std::setw(2) << pnow->tm_min;
        std::string m = m_str.str();

        return h + ":" + m;
    }


    namespace Palette
    {
        uint8_t color(std::string color_name)
        {
            return ColorPalette::getInstance()->getIDFromName(color_name);
        }
    }

    static double clock = 0.0;

    void startClock()
    {
        if (!verbose)
            return;

        struct::timespec current_time;
        clock_gettime(CLOCK_MONOTONIC, &current_time);
        clock = (current_time.tv_sec + current_time.tv_nsec * 1e-9) * 1000;
    }

    void endClock(std::string function_name)
    {
        if (!verbose)
            return;

        struct::timespec current_time;
        clock_gettime(CLOCK_MONOTONIC, &current_time);

        std::cout << "tll-Log: " << function_name << " - " << ((current_time.tv_sec + current_time.tv_nsec * 1e-9) * 1000) - clock << "[ms]" << std::endl;
    }

}
