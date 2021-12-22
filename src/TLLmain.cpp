/**
 * @file    TLLmain.cpp
 * @brief   公開APIの実装
 * @author  Yoshito Nakaue
 * @date    2021/10/19
 */

#include "TLL.h"
#include "Color.hpp"
#include "Event.hpp"
#include "TextRenderer.hpp"
#include "PanelManager.hpp"
#include "SerialManager.hpp"
#include "Simulator.hpp"

#include <opencv2/opencv.hpp>

#include <ctime>

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

namespace tll
{

    void init(uint16_t width, uint16_t height)
    {
        ColorPalette::create();

        // Load color palette information from csv.
        std::cout << "Loading color palette data..." << std::endl;
        std::cout << "-------------------------------" << std::endl;

        std::string str;
        std::ifstream ifs("./src/data/ColorPalette.csv");

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

        std::cout << "-------------------------------" << std::endl;
        std::cout << "Finish loading." << std::endl;

        /* Initialize singleton classes */
        TextRenderer::create();
        TextRenderer::getInstance()->init();

        PanelManager::create();
        PanelManager::getInstance()->init(width, height);

        SerialManager::create();
        SerialManager::getInstance()->init();

        EventHandler::create();
        EventHandler::getInstance()->init();

        SDL_Init(SDL_INIT_VIDEO);
        Simulator::create();
    }

    bool loop()
    {
        EventHandler::getInstance()->updateState();
        Simulation::update();

        return !EventHandler::getInstance()->getQuitFlag();
    }

    void quit()
    {
        PanelManager::getInstance()->clear();
        SerialManager::getInstance()->sendColorData();

        TextRenderer::getInstance()->quit();

        Simulator::getInstance()->destroy();
        SDL_Quit();
        EventHandler::getInstance()->destroy();
        SerialManager::getInstance()->destroy();
        PanelManager::getInstance()->destroy();
        TextRenderer::getInstance()->destroy();
        ColorPalette::getInstance()->destroy();
    }

    void drawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t c)
    {
        PanelManager::getInstance()->drawRect(x, y, w, h, c);
        SerialManager::getInstance()->sendColorData();
    }

    void drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t c)
    {
        PanelManager::getInstance()->drawLine(x1, y1, x2, y2, c);
        SerialManager::getInstance()->sendColorData();
    }

    void drawCircle(uint16_t x, uint16_t y, uint16_t rad, uint8_t c)
    {
        PanelManager::getInstance()->drawCircle(x, y, rad, c);
        SerialManager::getInstance()->sendColorData();
    }

    void print(std::string str, uint8_t c)
    {
        TextRenderer::getInstance()->drawText(str, c, 0, 0);
        SerialManager::getInstance()->sendColorData();
    }

    void clear()
    {
        PanelManager::getInstance()->clear();
        SerialManager::getInstance()->sendColorData();
    }

    tll::Image loadImage(const char* file)
    {
        cv::Mat img = cv::imread(file);
        if (img.empty())
            std::cout << file << " is not found." << std::endl;

        return tll::Image(img);
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


    namespace Simulation
    {
        void start()
        {
            Simulator::getInstance()->start();
        }

        void update()
        {
            Simulator::getInstance()->update();
        }

        void quit()
        {
            Simulator::getInstance()->quit();
        }
    }

}
