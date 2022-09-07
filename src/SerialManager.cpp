/**
 * @file    SerialManager.cpp
 * @brief   Implementing a class to manage serial communication.
 * @author  Yoshito Nakaue
 * @date    2022/08/22
 */

#include "SerialManager.hpp"

#include <iostream>
#include <chrono>
#include <thread>
#include <unistd.h>

#include "tllEngine.hpp"
#include "PanelManager.hpp"
#include "Color.hpp"
#include "Common.hpp"

#include <zmq.hpp>

#ifdef WITH_RASPI
#include <wiringSerial.h>
#endif

namespace tll
{

    /* シミュレータ用の色情報送信処理 */
    void threadSendColor()
    {
        auto send_data = []()
        {
            zmq::context_t ctx;
            zmq::socket_t sock(ctx, zmq::socket_type::push);
            sock.connect("tcp://127.0.0.1:44100");

            while (true)
            {
                if (!TLL_ENGINE(SerialManager)->send_ready)
                    continue;

                for (uint16_t y = 0; y < TLL_ENGINE(PanelManager)->getHeight(); y++)
                {
                    for (uint16_t x = 0; x < TLL_ENGINE(PanelManager)->getWidth(); x++)
                    {
                        Color color = TLL_ENGINE(PanelManager)->getColor(x, y);
                        std::vector<uint16_t> color_vec = { static_cast<uint16_t>(x + TLL_ENGINE(PanelManager)->getWidth() * y), color.r_, color.g_, color.b_ };

                        zmq::message_t msg(color_vec);
                        
                        auto res = sock.send(msg, zmq::send_flags::none);
                    }
                }

                TLL_ENGINE(SerialManager)->send_ready = false;
            }
        };

        std::thread th_send_data(send_data);
        th_send_data.detach();
    }

    ISerialManager* ISerialManager::create()
    {
        return new SerialManager();
    }

    SerialManager::SerialManager()
    {
        this->system_mode = 0;

        printLog("Create Serial manager");
    }

    SerialManager::~SerialManager()
    {
        if (this->system_mode == 0)
        {
            #ifdef WITH_RASPI
            serialClose(fd);
            #endif
        }

        printLog("Destroy Serial manager");
    }

    void SerialManager::init(std::string LED_driver)
    {
        this->led_driver_ = LED_driver;

        if (LED_driver == "HT16K33")
        {
            #ifdef WITH_RASPI
            fd = serialOpen("/dev/ttyUSB0", 115200);
            if (fd < 0)
            {
                this->system_mode = 1;
                std::cout << "Start with simulation mode." << std::endl;
            }
            #else
            //std::cout << "Start with simulation mode." << std::endl;
            this->system_mode = 1;    
            #endif
        }
        else if (LED_driver == "HUB75")
        {
            #ifdef WITH_RASPI
            rgb_matrix::RGBMatrix::Options options;
            rgb_matrix::RuntimeOptions runtime_options;
            options.hardware_mapping = "adafruit-hat";
            options.rows = 32;
            options.cols = 64;
            //options.chain_length = 2;
            options.brightness = 100;
            //options.limit_refresh_rate_hz = 30;

	        runtime_options.gpio_slowdown = 4;

            this->matrix_ = rgb_matrix::CreateMatrixFromOptions(options, runtime_options);
            this->off_canvas_ = this->matrix_->CreateFrameCanvas();
            #else
            //std::cout << "Start with simulation mode." << std::endl;
            this->system_mode = 1;
            #endif
        }

        threadSendColor();
    }

    void SerialManager::sendColorData()
    {
        if (this->system_mode == 0)
        {
            uint16_t width  = TLL_ENGINE(PanelManager)->getWidth();
            uint16_t height = TLL_ENGINE(PanelManager)->getHeight();

            // If led driver is HT16K33 and use ESP32
            if (this->led_driver_ == "HT16K33")
            {
                for (uint16_t y = 0; y < height; y++)
                {
                    for (uint16_t x = 0; x < width; x++)
                    {
                        #ifdef WITH_RASPI
                        serialPutchar(fd, TLL_ENGINE(PanelManager)->getColor(x, y));
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
                        #ifdef WITH_RASPI
                        Color color = ColorPalette::getInstance()->getColorFromID(TLL_ENGINE(PanelManager)->getColor(x, y));
                        this->off_canvas_->SetPixel(x, y, color.r_, color.g_, color.b_);
                        #endif
                    }
                }

                #ifdef WITH_RASPI
                this->matrix_->SwapOnVSync(this->off_canvas_);
                #endif
            }
        }

        TLL_ENGINE(SerialManager)->send_ready = true;
    }

}
