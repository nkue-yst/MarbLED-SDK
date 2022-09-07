/**
 * @file tllEngine.cpp
 * @author Y.Nakaue
 */

#include "tllEngine.hpp"

#include <cstddef>

#include "Common.hpp"
#include "Event.hpp"
#include "PanelManager.hpp"
#include "SerialManager.hpp"
#include "TextRenderer.hpp"

namespace tll
{

    tllEngine::tllEngine()
    {
        printLog("Create Engine instance");
    }

    tllEngine::~tllEngine()
    {
        printLog("Destroy Engine instance");
    }

    void tllEngine::init(uint16_t width, uint16_t height, std::string LED_driver)
    {
        TLL_ENGINE(PanelManager)->init(width, height);
        TLL_ENGINE(SerialManager)->init(LED_driver);
        TLL_ENGINE(TextRenderer)->init();
        TLL_ENGINE(EventHandler)->init();

    }

    void tllEngine::run()
    {

    }

    namespace component
    {
        template<size_t N, class T>
        static void release(T&& t)
        {
            std::get<N>(t).release();

            if constexpr (N > 0)
            {
                release<N - 1>(t);
            }
        }

        template<class T>
        static void releaseAll(T&& t)
        {
            return release<std::tuple_size_v<std::remove_reference_t<T>> - 1>(std::forward<T>(t));
        }
    }

    void tllEngine::quit()
    {
        component::releaseAll(this->components_);
    }

}
