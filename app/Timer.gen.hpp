/********************************************
 ** This file is generated by AppGenerator **
 ********************************************/

#pragma once

#include "AppInterface.hpp"
#include "TLL.h"

#include <chrono>
#include <cstdint>
#include <memory>
#include <vector>

class Timer : public tll::AppInterface
{
public:
    Timer();
    ~Timer();

    void drawArc(int percent);

    void init() override;
    void run() override;
    void terminate() override;

    void onTouched(uint32_t x, uint32_t y) override;
    void onMoved(uint32_t x, uint32_t y) override;
    void onReleased() override;

    void procOscMessage(const osc::ReceivedMessage& msg) override;

private:
    // 円弧画像のリスト
    std::vector<class tll::Image*> arc_img_list;

    // 設定する時間（秒）
    uint32_t set_time;

    // タイマー開始からの経過時間（秒）
    uint32_t elapsed_time;

    std::chrono::system_clock::time_point pre_tp, now_tp;
};

/* Required to use in loading application file */
extern "C"
{
    std::unique_ptr<tll::AppInterface> create()
    {
        return std::unique_ptr<tll::AppInterface>(new Timer);
    }
}
