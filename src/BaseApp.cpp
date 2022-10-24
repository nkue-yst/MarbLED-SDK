#include "BaseApp.hpp"

#include <algorithm>
#include <chrono>
#include <dlfcn.h>
#include <filesystem>
#include <thread>

#include "AppInterface.hpp"
#include "OscHandler.hpp"

#include "ip/UdpSocket.h"
#include "ip/IpEndpointName.h"

#include "SDL.h"
#include "SDL_mixer.h"

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
    {
        this->osc_receiver = new TUIO::UdpReceiver();
        this->tuio_client  = new TUIO::TuioClient(this->osc_receiver);
        this->tuio_client->addTuioListener(this);
        this->tuio_client->connect();
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

        if (with_sound)
        {
            if (SDL_Init(SDL_INIT_AUDIO) < 0)
            {
                std::cout << "Failed to init audio system: " << SDL_GetError() << std::endl;
                return;
            }

            if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
            {
                std::cout << "Failed to open audio device: " << SDL_GetError() << std::endl;
                return;
            }
        }

        this->loadApps();
        this->switchApp("CockroachShooting");

        while (loop())
        {
            if (this->running_app)
            {
                this->running_app->run();
            }
        }

        if (this->running_app)
            this->running_app->terminate();
        quit();

        SDL_Quit();
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

    void playSound(const char* file)
    {
        Mix_Chunk* wave = nullptr;
        wave = Mix_LoadWAV(file);

        if (with_sound)
        {
            if (Mix_PlayChannel(-1, wave, 0) == -1)
            {
                std::cout << "Failed to play wav" << std::endl;
            }
        }
    }

}

int main(int argc, char** argv)
{
    if (argc > 1)
    {
        if (strcmp(argv[1], "--without-osc") == 0) with_osc = false;
        if (strcmp(argv[1], "--without-sound") == 0) tll::with_sound = false;
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
