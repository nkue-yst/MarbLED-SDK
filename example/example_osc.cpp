/**
 * @file    example_osc.cpp
 * @brief   ---
 * @author  Yoshito Nakaue
 * @date    2022/07/05
 */

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
#include "ip/UdpSocket.h"
#include "ip/IpEndpointName.h"

using namespace tll;
using namespace TUIO;

class OscReceiverComponent : public osc::OscPacketListener
{
public:
    OscReceiverComponent() {}
    ~OscReceiverComponent() {}

protected:
    virtual void ProcessMessage(const osc::ReceivedMessage& msg, const IpEndpointName& remote_end_pt) override
    {
        (void)remote_end_pt;
        try
        {
            std::cout << "Received osc message" << std::endl;
            osc::ReceivedMessageArgumentStream args = msg.ArgumentStream();
            osc::ReceivedMessage::const_iterator arg = msg.ArgumentsBegin();

            if (strcmp(msg.AddressPattern(), "/example/notify") == 0)
            {
                std::cout << "/example/notify" << std::endl;
            }
        }
        catch (osc::Exception& e)
        {
            std::cout << "OSC error" << std::endl;
        }
    }
};

void runOscReceivingThread()
{
    // Initialize socket for osc
    OscReceiverComponent osc_receiver;
    UdpListeningReceiveSocket osc_sock(IpEndpointName(IpEndpointName::ANY_ADDRESS, 44101), &osc_receiver);
    osc_sock.Run();
}

class App : public TuioListener
{
public:
    App()
    {
        this->receiver = new UdpReceiver();
        this->client   = new TuioClient(this->receiver);
        this->client->addTuioListener(this);
        this->client->connect();
    };

    void addTuioObject(TuioObject *tobj) override {}
    void updateTuioObject(TuioObject *tobj) override {}
    void removeTuioObject(TuioObject *tobj) override {}

    void addTuioCursor(TuioCursor *tcur) override {}
    void updateTuioCursor(TuioCursor *tcur) override {}
    void removeTuioCursor(TuioCursor *tcur) override {}
    
    void addTuioBlob(TuioBlob *tblb) override {}
    void updateTuioBlob(TuioBlob *tblb) override {}
    void removeTuioBlob(TuioBlob *tblb) override {}

    void refresh(TuioTime ftime) override {}

    virtual void run()
    {
        init(64, 32, "HUB75", false);

        while (loop())
        {
        }

        quit();
    }

private:
    TuioClient* client;
    OscReceiver* receiver;
};


int main()
{
    App* app = new App();

    std::thread th_osc_recv(runOscReceivingThread);
    th_osc_recv.detach();

    app->run();
    delete app;
}
