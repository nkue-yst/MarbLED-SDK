#pragma once

#include "TLL.h"
#include "AppInterface.hpp"

#include <TuioListener.h>
#include <UdpReceiver.h>
#include <TuioClient.h>

#include "osc/OscReceivedElements.h"
#include "osc/OscPacketListener.h"
#include "osc/OscOutboundPacketStream.h"

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
            this->running_app->onTouched((uint32_t)tobj->getX(), (uint32_t)tobj->getY());
        }

        void updateTuioObject(TUIO::TuioObject *tobj) override
        {
            this->running_app->onMoved((uint32_t)tobj->getX(), (uint32_t)tobj->getY());
        }

        void removeTuioObject(TUIO::TuioObject *tobj) override
        {
            this->running_app->onReleased();
        }

        void addTuioCursor(TUIO::TuioCursor *tcur) override {}
        void updateTuioCursor(TUIO::TuioCursor *tcur) override {}
        void removeTuioCursor(TUIO::TuioCursor *tcur) override {}
        
        void addTuioBlob(TUIO::TuioBlob *tblb) override {}
        void updateTuioBlob(TUIO::TuioBlob *tblb) override {}
        void removeTuioBlob(TUIO::TuioBlob *tblb) override {}

        void refresh(TUIO::TuioTime ftime) override {}

        virtual void run();

    private:
        uint32_t loadApps();
        void unloadApps();

        // 読み込んだ（アプリ名 - 管理に使う名前）のリスト
        std::unordered_map<std::string, std::string> app_list;

        std::unique_ptr<class AppInterface> running_app;

        std::vector<void*> dl_list;

        TUIO::TuioClient* tuio_client;
        TUIO::OscReceiver* osc_receiver;
    };

}
