/**
 * @file PanelManager.ino
 * @brief LEDの更新処理を行うメイン処理部
 * @author Yoshito Nakaue
 * @date 2021/07/05
 */

#include "Panel_8x8.hpp"

Panel_8x8 panel = Panel_8x8();

void setup()
{
    Serial.begin(115200);
    
    panel.begin(0x70);
}

void loop()
{
    panel.update();
    delay(500);
}
