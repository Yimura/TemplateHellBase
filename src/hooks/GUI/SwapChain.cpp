#include "hooking/VMTHook.hpp"
#include "hooks/Hooks.hpp"

namespace NewBase
{
	HRESULT SwapChain::Present(IDXGISwapChain* that, UINT syncInterval, UINT flags)
	{
		return BaseHook::Get<SwapChain::Present, VMTHook<SwapChain::VMTSize>>()->Original<decltype(&Present)>(SwapChain::VMTPresentIdx)(that, syncInterval, flags);
	}

	HRESULT SwapChain::ResizeBuffers(IDXGISwapChain* that, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags)
	{
		LOG(VERBOSE) << "Buffers have been resized";

		return BaseHook::Get<SwapChain::Present, VMTHook<SwapChain::VMTSize>>()->Original<decltype(&ResizeBuffers)>(SwapChain::VMTResizeBuffersIdx)(that, bufferCount, width, height, newFormat, swapChainFlags);
	}
}