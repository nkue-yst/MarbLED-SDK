/**
 * @file    Event.hpp
 * @brief   Event handling
 * @author  Yoshito Nakaue
 * @date    2021/08/28
 */

#ifndef __EVENT_HPP__
#define __EVENT_HPP__

#include "TLL.h"

#include <cstdint>
#include <functional>
#include <vector>
#include <thread>
#include <map>
#include <mutex>

#include "tllEngine.hpp"

#include "TuioServer.h"
#include "UdpSender.h"

#include "osc/OscReceivedElements.h"
#include "osc/OscPacketListener.h"
#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"
#include "ip/IpEndpointName.h"

namespace tll
{

    /* タッチイベント管理インターフェースクラス */
    class IEventHandler
    {
    public:
        virtual ~IEventHandler() = default;

        // イベントハンドラを作成
        static IEventHandler* create();

        // イベントハンドラを初期化
        virtual void init() = 0;

        // タッチ状態を最新情報に更新する
        virtual void updateState() = 0;

        // タッチ点が追加された際の処理
        virtual void addTouchedPoint(uint32_t id, int32_t x, int32_t y) = 0;

        // タッチ点が移動した際の処理
        virtual void updateTouchedPoint(uint32_t id, int32_t x, int32_t y) = 0;

        // タッチ点が削除された際の処理
        virtual void removeTouchedPoint(uint32_t id) = 0;

        // タッチ領域が追加された際の処理
        virtual void addTouchedBlob(uint32_t id, int32_t x, int32_t y, int32_t w, int32_t h) = 0;

        // タッチ領域が移動した際の処理
        virtual void updateTouchedBlob(uint32_t id, int32_t x, int32_t y, int32_t w, int32_t h) = 0;

        // タッチ領域が削除された際の処理
        virtual void removeTouchedBlob(uint32_t id) = 0;

        // タッチ点の数を返す
        virtual uint32_t getTouchedNum() = 0;

        // 終了フラグの状態を取得
        bool getQuitFlag() { return quit_flag_; }

        // 終了フラグを更新｀
        void setQuitFlag(bool new_flag) { quit_flag_ = new_flag; }

    private:
        /// Quit flag
        bool quit_flag_ = false;
    };

    /* タッチイベント管理クラス（TUIO使用） */
    class EventHandlerTuio : public IEventHandler
    {
    public:
        EventHandlerTuio() noexcept;
        ~EventHandlerTuio() noexcept override;

        // イベントハンドラを初期化
        void init() override;

        // タッチ状態を最新情報に更新する
        void updateState() override;

        // タッチ点が追加された際の処理
        void addTouchedPoint(uint32_t id, int32_t x, int32_t y) override;

        // タッチ点が移動した際の処理
        void updateTouchedPoint(uint32_t id, int32_t x, int32_t y) override;

        // タッチ点が削除された際の処理
        void removeTouchedPoint(uint32_t id) override;

        // タッチ領域が追加された際の処理
        void addTouchedBlob(uint32_t id, int32_t x, int32_t y, int32_t w, int32_t h) override;

        // タッチ領域が移動した際の処理
        void updateTouchedBlob(uint32_t id, int32_t x, int32_t y, int32_t w, int32_t h) override;

        // タッチ領域が削除された際の処理
        void removeTouchedBlob(uint32_t id) override;

        // タッチ点の数を返す
        uint32_t getTouchedNum() override;

    private:
        // キーボード入力処理
        int kbhit();

        // OscSender
        TUIO::OscSender* sender_;

        // TuioServer
        TUIO::TuioServer* server_;

        // Tuio Object（タッチ点）のリスト
        std::map<uint32_t, TUIO::TuioObject*> tobj_list_;

        // Tuio Blob（認識した領域）のリスト
        std::map<uint32_t, TUIO::TuioBlob*> tblob_list_;
    };
    
    /* タッチイベント関連のOSCメッセージ受信クラス */
    class OscReceiver : public osc::OscPacketListener
    {
    public:
        OscReceiver() {}
        ~OscReceiver() {}

    protected:
        void ProcessMessage(const osc::ReceivedMessage& msg, const IpEndpointName& remote_end_pt) override;

    private:
        // 受信したOSCメッセージをスラッシュごとに区切ったリストに分割する
        std::vector<std::string> split(const std::string msg);

        std::mutex osc_mutex_;
    };

    // タッチイベント関連のOSCメッセージをスレッドで受信し始める
    void threadListen();
}

#endif
