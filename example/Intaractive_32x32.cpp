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
        drawCircle(tobj->getX(), tobj->getY(), 1, Palette::color("Aqua"));
    }
    
    void updateTuioObject(TuioObject *tobj) override
    {
        std::cout << "[Updated TUIO object] " << "SessionID: " << tobj->getSessionID() << ", SymoblID: " << tobj->getSymbolID() << ", X: " << tobj->getX() << ", Y: " << tobj->getY() << std::endl;
        clear();
        drawCircle(tobj->getX(), tobj->getY(), 1, Palette::color("Aqua"));
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
        init(32, 32, "HUB75", true);
        Simulation::start(CHIP);

/*
        drawLine(0, 0, 0, 31, Palette::color("Navy"));
        drawLine(3, 0, 3, 31, Palette::color("Lime"));
        drawLine(6, 0, 6, 31, Palette::color("Turquoise"));
        drawLine(9, 0, 9, 31, Palette::color("Yellow"));
        drawLine(12, 0, 12, 31, Palette::color("BlueViolet"));
        drawLine(15, 0, 15, 31, Palette::color("Brown"));
        drawLine(18, 0, 18, 31, Palette::color("Silver"));
        drawLine(21, 0, 21, 31, Palette::color("Crimson"));
        drawLine(24, 0, 24, 31, Palette::color("Aqua"));
        drawLine(27, 0, 27, 31, Palette::color("DeepPink"));
        drawLine(30, 0, 30, 31, Palette::color("White"));
*/
/*
        Image img = loadImage("./example/image/Arrow2.png");
        img.resize(32, 32);
        img.draw(0, 0);
*/

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
