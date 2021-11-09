/**
 * @file ArduinoMain.ino
 * @brief LEDの更新処理を行うメイン処理部
 * @author Yoshito Nakaue
 * @date 2021/11/09
 */

#include "HT16K33_24x16.hpp"

HT16K33_24x16 panel = HT16K33_24x16();

void setup()
{
    Serial.begin(115200);

    panel.init(0x70);
}

void loop()
{
    panel.update();
}
