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

#define SOUND_PLAYER_PI_IP "192.168.0.222"

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
        this->home_img_ = tll::loadImage("HomeIcons.png");
        this->home_img_->resize(32, 64);
    }

    BaseApp::~BaseApp()
    {
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
            // ホーム画面の表示
            if (this->is_home_)
            {
                this->home_img_->draw(0, 0);
                continue;
            }

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

namespace PiSoundPlayer
{
    // 効果音再生
    void playSound(std::string file)
    {
        tll::OscHandler::sendMessageWithString("/PiSoundPlayer/se/play", file, SOUND_PLAYER_PI_IP, 44100);
    }

    // 効果音の音量設定
    void setSoundVolume(int32_t new_volume)
    {
        tll::OscHandler::sendMessageWithInt32("/PiSoundPlayer/se/volume", new_volume, SOUND_PLAYER_PI_IP, 44100);
    }

    // BGM再生
    void playBGM(std::string file)
    {
        tll::OscHandler::sendMessageWithString("/PiSoundPlayer/bgm/play", file, SOUND_PLAYER_PI_IP, 44100);
    }

    // BGM一時停止
    void pauseBGM()
    {
        tll::OscHandler::sendMessage("/PiSoundPlayer/bgm/pause", SOUND_PLAYER_PI_IP, 44100);
    }

    // BGM再開
    void resumeBGM()
    {
        tll::OscHandler::sendMessage("/PiSoundPlayer/bgm/resume", SOUND_PLAYER_PI_IP, 44100);
    }

    // BGM停止
    void stopBGM()
    {
        tll::OscHandler::sendMessage("/PiSoundPlayer/bgm/stop", SOUND_PLAYER_PI_IP, 44100);
    }

    // BGMの音量設定
    void setBgmVolume(int32_t new_volume)
    {
        tll::OscHandler::sendMessageWithInt32("/PiSoundPlayer/bgm/volume", new_volume, SOUND_PLAYER_PI_IP, 44100);
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
