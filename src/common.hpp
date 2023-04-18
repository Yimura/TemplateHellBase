#pragma once

#include <Windows.h>

#include <atomic>

namespace NewBase
{
    extern std::atomic<bool> g_Running;
    extern HINSTANCE g_DllInstance;
    extern HANDLE g_MainThread;
    extern DWORD g_MainThreadId;
}