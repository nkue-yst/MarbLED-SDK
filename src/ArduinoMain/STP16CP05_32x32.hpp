/**
 * @file STP16CP05_32x32.hpp
 * @brief 32x32サイズのLEDパネルクラス
 * @author Yoshito Nakaue
 * @date 2021/11/09
 */

#ifndef STP16CP05_32X32_HPP
#define STP16CP05_32X32_HPP

#include "STP16CP05_Base.hpp"

/**
 * @brief  32x32サイズのLEDパネルクラス
 */
class STP16CP05_32x32 : public STP16CP05_Base
{
public:
    /**
     * @brief  32x32すべてがLEDのパネルとして初期化
     */
    STP16CP05_32x32();

private:
    /**
     * @brief  32x32すべてがLEDとしてチップ情報を登録
     */
    void registerMatrixInfo() override;
};

#endif
