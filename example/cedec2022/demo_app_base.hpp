#pragma once

#define emptyFuncError __FILE__ << "#" << __LINE__ << " " << __PRETTY_FUNCTION__ << "  --> 実装されていない関数です."

class AppBase
{
public:
    AppBase() {}
    virtual ~AppBase() {};

    /* Common */
    template<class App>
    static App* load() { return new App(); }

    virtual void init() = 0;
    virtual void run() = 0;
    virtual void terminate() = 0;

    virtual void procMessage(const char* msg) = 0;

protected:
    bool is_running = false;    // run()の終了判定
};
