/**
 * @file    SerialManager.hpp
 * @brief   Class to manage serial communication.
 * @author  Yoshito Nakaue
 * @date    2022/08/18
 */

#ifndef SERIAL_MANAGER_HPP
#define SERIAL_MANAGER_HPP

#ifdef WITH_RASPI
#include "led-matrix.h"
#endif

#include <string>

namespace tll
{

    /**
     * @brief  Class to manage serial communication.
     */
    class SerialManager
    {
    public:
        /**
         * @fn      static SerialManager* getInstance()
         * @brief   SerialManagerクラスのインスタンスを取得
         * @return  SerialManagerクラスのインスタンス
         */
        static SerialManager* getInstance()
        {
            return pInstance_;
        }

        /**
         * @fn     static void create()
         * @brief  インスタンスを作成
         */
        static void create();

        /**
         * @fn     static void destroy()
         * @brief  インスタンスを破棄
         */
        static void destroy();

        /**
         * @fn     void init()
         * @brief  Open serial device.
         */
        void init(std::string LED_driver);

        /**
         * @fn     void quit()
         * @brief  Close serial device.
         */
        void quit();

        /**
         * @fn     void sendColorData()
         * @brief  Send color information for all pixels.
         */
        void sendColorData();

        bool send_ready = true;

    protected:
        SerialManager()
        : system_mode(0)
        {};

        /// SerialManagerクラスインスタンス
        static SerialManager* pInstance_;

    private:
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

}

#endif
