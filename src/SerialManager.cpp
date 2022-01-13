/**
 * @file    SerialManager.cpp
 * @brief   Implementing a class to manage serial communication.
 * @author  Yoshito Nakaue
 * @date    2021/08/05
 */

#include "SerialManager.hpp"
#include "PanelManager.hpp"
#include "Color.hpp"
#include <iostream>

#ifdef __linux__
#include <wiringSerial.h>
#endif

namespace tll
{

    SerialManager* SerialManager::pInstance_ = nullptr;

    void SerialManager::create()
    {
        if (!pInstance_)
        {
            pInstance_ = new SerialManager();
        }
    }

    void SerialManager::destroy()
    {
        delete pInstance_;
        pInstance_ = nullptr;
    }

    void SerialManager::init(std::string LED_driver)
    {
        this->led_driver_ = LED_driver;

        if (LED_driver == "HT16K33")
        {
            #ifdef __linux__
            fd = serialOpen("/dev/ttyUSB0", 115200);
            if (fd < 0)
            {
                this->system_mode = 1;
                std::cout << "Start with simulation mode." << std::endl;
            }
            #else
            std::cout << "Start with simulation mode." << std::endl;
            this->system_mode = 1;    
            #endif
        }
        else if (LED_driver == "HUB75")
        {
            #ifdef __linux__
            rgb_matrix::RGBMatrix::Options options;
            rgb_matrix::RuntimeOptions runtime_options;
            options.rows = 32;
            options.cols = 32;
            options.brightness = 50;

            this->matrix_ = rgb_matrix::CreateMatrixFromOptions(options, runtime_options);
            this->off_canvas_ = this->matrix_->CreateFrameCanvas();
            #else
            std::cout << "Start with simulation mode." << std::endl;
            this->system_mode = 1;
            #endif
        }
    }

    void SerialManager::quit()
    {
        if (this->system_mode == 0)
        {
            #ifdef __linux__
            serialClose(fd);
            #endif
        }
    }

    void SerialManager::sendColorData()
    {
        if (this->system_mode == 0)
        {
            uint16_t width  = PanelManager::getInstance()->getWidth();
            uint16_t height = PanelManager::getInstance()->getHeight();

            // If led driver is HT16K33 and use ESP32
            if (this->led_driver_ == "HT16K33")
            {


                for (uint16_t y = 0; y < height; y++)
                {
                    for (uint16_t x = 0; x < width; x++)
                    {
                        #ifdef __linux__
                        serialPutchar(fd, PanelManager::getInstance()->getColor(x, y));
                        #endif
                    }
                }
            }
            // If led driver is HUB75, only use raspberry pi
            else if (this->led_driver_ == "HUB75")
            {
                for (uint16_t y = 0; y < height; y++)
                {
                    for (uint16_t x = 0; x < width; x++)
                    {
                        #ifdef __linux__
                        Color color = ColorPalette::getInstance()->getColorFromID(PanelManager::getInstance()->getColor(x, y));
                        this->off_canvas_->SetPixel(x, y, color.r_, color.g_, color.b_);
                        #endif
                    }
                }

                this->matrix_->SwapOnVSync(this->off_canvas_);
            }
        }
    }

}
