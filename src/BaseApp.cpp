#include "BaseApp.hpp"
#include "AppInterface.hpp"

#include <algorithm>
#include <dlfcn.h>
#include <filesystem>

#include "ip/UdpSocket.h"
#include "ip/IpEndpointName.h"

namespace tll
{

    static const std::string extention =
        #ifdef __APPLE__
        ".dylib";
        #elif __linux__
        ".so";
        #endif

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
        init(64, 32, "HUB75", false);

        auto dirs = std::filesystem::directory_iterator(std::filesystem::path("./app"));
        for (auto& dir : dirs)
        {
            std::string path = dir.path().string();

            // アプリファイルを検索する
            if (path.find(extention.c_str()) != std::string::npos)
            {
                this->app_list[path] = dir.path().stem().string();
            }
        }

        // 全てのアプリを一度読み込んで破棄する（テスト用）
        std::for_each(this->app_list.begin(), this->app_list.end(), [](std::unordered_map<std::string, std::string>::value_type app)
        {
            void* app_handle = dlopen(app.first.c_str(), RTLD_LAZY);
            auto createApp = (createAppFunc*)(dlsym(app_handle, "create"));

            {
                const auto& app_instance = createApp();
            }

            dlclose(app_handle);
        });

        while (loop())
        {

        }

        quit();
    }

}

int main(int argc, char** argv)
{
    tll::BaseApp* base_app = new tll::BaseApp();

    base_app->run();

    delete base_app;
}
