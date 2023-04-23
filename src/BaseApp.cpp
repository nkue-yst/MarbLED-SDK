#include "BaseApp.hpp"

#include <algorithm>
#include <chrono>
#include <dlfcn.h>
#include <filesystem>
#include <thread>

#include <cstdio>
#include <fcntl.h>
#include <iostream>
#include <termios.h>
#include <unistd.h>

#include "AppInterface.hpp"
#include "OscHandler.hpp"

#include "ip/UdpSocket.h"
#include "ip/IpEndpointName.h"

namespace
{
    bool with_osc = true;
}

namespace tll
{

    namespace
    {
        const std::string extention =
            #ifdef __APPLE__
            ".dylib";
            #elif __linux__
            ".so";
            #endif
    }

    BaseApp::BaseApp()
        : is_home_(true)
    {
        this->osc_receiver = new TUIO::UdpReceiver();
        this->tuio_client  = new TUIO::TuioClient(this->osc_receiver);
        this->tuio_client->addTuioListener(this);
        this->tuio_client->connect();

        // ホーム画面用画像ファイルの読み込み
        this->icon_img = tll::loadImage("image/IconBase.png");

        tll::OscHandler::sendMessage("/tll/init", "192.168.0.100", 3333);
    }

    BaseApp::~BaseApp()
    {
        tll::OscHandler::sendMessage("/tll/terminate", "192.168.0.100", 3333);
        this->tuio_client->disconnect();
        delete this->tuio_client;
        delete this->osc_receiver;
    }

    void BaseApp::run()
    {
        init(64, 32, "HUB75");

        this->loadApps();

        while (loop())
        {
            static uint32_t count = 0;    // アニメーション用カウンタ

            std::this_thread::sleep_for(std::chrono::milliseconds(33));

            // ホーム画面の表示
            if (this->is_home_)
            {
                clear();
                this->icon_img->draw( 3, 8, (!this->icon_pressed[0] ? tll::Color(255,   0,   0) : tll::Color(100,   0,   0)));
                this->icon_img->draw(24, 8, (!this->icon_pressed[1] ? tll::Color(  0, 255,   0) : tll::Color(  0, 100,   0)));
                this->icon_img->draw(45, 8, (!this->icon_pressed[2] ? tll::Color(  0, 128, 255) : tll::Color(  0,   0, 100)));

                // 開始時アニメーション処理
                if (this->is_playing_anim != -1)
                {
                    count++;

                    if (this->is_playing_anim == 0)
                    {
                        drawCircle(11, 16, count * 2, tll::Color(255, 0, 0));
                        drawCircle(11, 16, count * 2 + 1, tll::Color(255, 0, 0));
                        if (count >= 45)
                        {
                            this->switchApp("CockroachShooting");
                        }
                    }
                    else if (this->is_playing_anim == 1)
                    {
                        drawCircle(32, 16, count * 2, tll::Color(0, 255, 0));
                        drawCircle(32, 16, count * 2 + 1, tll::Color(0, 255, 0));
                        if (count >= 45)
                            this->switchApp("Theremin");
                    }
                    else if (this->is_playing_anim == 2)
                    {
                        drawCircle(53, 16, count * 2, tll::Color(0, 128, 255));
                        drawCircle(53, 16, count * 2 + 1, tll::Color(0, 128, 255));
                        if (count >= 45)
                            this->switchApp("ADIR01P_Light");
                    }

                    if (count >= 45)
                    {
                        this->is_playing_anim = -1;
                        for (int i = 0; i < 3; i++)
                            this->icon_pressed[i] = false;
                        count = 0;
                    }
                }

                continue;
            }

            // 起動中アプリケーションの表示など
            if (this->running_app)
            {
                // 5点タッチ
                if (getTouchedNum() == 5)
                {
                    if (!this->back_to_home_flag)
                    {
                        this->back_to_home_flag = true;
                        this->back_to_home_tp = std::chrono::system_clock::now();
                        continue;
                    }

                    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
                    double elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - this->back_to_home_tp).count();
                    
                    if (elapsed >= 3.f)
                    {
                        OscHandler::sendMessageWithString("/tll/switch", "home", "127.0.0.1", 44101);
                    }
                }
                else if (this->back_to_home_flag)
                {
                    this->back_to_home_flag = false;
                }

                this->running_app->run();
            }
        }

        if (this->running_app)
            this->running_app->terminate();
        quit();
    }

    bool BaseApp::switchApp(std::string app_name)
    {
        bool is_found = false;

        if (this->running_app)
        {
            this->running_app->terminate();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            this->running_app.reset();
        }

        if (app_name == "home")
        {
            this->is_home_ = true;
            is_found = true;

            clear();
        }

        std::for_each(this->app_list.begin(), this->app_list.end(), [this, app_name, &is_found](std::unordered_map<std::string, void*>::value_type app)
        {
            if (app.first == app_name)
            {
                createApp* createAppFunc = (createApp*)(dlsym(this->app_list.find(app_name)->second, "create"));
                std::unique_ptr<class AppInterface> app = createAppFunc();
                this->running_app = std::move(app);

                clear();
                this->running_app->init();

                this->is_home_ = false;

                is_found = true;
            }
        });

        return is_found;
    }

    uint32_t BaseApp::loadApps()
    {
        uint32_t app_num = 0;

        std::cout << "[Loaded applications]" << std::endl;

        auto dirs = std::filesystem::directory_iterator(std::filesystem::path("./app"));
        for (auto& dir : dirs)
        {
            std::string path = dir.path().string();

            // アプリファイルを検索し、ロードする
            if (path.find(extention.c_str()) != std::string::npos)
            {
                std::string app_file_name = dir.path().stem().string();        // 拡張子を削除
                std::string app_name = app_file_name.substr(3);                // 先頭の"lib"を削除
                this->app_list[app_name] = dlopen(path.c_str(), RTLD_LAZY);    // DLLを読み込む

                std::cout << " - " << app_name << std::endl;

                app_num++;    // 読み込んだアプリ数をカウント
            }
        }
        std::cout << std::endl;
        
        return app_num;
    }

}

int main(int argc, char** argv)
{
    if (argc > 1)
    {
        if (strcmp(argv[1], "--without-osc") == 0) with_osc = false;
    }

    tll::BaseApp* base_app = new tll::BaseApp();

    if (with_osc)
    {
        std::thread thread_osc(tll::runOscReceiveThread, base_app);
        thread_osc.detach();
    }

    base_app->run();

    delete base_app;
}
