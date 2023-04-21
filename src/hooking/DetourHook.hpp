#pragma once
#include "BaseHook.hpp"

#include <MinHook.h>
#include <string_view>

namespace NewBase
{
	template<typename T = int, typename D = int>
	class DetourHook : public BaseHook
	{
	private:
		void* m_TargetFunc;
		void* m_DetourFunc;
		void* m_OriginalFunc;

	public:
		DetourHook(const std::string_view name, T* target, D* detour);
		virtual ~DetourHook();

		bool Enable();
		bool Disable();

		bool EnableNow();
		bool DisableNow();

		template<typename Func>
		Func Original() const;

    private:
        static void OptimizeHook() {};

	};

	template<typename T, typename D>
	inline DetourHook<T, D>::DetourHook(const std::string_view name, T* target, D* detour) :
        BaseHook(name),
        m_TargetFunc(target),
        m_DetourFunc(detour),
        m_OriginalFunc(nullptr)
	{
        OptimizeHook();

        if (const auto result = MH_CreateHook(m_TargetFunc, m_DetourFunc, &m_OriginalFunc); result != MH_OK)
		{
			throw std::runtime_error("Failed to create hook!");
		}
	}

	template<typename T, typename D>
	inline DetourHook<T, D>::~DetourHook()
	{
		DisableNow();
	}
	
	template<typename T, typename D>
	inline bool DetourHook<T, D>::Enable()
	{
		if (m_Enabled)
			return false;

		if (const auto result = MH_QueueEnableHook(m_TargetFunc); result != MH_OK)
		{
			throw std::runtime_error("Failed to queue hook to be enabled.");

			return false;
		}
		return true;
	}
	
	template<typename T, typename D>
	inline bool DetourHook<T, D>::Disable()
	{
		if (!m_Enabled)
			return false;

		if (const auto result = MH_QueueDisableHook(m_TargetFunc); result != MH_OK)
		{
			throw std::runtime_error("Failed to queue hook to be disable.");

			return false;
		}
		return true;
	}
	
	template<typename T, typename D>
	inline bool DetourHook<T, D>::EnableNow()
	{
		if (m_Enabled)
			return false;
		
		if (const auto result = MH_EnableHook(m_TargetFunc); result != MH_OK)
		{
			throw std::runtime_error("Failed to enable hook right now.");

			return false;
		}
		return true;
	}

	template<typename T, typename D>
	inline bool DetourHook<T, D>::DisableNow()
	{
		if (!m_Enabled)
			return false;
		
		if (const auto result = MH_DisableHook(m_TargetFunc); result != MH_OK)
		{
			throw std::runtime_error("Failed to disable hook right now.");

			return false;
		}
		return true;
	}

	template<typename T, typename D>
	template<typename Func>
	inline Func DetourHook<T, D>::Original() const
	{
		return reinterpret_cast<Func>(m_OriginalFunc);
	}
}