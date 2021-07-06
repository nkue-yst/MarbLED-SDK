/**
 * @file PanelManager.ino
 * @brief LEDの更新処理を行うメイン処理部
 * @author Yoshito Nakaue
 * @date 2021/07/05
 */

#include "PanelBase.hpp"

PanelBase panel = PanelBase(8, 8);

void setup()
{
    Serial.begin(115200);
    
    panel.begin(0x70);
    panel.setRotation(3);
}

void loop()
{
    panel.update();
    delay(500);
}
