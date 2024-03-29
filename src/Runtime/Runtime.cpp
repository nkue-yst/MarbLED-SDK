#include "Runtime.h"

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

    AppManager::AppManager()
    {
        this->osc_receiver = new TUIO::UdpReceiver();
        this->tuio_client  = new TUIO::TuioClient(this->osc_receiver);
        this->tuio_client->addTuioListener(this);
        this->tuio_client->connect();

        tll::OscHandler::sendMessage("/tll/init", "192.168.0.100", 3333);
    }

    AppManager::~AppManager()
    {
        tll::OscHandler::sendMessage("/tll/terminate", "192.168.0.100", 3333);
        this->tuio_client->disconnect();
        delete this->tuio_client;
        delete this->osc_receiver;
    }

    void AppManager::run()
    {
        init(64, 32, "HUB75");

        this->loadApps();
        this->switchApp("Rain");

        while (loop())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(33));

            // 起動中アプリケーションの表示など
            if (this->running_app)
            {
                this->running_app->run();
            }
        }

        if (this->running_app)
            this->running_app->terminate();
        quit();
    }

    bool AppManager::switchApp(std::string app_name)
    {
        bool is_found = false;

        if (this->running_app)
        {
            this->running_app->terminate();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            this->running_app.reset();
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

                is_found = true;
            }
        });

        return is_found;
    }

    uint32_t AppManager::loadApps()
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

    tll::AppManager* app_manager = new tll::AppManager();

    if (with_osc)
    {
        std::thread thread_osc(tll::runOscReceiveThread, app_manager);
        thread_osc.detach();
    }

    app_manager->run();

    delete app_manager;
}