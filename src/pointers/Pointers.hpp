#pragma once
#include <d3d11.h>
#include <windows.h>

namespace NewBase
{
    struct PointerData
    {
        IDXGISwapChain** SwapChain;
        WNDPROC WndProc;
    };

    struct Pointers : PointerData
	{
		bool Init();
	};

    inline NewBase::Pointers Pointers;
}