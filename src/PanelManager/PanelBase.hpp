/**
 * @file PanelBase.hpp
 * @brief LEDパネルの基底クラス
 * @author Yoshito Nakaue
 * @date 2021/07/05
 */

#include <vector>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

class PanelBase : public Adafruit_LEDBackpack, public GFXcanvas1
{
public:
    PanelBase(uint16_t width, uint16_t height);

    void update();

protected:
    int calcX(int x) { return x; }
    int calcY(int y) { return (y + 1) % height_; }
    
    std::vector<int> color_data_;
    uint16_t width_;
    uint16_t height_;
};
