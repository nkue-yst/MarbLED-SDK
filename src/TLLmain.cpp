/**
 * @file    TLLmain.cpp
 * @brief   公開APIの実装
 * @author  Yoshito Nakaue
 * @date    2021/08/05
 */

#include "TLL.h"
#include "Color.hpp"
#include "PanelManager.hpp"
#include "SerialManager.hpp"
#include "Simulator.hpp"

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
        PanelManager::create();
        PanelManager::getInstance()->init(width, height);

        SerialManager::create();
        SerialManager::getInstance()->init();

        Simulator::create();
    }

    void quit()
    {
        Simulator::getInstance()->destroy();
        SerialManager::getInstance()->destroy();
        PanelManager::getInstance()->destroy();
        ColorPalette::getInstance()->destroy();
    }

    void drawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t c)
    {
        PanelManager::getInstance()->drawRect(x, y, w, h, c);
        SerialManager::getInstance()->sendColorData();
    }

    void clear()
    {
        PanelManager::getInstance()->clear();
        SerialManager::getInstance()->sendColorData();
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
