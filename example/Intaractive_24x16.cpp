/**
 * @file    Intaractive_24x16.cpp
 * @brief   ---
 * @author  Yoshito Nakaue
 * @date    2021/12/08
 */

#include <unistd.h>

#include "TLL.h"
#include <TuioListener.h>
#include <UdpReceiver.h>
#include <TuioClient.h>

using namespace tll;
using namespace TUIO;

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

    void addTuioObject(TuioObject *tobj) override
    {
        std::cout << "[Added TUIO object]   " << "SessionID: " << tobj->getSessionID() << ", SymoblID: " << tobj->getSymbolID() << ", X: " << tobj->getX() << ", Y: " << tobj->getY() << std::endl;
        drawCircle(tobj->getX(), tobj->getY(), 1, Palette::color("White"));
    }
    
    void updateTuioObject(TuioObject *tobj) override
    {
        std::cout << "[Updated TUIO object] " << "SessionID: " << tobj->getSessionID() << ", SymoblID: " << tobj->getSymbolID() << ", X: " << tobj->getX() << ", Y: " << tobj->getY() << std::endl;
        clear();
        drawCircle(tobj->getX(), tobj->getY(), 1, Palette::color("White"));
    }
    
    void removeTuioObject(TuioObject *tobj) override
    {
        std::cout << "[Removed TUIO object] " << "SessionID: " << tobj->getSessionID() << ", SymoblID: " << tobj->getSymbolID() << ", X: " << tobj->getX() << ", Y: " << tobj->getY() << std::endl;
        clear();
    }

    void addTuioCursor(TuioCursor *tcur) override {}
    void updateTuioCursor(TuioCursor *tcur) override {}
    void removeTuioCursor(TuioCursor *tcur) override {}
    
    void addTuioBlob(TuioBlob *tblb) override {}
    void updateTuioBlob(TuioBlob *tblb) override {}
    void removeTuioBlob(TuioBlob *tblb) override {}

    void refresh(TuioTime ftime) override {}

    void run()
    {
        init(24, 16, true);
        Simulation::start();

        while (loop())
        {
        }

        Simulation::quit();
        quit();
    }

private:
    TuioClient* client;
    OscReceiver* receiver;
};

int main()
{
    App* app = new App();

    app->run();

    delete app;
}
