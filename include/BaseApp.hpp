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
            if (this->running_app)
            {
                this->running_app->onReleased(
                    TouchInfo{
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
        
        void addTuioBlob(TUIO::TuioBlob *tblb) override {}
        void updateTuioBlob(TUIO::TuioBlob *tblb) override {}
        void removeTuioBlob(TUIO::TuioBlob *tblb) override {}

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
