/**
 * @file  TLL.h
 * @brief  API公開用ヘッダファイル
 * @author  Yoshito Nakaue
 * @date  2021/07/23
 */

#ifndef _TLL_H_
#define _TLL_H_

#include <cstdint>

/**
 * @namespace  tll
 * @brief  TouchLED-Libraryの名前空間
 */
namespace tll
{
    /**
     * @fn  void init(uint16_t width, uint16_t height)
     * @brief  システム全体の初期化
     * @param  width  パネルの横幅
     * @param  height  パネルの高さ
     */
    void init(uint16_t width, uint16_t height);

    /**
     * @fn  void quit()
     * @brief  システム全体を終了
     */
    void quit();
}

#endif
