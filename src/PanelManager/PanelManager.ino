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
}

void loop()
{
    // unsigned long start = micros();
    
    panel.update();

    /* 処理時間出力 */
    // Serial.print(micros() - start);
    // Serial.println(" μs");
    
    delay(10000);
}
