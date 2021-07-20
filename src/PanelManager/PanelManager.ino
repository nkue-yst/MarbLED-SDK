/**
 * @file PanelManager.ino
 * @brief LEDの更新処理を行うメイン処理部
 * @author Yoshito Nakaue
 * @date 2021/07/19
 */

#include "Panel_8x8.hpp"
#include "Panel_8x16.hpp"

//Panel_8x8 panel = Panel_8x8();
Panel_8x16 panel = Panel_8x16();

void setup()
{
    Serial.begin(115200);

    panel.init();
}

void loop()
{
    panel.update();
}
