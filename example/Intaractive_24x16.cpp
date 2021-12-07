/**
 * @file    Intaractive_24x16.cpp
 * @brief   ---
 * @author  Yoshito Nakaue
 * @date    2021/12/08
 */

#include "TLL.h"
#include <TuioListener.h>
#include <TuioClient.h>

using namespace tll;
using namespace TUIO2;

class MyTuioListener : public TuioListener
{
public:
    MyTuioListener()
    {};

    void tuioAdd(TuioObject *tobj) override {}
    void tuioUpdate(TuioObject *tobj) override {}
    void tuioRemove(TuioObject *tobj) override {}
    void tuioRefresh(TuioTime ftime) override {}
};

int main()
{
    MyTuioListener* listener = new MyTuioListener();
    TuioClient* client = new TuioClient();
    client->addTuioListener(listener);
    client->connect();

    init(24, 16);
    Simulation::start();

/*
    while (loop())
    {
    }
*/

    Simulation::quit();
    quit();
}