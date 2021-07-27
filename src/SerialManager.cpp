/**
 * @file    SerialManager.cpp
 * @brief   Implementing a class to manage serial communication.
 * @author  Yoshito Nakaue
 * @date    2021/07/27
 */

#include "SerialManager.hpp"
#include "PanelManager.hpp"
#include <wiringSerial.h>
#include <iostream>

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
        fd = serialOpen("/dev/ttyUSB0", 115200);
    }

    void SerialManager::quit()
    {
        serialClose(fd);
    }

    void SerialManager::sendColorData()
    {
        int width  = PanelManager::getInstance()->getWidth();
        int height = PanelManager::getInstance()->getHeight();

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                if (PanelManager::getInstance()->getColor(x, y) == 1)
                {
                    serialPutchar(fd, x);
                    serialPutchar(fd, y);
                    serialPutchar(fd, 1);
                }
            }
        }
    }

}
