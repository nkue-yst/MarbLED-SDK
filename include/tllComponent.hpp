/**
 * @file tllComponent.hpp
 * @author Y.Nakaue
 */

#ifndef __TLL_COMPONENT_HPP__
#define __TLL_COMPONENT_HPP__

namespace tll
{

    template<class T>
    class tllComponent
    {
    private:
        inline static T* pComponent = nullptr;

    public:
        [[nodiscard]]
        T* get()
        {
            if (!this->pComponent)
            {
                this->pComponent = T::create();
            }
            
            return this->pComponent;
        }

        void release()
        {
            delete this->pComponent;
            this->pComponent = nullptr;
        }
    };

}

#endif
