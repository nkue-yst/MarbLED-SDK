/**
 * @file  TLLmain.cpp
 * @brief  公開APIの実装
 * @author  Yoshito Nakaue
 * @data  2021/07/23
 */

#include "TLL.h"
#include "PanelManager.hpp"

namespace tll
{

void init(uint16_t width, uint16_t height)
{
    PanelManager::create();
    PanelManager::getPanelManager()->init(width, height);
}

void quit()
{
    PanelManager::getPanelManager()->destroy();
}

}
