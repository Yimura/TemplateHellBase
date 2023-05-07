#include "Hooking.hpp"
#include "BaseHook.hpp"

namespace NewBase
{
	Hooking::Hooking()
	{

	}

	Hooking::~Hooking()
	{
        DestroyImpl();
	}

	bool Hooking::Init()
	{
		return GetInstance().InitImpl();
	}

	void Hooking::Destroy()
	{
        GetInstance().DestroyImpl();
	}

	bool Hooking::InitImpl()
	{
        BaseHook::EnableAll();
        m_MinHook.ApplyQueued();

		return true;
	}

	void Hooking::DestroyImpl()
	{
        BaseHook::DisableAll();
        m_MinHook.ApplyQueued();
	}
}