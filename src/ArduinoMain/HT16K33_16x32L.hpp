/**
 */

#ifndef HT16K33_16X32L_HPP
#define HT16K33_16X32L_HPP

#include "HT16K33_Base.hpp"

/**
 * @brief  
 */
class HT16K33_16x32L : public HT16K33_Base
{
public:
    /**
     * @brief  
     */
    HT16K33_16x32L();

private:
    /**
     * @brief  
     */
    void registerMatrixInfo() override;
};

#endif
