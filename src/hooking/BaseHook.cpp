#include "BaseHook.hpp"

namespace NewBase
{
    BaseHook::BaseHook(const std::string_view name) :
        m_Name(name),
        m_Enabled(false)
    {
    }
}