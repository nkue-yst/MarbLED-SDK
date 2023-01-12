/**
 * @file tllEngine.hpp
 * @author Y.Nakaue
 */

#ifndef __TLL_ENGINE_HPP__
#define __TLL_ENGINE_HPP__

#include <memory>
#include <string>
#include <tuple>

#include "tllComponent.hpp"

namespace tll
{

    class IEventHandler;
    class IPanelManager;
    class ISerialManager;
    class ITextRenderer;

    class tllEngine
    {
    private:
        inline static std::unique_ptr<tllEngine> pInstance_ = nullptr;

    public:
        tllEngine();
        ~tllEngine();

        void init(uint16_t width, uint16_t height, std::string LED_driver);
        void run();
        void quit();

        static tllEngine* get()
        {
            if (!tllEngine::pInstance_)
            {
                tllEngine::pInstance_ = std::make_unique<tllEngine>();
            }

            return tllEngine::pInstance_.get();
        }

        template<class T>
        static auto* getComponent()
        {
            return std::get<tllComponent<T>>(tllEngine::pInstance_->components_).get();
        }
        #define TLL_ENGINE(COMPONENT) tllEngine::getComponent<I##COMPONENT>()

    private:
        std::tuple<
            tllComponent<IEventHandler>,
            tllComponent<IPanelManager>,
            tllComponent<ISerialManager>,
            tllComponent<ITextRenderer>
        > components_;

        bool initialized_;
    };

}

#endif
