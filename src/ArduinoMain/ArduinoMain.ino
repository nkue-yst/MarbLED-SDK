/**
 * @file PanelManager.ino
 * @brief LEDの更新処理を行うメイン処理部
 * @author Yoshito Nakaue
 * @date 2021/09/22
 */

#include "Panel_8x8.hpp"
#include "Panel_8x16.hpp"
#include "Panel_24x16.hpp"

//Panel_8x8 panel = Panel_8x8();
//Panel_8x16 panel = Panel_8x16();
Panel_24x16 panel = Panel_24x16();

void setup()
{
    Serial.begin(115200);

    panel.init(0x70);
}

void loop()
{
    panel.update();
}
