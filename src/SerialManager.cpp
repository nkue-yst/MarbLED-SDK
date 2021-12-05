/**
 * @file    SerialManager.cpp
 * @brief   Implementing a class to manage serial communication.
 * @author  Yoshito Nakaue
 * @date    2021/08/05
 */

#include "SerialManager.hpp"
#include "PanelManager.hpp"
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

    void SerialManager::init()
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
            int width  = PanelManager::getInstance()->getWidth();
            int height = PanelManager::getInstance()->getHeight();

            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    #ifdef __linux__
                    serialPutchar(fd, PanelManager::getInstance()->getColor(x, y));
                    #endif
                }
            }
        }
    }

}
