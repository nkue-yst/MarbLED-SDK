#pragma once
#include "demo_app_base.hpp"

#include <iostream>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <vector>

#include "TLL.h"
#include <TuioListener.h>
#include <UdpReceiver.h>
#include <TuioClient.h>

#include "osc/OscReceivedElements.h"
#include "osc/OscPacketListener.h"
#include "osc/OscOutboundPacketStream.h"

using namespace tll;
using namespace TUIO;

/* CEDEC用ベースアプリ */
class CedecDemo : public TuioListener
{
public:
    CedecDemo();
    ~CedecDemo();

    void addTuioObject(TuioObject *tobj) override
    {
        this->running_app->onTouched();
    }
    void updateTuioObject(TuioObject *tobj) override
    {
        this->running_app->onMoved();
    }
    void removeTuioObject(TuioObject *tobj) override
    {
        this->running_app->onReleased();
    }

    void addTuioCursor(TuioCursor *tcur) override {}
    void updateTuioCursor(TuioCursor *tcur) override {}
    void removeTuioCursor(TuioCursor *tcur) override {}
    
    void addTuioBlob(TuioBlob *tblb) override {}
    void updateTuioBlob(TuioBlob *tblb) override {}
    void removeTuioBlob(TuioBlob *tblb) override {}

    void refresh(TuioTime ftime) override {}

    virtual void run();

    class AppBase* running_app;

private:
    TuioClient* client;
    OscReceiver* receiver;
};

/* OSCメッセージ受信クラス */
class OscHandler : public osc::OscPacketListener
{
public:
    OscHandler(class CedecDemo* app)
        :app_ref(app)
    {};
    ~OscHandler() {};

protected:
    /* 受信したメッセージのアドレスによって処理振り分け */
    virtual void ProcessMessage(const osc::ReceivedMessage& msg, const IpEndpointName& remote_end_pt) override
    {
        if (!this->app_ref)
            return;

        (void)remote_end_pt;
        try
        {
            //std::cout << "Received osc message" << std::endl;
            osc::ReceivedMessageArgumentStream args = msg.ArgumentStream();
            osc::ReceivedMessage::const_iterator arg = msg.ArgumentsBegin();
            
            this->app_ref->running_app->procMessage(msg.AddressPattern());
        }
        catch (osc::Exception& e)
        {
            std::cout << "OSC error" << std::endl;
        }
    }

    class CedecDemo* app_ref;    // ベースアプリのリファレンス
};

void runOscReceivingThread(CedecDemo* app);
