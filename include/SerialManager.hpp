/**
 * @file    SerialManager.hpp
 * @brief   Class to manage serial communication.
 * @author  Yoshito Nakaue
 * @date    2021/07/27
 */

#ifndef SERIAL_MANAGER_HPP
#define SERIAL_MANAGER_HPP

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
        void init();

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

    protected:
        SerialManager() {};

        /// SerialManagerクラスインスタンス
        static SerialManager* pInstance_;

    private:
        /**
         * @fn
         * @brief
         * @param
         * @return
         */
        

        /// File descriptor
        int fd;
    };

}

#endif
