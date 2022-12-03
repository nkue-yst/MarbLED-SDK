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
#include <vector>

#include "tllEngine.hpp"
#include "Color.hpp"
#include "Common.hpp"
#include "Event.hpp"
#include "PanelManager.hpp"

#include <zmq.hpp>

namespace tll
{

    namespace
    {
        void threadSendColor()
        {
            auto send_data = []() -> void
            {
                /* 送信ソケットの作成 */
                zmq::context_t ctx;
                zmq::socket_t pub(ctx, zmq::socket_type::pub);
                pub.bind("tcp://*:44100");

                /* 色情報の送信を開始 */
                printLog("Start sending color data");
                while (!TLL_ENGINE(EventHandler)->getQuitFlag())
                {
                    if (!TLL_ENGINE(SerialManager)->send_ready)
                    {
                        std::this_thread::sleep_for(std::chrono::milliseconds(16));
                        continue;
                    }

                    std::vector<uint8_t> color_vec;    // 送信用配列
                    color_vec.reserve(TLL_ENGINE(PanelManager)->getWidth() * TLL_ENGINE(PanelManager)->getHeight() * 3);

                    for (uint16_t y = 0; y < TLL_ENGINE(PanelManager)->getHeight(); y++)
                    {
                        for (uint16_t x = 0; x < TLL_ENGINE(PanelManager)->getWidth(); x++)
                        {
                            Color c = TLL_ENGINE(PanelManager)->getColor(x, y);
                            color_vec.push_back(c.r_);
                            color_vec.push_back(c.g_);
                            color_vec.push_back(c.b_);
                        }
                    }

                    zmq::message_t topic("color");
                    auto res = pub.send(topic, zmq::send_flags::sndmore);

                    zmq::message_t msg(color_vec);
                    res = pub.send(msg, zmq::send_flags::none);

                    TLL_ENGINE(SerialManager)->send_ready = false;
                }

                pub.close();
            };

            std::thread th_send_data(send_data);
            th_send_data.detach();
        }
    }

    ISerialManager* ISerialManager::create()
    {
        return new SerialManager();
    }

    SerialManager::SerialManager() noexcept
    {
        this->system_mode = 0;

        printLog("Create Serial manager");
    }

    SerialManager::~SerialManager() noexcept
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
                        //serialPutchar(fd, TLL_ENGINE(PanelManager)->getColor(x, y));
                        #endif
                    }
                }
            }
        }

        TLL_ENGINE(SerialManager)->send_ready = true;
    }

}
