/**
 * @file    TLLmain.cpp
 * @brief   公開APIの実装
 * @author  Yoshito Nakaue
 * @date    2021/07/23
 */

#include "TLL.h"
#include "PanelManager.hpp"
#include "Simulator.hpp"

namespace tll
{

    void init(uint16_t width, uint16_t height)
    {
        PanelManager::create();
        PanelManager::getInstance()->init(width, height);

        Simulator::create();
    }

    void quit()
    {
        PanelManager::getInstance()->destroy();
        Simulator::getInstance()->destroy();
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
