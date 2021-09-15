/**
 * @file    Color.hpp
 * @brief   Color information class
 * @author  Yoshito Nakaue
 * @date    2021/09/28
 */

#ifndef COLOR_HPP
#define COLOR_HPP

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace tll
{

    /**
     * @brief  Color information
     */
    class Color
    {
    public:
        Color(std::string color_name, uint16_t r, uint16_t g, uint16_t b)
        {
            color_name_ = color_name;
            r_ = r;
            g_ = g;
            b_ = b;
        }

        Color(uint16_t r, uint16_t g, uint16_t b)
        {
            color_name_ = "";
            r_ = r;
            g_ = g;
            b_ = b;
        }

        std::string color_name_;

        uint16_t r_;
        uint16_t g_;
        uint16_t b_;
    };

    /**
     * @brief  ColorPalette
     */
    class ColorPalette
    {
    public:
        /**
         * @fn      static ColorPalette* getInstance()
         * @brief   Get instance for singleton.
         * @return  Instance of color palette
         */
        static ColorPalette* getInstance()
        {
            return pInstance_;
        }

        /** 
         * @fn     static void create()
         * @brief  Create instance.
         */
        static void create();

        /**
         * @fn     static void destroy()
         * @brief  Destroy instance.
         */
        static void destroy();

        /**
         * @fn     void addColor(Color color)
         * @brief  Add color data.
         */
        void addColor(Color color);

        /**
         * @fn      uint8_t getID(std::string color_name)
         * @brief   Get color ID from name.
         * @param   color_name  Target color name
         * @return  Target color's ID
         */
        uint8_t getIDFromName(std::string color_name);

        /**
         * @fn      Color getColor(uint8_t color_id)
         * @brief   Get color data from ID
         * @param   Target color ID
         * @return  Target color data
         */
        Color getColorFromID(uint8_t color_id);

        /**
         * 
         */
        uint8_t getIDFromRGB(uint16_t r, uint16_t g, uint16_t b);

    protected:
        ColorPalette() {}

        /// Instance for singleton
        static ColorPalette* pInstance_;

    private:
        /// Color palette data
        std::vector<Color> palette_data_;    
    };

}

#endif
