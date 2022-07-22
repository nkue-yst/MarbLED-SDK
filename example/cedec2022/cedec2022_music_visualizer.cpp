/**
 * @file    cedec2022_music_visualizer.cpp
 * @brief   ---
 * @author  Yoshito Nakaue
 * @date    2022/07/13
 */

#include "cedec2022_music_visualizer.hpp"

#define BEAT_OFFSET 200    // 円が動ききるまでの時間（ms）

void MusicVisualizer::run()
{
    sendOscMessage("/tll/app/music_visualizer/init");
    this->is_running = true;

    while (loop())
    {
        if (!this->is_running)
            break;
    }

    sendOscMessage("/tll/app/music_visualizer/terminate");
}

void MusicVisualizer::beatNotified()
{
    std::chrono::system_clock::time_point notified_tp = std::chrono::system_clock::now();

    double elapse = std::chrono::duration_cast<std::chrono::milliseconds>(notified_tp - this->pre_tp).count();
    double elapse_ave = (this->pre_pre_elapse + this->pre_elapse + elapse) / 3.f;

    std::cout << elapse_ave - BEAT_OFFSET << "ms後に円を動かす" << std::endl;

    this->pre_pre_tp = this->pre_tp;
    this->pre_tp = notified_tp;

    this->pre_pre_elapse = this->pre_elapse;
    this->pre_elapse = elapse;
}

void MusicVisualizer::receiveValue()
{
    AppBase::receiveValue();
}
