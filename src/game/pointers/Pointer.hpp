#pragma once

namespace NewBase
{
    template<typename T>
    concept IsPointer = std::is_pointer_v<T>;

    template<typename T>
    requires IsPointer<T>
    class Pointer
    {
    private:
        T m_Ptr;

    public:
        Pointer(T ptr) :
            m_Ptr(ptr)
        {

        }

        T Get() const
        {
            return m_Ptr;
        }

    };
}