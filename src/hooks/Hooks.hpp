#pragma once
#include <d3d11.h>

namespace NewBase
{
    namespace SwapChain
    {
        constexpr auto VMTPresentIdx = 8;
        constexpr auto VMTResizeBuffersIdx = 13;
        constexpr auto VMTSize = 19;
        HRESULT Present(IDXGISwapChain* that, UINT syncInterval, UINT flags);
        HRESULT ResizeBuffers(IDXGISwapChain* that, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags);
    }
}