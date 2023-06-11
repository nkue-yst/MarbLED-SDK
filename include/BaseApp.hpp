#pragma once

#include "TLL.h"
#include "AppInterface.hpp"

#include <TuioListener.h>
#include <UdpReceiver.h>
#include <TuioClient.h>

#include <iostream>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <vector>
#include <unordered_map>
#include <memory>

namespace tll
{
    /* アプリを動作させるためのアプリクラス */
    class BaseApp : public TUIO::TuioListener
    {
    public:
        BaseApp();
        ~BaseApp();

        void addTuioObject(TUIO::TuioObject *tobj) override
        {
            if (this->is_home_)
            {
                int32_t x = static_cast<int32_t>(tobj->getX());
                int32_t y = static_cast<int32_t>(tobj->getY());

                if (8 <= y && y <= 22)
                {
                    this->icon_pressed[0] = ( 3 <= x && x <= 17);
                    this->icon_pressed[1] = (24 <= x && x <= 38);
                    this->icon_pressed[2] = (45 <= x && x <= 59);
                }

                return;
            }

            if (this->running_app)
            {
                this->running_app->onTouched(
                    TouchInfo{
                        static_cast<uint32_t>(tobj->getSymbolID()),
                        static_cast<int32_t>(tobj->getX()),
                        static_cast<int32_t>(tobj->getY())
                    }
                );
            }
        }

        void updateTuioObject(TUIO::TuioObject *tobj) override
        {
            if (this->is_home_)
            {
                int32_t x = static_cast<int32_t>(tobj->getX());
                int32_t y = static_cast<int32_t>(tobj->getY());

                if (8 <= y && y <= 22)
                {
                    this->icon_pressed[0] = ( 3 <= x && x <= 17);
                    this->icon_pressed[1] = (24 <= x && x <= 38);
                    this->icon_pressed[2] = (45 <= x && x <= 59);
                }
                else
                {
                    for (int i = 0; i < 3; i++)
                        this->icon_pressed[i] = false;
                }

                return;
            }

            if (this->running_app)
            {
                this->running_app->onMoved(
                    TouchInfo{
                        static_cast<uint32_t>(tobj->getSymbolID()),
                        static_cast<int32_t>(tobj->getX()),
                        static_cast<int32_t>(tobj->getY())
                    }
                );
            }
        }

        void removeTuioObject(TUIO::TuioObject *tobj) override
        {
            if (this->is_home_)
            {
                int32_t x = static_cast<int32_t>(tobj->getX());
                int32_t y = static_cast<int32_t>(tobj->getY());

                if (8 <= y && y <= 22)
                {
                    if (3 <= x && x <= 17)
                    {
                        this->is_playing_anim = 0;
                    }
                    else
                    {
                        this->icon_pressed[0] = false;
                    }

                    if (24 <= x && x <= 38)
                    {
                        this->is_playing_anim = 1;
                    }
                    else
                    {
                        this->icon_pressed[1] = false;
                    }

                    if (45 <= x && x <= 59)
                    {
                        this->is_playing_anim = 2;
                    }
                    else
                    {
                        this->icon_pressed[2] = false;
                    }
                }
                else
                {
                    for (int i = 0; i < 3; i++)
                        this->icon_pressed[i] = false;
                }

                return;
            }

            if (this->running_app)
            {
                this->running_app->onReleased(
                    TouchInfo
                    {
                        static_cast<uint32_t>(tobj->getSymbolID()),
                        static_cast<int32_t>(tobj->getX()),
                        static_cast<int32_t>(tobj->getY())
                    }
                );
            }
        }

        void addTuioCursor(TUIO::TuioCursor *tcur) override {}
        void updateTuioCursor(TUIO::TuioCursor *tcur) override {}
        void removeTuioCursor(TUIO::TuioCursor *tcur) override {}
        
        void addTuioBlob(TUIO::TuioBlob *tblb) override
        {
            this->running_app->addBlob(
                BlobInfo
                {
                    static_cast<uint32_t>(tblb->getBlobID()),
                    static_cast<int32_t>(tblb->getX()),
                    static_cast<int32_t>(tblb->getY()),
                    static_cast<int32_t>(tblb->getWidth()),
                    static_cast<int32_t>(tblb->getHeight())
                }
            );
        }

        void updateTuioBlob(TUIO::TuioBlob *tblb) override
        {
            this->running_app->moveBlob(
                BlobInfo
                {
                    static_cast<uint32_t>(tblb->getBlobID()),
                    static_cast<int32_t>(tblb->getX()),
                    static_cast<int32_t>(tblb->getY()),
                    static_cast<int32_t>(tblb->getWidth()),
                    static_cast<int32_t>(tblb->getHeight())
                }
            );
        }

        void removeTuioBlob(TUIO::TuioBlob *tblb) override
        {
            this->running_app->removeBlob(
                BlobInfo
                {
                    static_cast<uint32_t>(tblb->getBlobID()),
                    static_cast<int32_t>(tblb->getX()),
                    static_cast<int32_t>(tblb->getY()),
                    static_cast<int32_t>(tblb->getWidth()),
                    static_cast<int32_t>(tblb->getHeight())
                }
            );
        }

        void refresh(TUIO::TuioTime ftime) override {}

        void run();
        bool switchApp(const std::string app_name);

        AppInterface* getRunningApp() { return this->running_app.get(); }

    private:
        uint32_t loadApps();

        // 読み込んだ（アプリ名 - DLL）のリスト
        std::unordered_map<std::string, void*> app_list;

        std::unique_ptr<class AppInterface> running_app;

        TUIO::TuioClient* tuio_client;
        TUIO::OscReceiver* osc_receiver;

        bool is_home_;            // ホーム画面の表示判定用
        tll::Image* icon_img;     // ホーム画面用画像データ

        bool icon_pressed[3] = { false, false, false };

        bool back_to_home_flag = false;
        std::chrono::system_clock::time_point back_to_home_tp;

        // アニメーション用フラグ
        int8_t is_playing_anim = -1;
    };

}

namespace PiSoundPlayer
{
    // 効果音再生
    void playSound(std::string file);

    // 効果音の音量設定
    void setSoundVolume(int32_t new_volume);

    // BGM再生
    void playBGM(std::string file);

    // BGM一時停止
    void pauseBGM();

    // BGM再開
    void resumeBGM();

    // BGM停止
    void stopBGM();

    // BGMの音量設定
    void setBgmVolume(int32_t new_volume);
}
