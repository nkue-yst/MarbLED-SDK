/********************************************
 ** This file is generated by AppGenerator **
 ********************************************/

#include "CockroachShooting.gen.hpp"

#include <cstdlib>
#include <cmath>
#include <thread>
#include <iostream>
#include <random>
#include <vector>

#include "BaseApp.hpp"

#define PLAYING_TIME 60.f     // プレイ時間（sec）
#define MAX_G_SPEED 2         // Gの最高速度（pixel/frame）
#define MAX_LEVEL 5           // 最大レベル
#define NUMBER_OF_G 3         // Gの同時出現数
#define SHOOT_THRESHOLD 15.f  // 攻撃が当たる距離
#define CHARGE_VALUE 2        // 1フレームあたりのチャージ量（n/100）
#define FRAME_DELAY 33        // 1フレームあたりのディレイ（ms）（フレームレート設定）
#define RESULT_DURATION 5.f   // 結果画面の表示時間（sec）

#define COCKROACH_COLOR tll::Color(200, 0, 0)
#define RETICLE_COLOR tll::Color(128, 255, 128)

static std::random_device rnd;

Cockroach::Cockroach(int16_t x, int16_t y, int16_t vx, int16_t vy)
    : x(x)
    , y(y)
    , vx(vx)
    , vy(vy)
{

}

void Cockroach::move(int32_t level)
{
    if (this->frame++ % (MAX_LEVEL - level + 1) != 0)
        return;

    if (this->frame == UINT64_MAX)
        this->frame = 0;

    // 横方向への移動
    this->x += this->vx;

    if (this->x < 0) this->x = 0;
    if (this->x > 61) this->x = 61;

    if (this->x == 0 || 61 == this->x)
    {
        this->vx = -((this->vx > 0) - (this->vx < 0)) * (rnd() % MAX_G_SPEED + 1);
    }

    // 縦方向への移動
    this->y += this->vy;

    if (this->y < 0) this->y = 0;
    if (this->y > 31) this->y = 31;

    if (this->y == 0 || 31 == this->y)
    {
        this->vy = -((this->vy > 0) - (this->vy < 0)) * (rnd() % MAX_G_SPEED + 1);
    }
}

void Cockroach::draw()
{
    uint16_t w = 4;
    uint16_t h = 3;

    tll::drawRect(this->x - 2, this->y - 2, w, h, COCKROACH_COLOR);
    tll::drawPixel(this->x + 2, this->y - 1, COCKROACH_COLOR);
    tll::drawPixel(this->x - 3, this->y - 1, COCKROACH_COLOR);
    tll::drawPixel(this->x + 1, this->y - 3, COCKROACH_COLOR);
    tll::drawPixel(this->x + 1, this->y + 1, COCKROACH_COLOR);   
    tll::drawPixel(this->x - 3, this->y - 3, COCKROACH_COLOR);
    tll::drawPixel(this->x - 3, this->y + 1, COCKROACH_COLOR); 
    tll::drawPixel(this->x - 1, this->y - 3, COCKROACH_COLOR);
    tll::drawPixel(this->x - 1, this->y + 1, COCKROACH_COLOR);
}

CockroachShooting::CockroachShooting()
    : score(50)
    , game_state(GameState::TITLE)
    , level(0)
    , charge(100)
    , playing_shoot_anim(false)
{
    std::cout << "Create CockroachShooting instance." << std::endl;
}

CockroachShooting::~CockroachShooting()
{
    for (auto cockroach : this->cockroach)
    {
        delete cockroach;
        cockroach = nullptr;
    }

    delete this->button_start;

    std::cout << "Delete CockroachShooting instance." << std::endl;
}

void CockroachShooting::init()
{
    this->button_start = tll::loadImage("Button_Start.jpg");
    this->button_start->resize(32, 64);

    //PiSoundPlayer::playSound("start.wav");
    tll::OscHandler::sendMessage("/tll/app/G-Shooter/init", "192.168.0.100", 3333);
}

void CockroachShooting::run()
{
    tll::clear();

    switch (this->game_state)
    {
    // タイトル画面
    case TITLE:
        // タイトル画面表示
        button_start->draw(0, 0, (tll::getTouchedNum() == 0 ? tll::Color(0, 200, 255) : tll::Color(0, 128, 128)));
        break;

    // ゲームプレイ中
    case IN_GAME:
        // プレイ時間を記録
        this->now = std::chrono::system_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(now - this->start).count() > PLAYING_TIME)
        {
            this->game_state = FINISHED;
            //PiSoundPlayer::playSound("end.wav");
            tll::OscHandler::sendMessage("/tll/app/G-Shooter/end", "192.168.0.100", 3333);
            this->start = std::chrono::system_clock::now();
            break;
        }

        // G のスポーン処理
        if (this->cockroach.size() < NUMBER_OF_G)
        {
            auto sign = []()
            {
                return rnd() / RAND_MAX * 2 - 1;
            };

            this->cockroach.push_back(new Cockroach(rnd() % 31, rnd() % 63, (rnd() % MAX_G_SPEED + 1) * sign(), (rnd() % MAX_G_SPEED + 1) * sign()));
        }

        // G の位置を更新
        for (auto cockroach : this->cockroach)
            cockroach->move(this->level);

        // G の描画
        for (auto cockroach : this->cockroach)
            cockroach->draw();

        // チャージ状態の更新
        if (this->charge < 100)
        {
            this->charge += CHARGE_VALUE;

            if (this->charge >= 100)
            {
                //PiSoundPlayer::playSound("charge.wav");
                tll::OscHandler::sendMessage("/tll/app/G-Shooter/charge", "192.168.0.100", 3333);
            }
        }
        tll::drawRect(61, 32 - (float)this->charge / 100 * 32, 3, 32, tll::Palette::Aqua);

        // 3点タッチされている場合、円の中心を描画
        if (tll::getTouchedNum() >= 3)
        //if (tll::getTouchedNum() == 1)
        {
            //this->drawReticle(0, 0, 0, 31, 63, 31);
            this->drawReticle(
                this->points[0].x, this->points[0].y,
                this->points[1].x, this->points[1].y,
                this->points[2].x, this->points[2].y
            );

            if (this->charge >= 100)    // 射撃可能な場合射撃
            {
                this->shoot();
            }
        }

        // アニメーションの再生処理呼び出し
        if (this->playing_shoot_anim)
            this->playShootAnim();

        break;
        
    case FINISHED:
        this->now = std::chrono::system_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(now - this->start).count() > RESULT_DURATION)
        {
            this->game_state = TITLE;
            break;
        }

        tll::print(std::to_string(this->score), tll::Palette::White);
        break;

    default:
        break;
    }
}

void CockroachShooting::terminate()
{
    tll::OscHandler::sendMessage("/tll/app/G-Shooter/terminate", "192.168.0.100", 3333);
}

void CockroachShooting::onTouched(tll::TouchInfo ti)
{
    if (0 <= ti.id && ti.id < 3)
    {
        this->points[ti.id] = ti;
    }
}

void CockroachShooting::onMoved(tll::TouchInfo ti)
{
    if (0 <= ti.id && ti.id < 3)
    {
        this->points[ti.id] = ti;
    }
}

void CockroachShooting::onReleased(tll::TouchInfo ti)
{
    // ゲーム開始
    if (this->game_state == TITLE)
    {
        this->start = std::chrono::system_clock::now();
        this->game_state = IN_GAME;

        //PiSoundPlayer::playSound("start.wav");
        tll::OscHandler::sendMessage("/tll/app/G-Shooter/start", "192.168.0.100", 3333);

        // ゲームを初期化
        this->score = 0;
        this->level = 1;
        this->charge = 100;
        this->cockroach.clear();
    }

    if (0 <= ti.id && ti.id < 3)
    {
        this->points[ti.id] = ti;
    }
}

void CockroachShooting::drawReticle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3)
{
    bool stat = false;

    int64_t cx = 0;
    int64_t cy = 0;

    int64_t a = (int64_t)x2 - x1;
    int64_t b = (int64_t)y2 - y1;
    int64_t c = (int64_t)x3 - x1;
    int64_t d = (int64_t)y3 - y1;

    if ((a && d) || (b && c))
    {
        cx = x1 + (d * (a * a + b * b) - b * (c * c + d * d)) / (a * d - b * c) / 2;
        
        if (b)
        {
            cy = (a * (x1 + x2 - cx - cx) + b * (y1 + y2)) / b / 2;
        }
        else if (d)
        {
            cy = (c * (x1 + x3 - cx - cx) + d * (y1 + y3)) / d / 2;
        }
    }

    tll::drawCircle(cx, cy, 4, RETICLE_COLOR);

    tll::drawLine( 0,  0, cx - 2, cy - 2, RETICLE_COLOR);
    tll::drawLine(60,  0, cx + 2, cy - 2, RETICLE_COLOR);
    tll::drawLine( 0, 31, cx - 2, cy + 2, RETICLE_COLOR);
    tll::drawLine(60, 31, cx + 2, cy + 2, RETICLE_COLOR);

    // 射撃アニメーション開始時の座標を記録したい
    if (!this->playing_shoot_anim)
    {
        this->cx = cx;
        this->cy = cy;
    }
}

void CockroachShooting::shoot()
{
    this->charge = 0;
    this->playing_shoot_anim = true;

    //PiSoundPlayer::playSound("shoot.wav");
    tll::OscHandler::sendMessage("/tll/app/G-Shooter/shoot", "192.168.0.100", 3333);
}

void CockroachShooting::playShootAnim()
{
    static uint32_t count = 0;
    
    tll::drawCircle(this->cx, this->cy, 46 - count, tll::Color(128, 255, 255));
    tll::drawCircle(this->cx, this->cy, 45 - count, tll::Color(128, 255, 255));

    count += 5;
    if (count == 45)
    {
        if (this->checkSuccess())
        {
            score += 10;

            if ((score % 30 == 0) && (this->level < MAX_LEVEL))
            {
                level++;
            }
        }
        else
        {
        }

        count = 0;
        this->playing_shoot_anim = false;
    }
}

bool CockroachShooting::checkSuccess()
{
    // G との距離が一定範囲内か調べる
    for (auto iter = this->cockroach.begin(); iter != this->cockroach.end(); iter++)
    {
        int16_t dx = (*iter)->x - this->cx;
        int16_t dy = (*iter)->y - this->cy;

        double distance = std::sqrt(dx * dx + dy * dy);

        //std::cout << distance << std::endl;

        if (distance < SHOOT_THRESHOLD)
        {
            //PiSoundPlayer::playSound("success.wav");
            tll::OscHandler::sendMessage("/tll/app/G-Shooter/hit", "192.168.0.100", 3333);
            this->cockroach.erase(iter);
            return true;
        }
    }

    return false;
}
