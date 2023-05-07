#include "BaseHook.hpp"
#include <MinHook.h>

namespace NewBase
{
    BaseHook::BaseHook(const std::string_view name) :
        m_Name(name),
        m_Enabled(false)
    {
        m_Hooks.emplace_back(this);
    }

	void BaseHook::EnableAll()
	{
        for (auto hook : m_Hooks)
        {
            hook->Enable();
        }
	}

	void BaseHook::DisableAll()
	{
        for (auto hook : m_Hooks)
        {
            hook->Disable();
        }
	}
}