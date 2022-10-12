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

#include <sys/socket.h>
#include <sys/un.h>

#include "tllEngine.hpp"
#include "Color.hpp"
#include "Common.hpp"
#include "Event.hpp"
#include "PanelManager.hpp"

#ifdef WITH_RASPI
#include <wiringSerial.h>
#endif

#define UNIX_SOCKET_PATH "/tmp/tll/unix_socket"

namespace tll
{

    namespace
    {
        void threadSendColor()
        {
            auto send_data = []() -> void
            {
                /* 接続先の設定 */
                struct sockaddr_un dest_addr;
                std::memset(&dest_addr, 0, sizeof(struct sockaddr_un));
                
                dest_addr.sun_family = AF_UNIX;
                std::strcpy(dest_addr.sun_path, UNIX_SOCKET_PATH);
                int32_t sock = socket(AF_UNIX, SOCK_STREAM, 0);

                /* データ送信先が受信待ち状態になるまで接続を試みる */
                printLog("Start waiting for simulator to connect");
                while (connect(sock, (struct sockaddr*)&dest_addr, sizeof(struct sockaddr_un)) == -1)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
                printLog("Simulator is connected");

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
                            color_vec.push_back(c.b_);
                            color_vec.push_back(c.g_);
                            color_vec.push_back(c.r_);
                        }
                    }
                    send(sock, color_vec.data(), TLL_ENGINE(PanelManager)->getWidth() * TLL_ENGINE(PanelManager)->getHeight() * 3, 0);

                    #ifndef WITH_RASPI
                    std::this_thread::sleep_for(std::chrono::milliseconds(33));
                    #endif

                    TLL_ENGINE(SerialManager)->send_ready = false;
                }

                close(sock);
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
                        //serialPutchar(fd, TLL_ENGINE(PanelManager)->getColor(x, y));
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
                        Color color = TLL_ENGINE(PanelManager)->getColor(x, y);
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
