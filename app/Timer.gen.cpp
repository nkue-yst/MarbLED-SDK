/********************************************
 ** This file is generated by AppGenerator **
 ********************************************/

#include "Timer.gen.hpp"

#include <iostream>

void Timer::drawArc(int percent)
{
    tll::clear();

    if (    100 >= percent && percent > 95) this->arc_img_list.at(0)->draw(16, 0, this->color);
    else if (95 >= percent && percent > 90) this->arc_img_list.at(1)->draw(16, 0, this->color);
    else if (90 >= percent && percent > 85) this->arc_img_list.at(2)->draw(16, 0, this->color);
    else if (85 >= percent && percent > 80) this->arc_img_list.at(3)->draw(16, 0, this->color);
    else if (80 >= percent && percent > 75) this->arc_img_list.at(4)->draw(16, 0, this->color);
    else if (75 >= percent && percent > 70) this->arc_img_list.at(5)->draw(16, 0, this->color);
    else if (70 >= percent && percent > 65) this->arc_img_list.at(6)->draw(16, 0, this->color);
    else if (65 >= percent && percent > 60) this->arc_img_list.at(7)->draw(16, 0, this->color);
    else if (60 >= percent && percent > 55) this->arc_img_list.at(8)->draw(16, 0, this->color);
    else if (55 >= percent && percent > 50) this->arc_img_list.at(9)->draw(16, 0, this->color);
    else if (50 >= percent && percent > 45) this->arc_img_list.at(10)->draw(16, 0, this->color);
    else if (45 >= percent && percent > 40) this->arc_img_list.at(11)->draw(16, 0, this->color);
    else if (40 >= percent && percent > 35) this->arc_img_list.at(12)->draw(16, 0, this->color);
    else if (35 >= percent && percent > 30) this->arc_img_list.at(13)->draw(16, 0, this->color);
    else if (30 >= percent && percent > 25) this->arc_img_list.at(14)->draw(16, 0, this->color);
    else if (25 >= percent && percent > 20) this->arc_img_list.at(15)->draw(16, 0, this->color);
    else if (20 >= percent && percent > 15) this->arc_img_list.at(16)->draw(16, 0, this->color);
    else if (15 >= percent && percent > 10) this->arc_img_list.at(17)->draw(16, 0, this->color);
    else if (10 >= percent && percent >  5) this->arc_img_list.at(18)->draw(16, 0, this->color);
    else if ( 5 >= percent && percent >  0) this->arc_img_list.at(19)->draw(16, 0, this->color);
    else                                    this->arc_img_list.at(20)->draw(16, 0, this->color);
}

Timer::Timer()
    : set_time(0)
    , elapsed_time(0)
    , color(tll::Color(255, 255, 255))
{
    std::cout << "Create Timer instance." << std::endl;
}

Timer::~Timer()
{
    for (auto img : this->arc_img_list)
    {
        delete img;
    }

    std::cout << "Delete Timer instance." << std::endl;
}

void Timer::init()
{
    this->is_running = true;

    tll::clear();

    // 円弧画像の読み込み
    this->arc_img_list.push_back(tll::loadImage("./app/Timer100.png"));
    this->arc_img_list.push_back(tll::loadImage("./app/Timer095.png"));
    this->arc_img_list.push_back(tll::loadImage("./app/Timer090.png"));
    this->arc_img_list.push_back(tll::loadImage("./app/Timer085.png"));
    this->arc_img_list.push_back(tll::loadImage("./app/Timer080.png"));
    this->arc_img_list.push_back(tll::loadImage("./app/Timer075.png"));
    this->arc_img_list.push_back(tll::loadImage("./app/Timer070.png"));
    this->arc_img_list.push_back(tll::loadImage("./app/Timer065.png"));
    this->arc_img_list.push_back(tll::loadImage("./app/Timer060.png"));
    this->arc_img_list.push_back(tll::loadImage("./app/Timer055.png"));
    this->arc_img_list.push_back(tll::loadImage("./app/Timer050.png"));
    this->arc_img_list.push_back(tll::loadImage("./app/Timer045.png"));
    this->arc_img_list.push_back(tll::loadImage("./app/Timer040.png"));
    this->arc_img_list.push_back(tll::loadImage("./app/Timer035.png"));
    this->arc_img_list.push_back(tll::loadImage("./app/Timer030.png"));
    this->arc_img_list.push_back(tll::loadImage("./app/Timer025.png"));
    this->arc_img_list.push_back(tll::loadImage("./app/Timer020.png"));
    this->arc_img_list.push_back(tll::loadImage("./app/Timer015.png"));
    this->arc_img_list.push_back(tll::loadImage("./app/Timer010.png"));
    this->arc_img_list.push_back(tll::loadImage("./app/Timer005.png"));
    this->arc_img_list.push_back(tll::loadImage("./app/Timer000.png"));

    // 全ての円弧画像をリサイズ
    for (auto img : this->arc_img_list)
        img->resize(32, 32);
}

void Timer::run()
{
    while (tll::loop())
    {
        if (!this->is_running)
            return;
        
        // タイマーがセットされていなければ何もしない
        if (this->set_time == 0)
            continue;

        this->now_tp = std::chrono::system_clock::now();

        // 1秒以上経過していれば記録
        if (std::chrono::duration_cast<std::chrono::milliseconds>(this->now_tp - this->pre_tp).count() >= 1000)
        {
            this->elapsed_time++;

            // タイムポイントの更新
            this->pre_tp = this->now_tp;
        }
        else
        {
            continue;
        }

        // 設定時間と経過時間が一致した場合（設定時間が経過した際）
        if (elapsed_time == this->set_time)
        {
            this->drawArc(0);

            tll::OscHandler::sendMessage("/tll/app/Timer/end_notify");

            this->elapsed_time = 0;
            this->set_time     = 0;
        }
        else    // 経過時間から設定時間のうち何%残っているかを計算し描画更新
        {
            float percent = (float)this->elapsed_time / this->set_time * 100;
            this->drawArc(100 - (int)percent);
        }
    }
}

void Timer::terminate()
{
    this->is_running = false;
}

void Timer::onTouched(tll::TouchInfo ti)
{

}

void Timer::onMoved(tll::TouchInfo ti)
{

}

void Timer::onReleased(tll::TouchInfo ti)
{

}

void Timer::procOscMessage(const osc::ReceivedMessage& msg)
{
    if (strcmp(msg.AddressPattern(), "/tll/app/Timer/set") == 0)
    {
        this->set_time = msg.ArgumentsBegin()->AsInt32();
        this->elapsed_time = 0;

        this->now_tp = std::chrono::system_clock::now();
        this->pre_tp = this->now_tp;

        this->drawArc(100);
    }
}
