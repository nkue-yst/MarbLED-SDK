#pragma once
#include <iostream>

#define emptyFuncError std::cout << __FILE__ << "#" << __LINE__ << " " << __PRETTY_FUNCTION__ << "  --> 実装されていない関数です." << std::endl

class AppBase
{
public:
    AppBase() {}
    virtual ~AppBase() {}

    /* Common */
    virtual void run() = 0;

    /* Music visualizer */
    virtual void beatNotified() { emptyFuncError; }
    virtual void receiveValue() { emptyFuncError; }

    /* test */
    virtual void test() { emptyFuncError; }

    bool is_running = false;    // run()の終了判定
};
