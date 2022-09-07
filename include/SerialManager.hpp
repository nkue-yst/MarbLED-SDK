/**
 * @file    SerialManager.hpp
 * @brief   Class to manage serial communication.
 * @author  Yoshito Nakaue
 * @date    2022/08/18
 */

#ifndef __SERIAL_MANAGER_HPP__
#define __SERIAL_MANAGER_HPP__

#include <string>

#ifdef WITH_RASPI
#include "led-matrix.h"
#endif

namespace tll
{

    /* 通信関連インターフェースクラス */
    class ISerialManager
    {
    public:
        virtual ~ISerialManager() = default;

        // インスタンスを作成
        static ISerialManager* create();

        // 通信管理クラスを初期化
        virtual void init(std::string LED_driver) = 0;

        // 色情報を送信する
        virtual void sendColorData() = 0;

        bool send_ready = true;

    protected:
        /// System mode (0:LED and Simulation, 1:Only Simulation)
        int system_mode;

        /// LED driver name
        std::string led_driver_;

        #ifdef WITH_RASPI
        /// File descriptor
        int fd;

        /* For HUB75 panel */
        /// Default canvas
        class rgb_matrix::RGBMatrix* matrix_;

        /// Canvas for duble buffering
        class rgb_matrix::FrameCanvas* off_canvas_;
        #endif
    };

    /* 通信関連クラス */
    class SerialManager : public ISerialManager
    {
    public:
        SerialManager() noexcept;
        ~SerialManager() noexcept override;

        // 通信管理クラスを初期化
        void init(std::string LED_driver) override;

        // 色情報を送信する
        void sendColorData() override;
    };

}

#endif
