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
        std::cout << "Added TUIO object." << " ( ";
        std::cout << "ID: " << tobj->getSymbolID() << ", ";
        std::cout << "X: "  << tobj->getX() << ", ";
        std::cout << "Y: "  << tobj->getY() << " )" << std::endl;
    }
    void updateTuioObject(TuioObject *tobj) override {}
    void removeTuioObject(TuioObject *tobj) override {}

	void addTuioCursor(TuioCursor *tcur) override {}
	void updateTuioCursor(TuioCursor *tcur) override {}
	void removeTuioCursor(TuioCursor *tcur) override {}
	
	void addTuioBlob(TuioBlob *tblb) override {}
	void updateTuioBlob(TuioBlob *tblb) override {}
	void removeTuioBlob(TuioBlob *tblb) override {}

    void refresh(TuioTime ftime) override {}

    void run()
    {
        init(24, 16);
        Simulation::start();

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
