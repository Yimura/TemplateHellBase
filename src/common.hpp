#pragma once

#include <Windows.h>

#include <atomic>
#include <chrono>
#include <thread>

#include <array>

#include <cstddef>
#include <string_view>

namespace NewBase
{
    using namespace std::chrono_literals;

    extern std::atomic<bool> g_Running;
    extern HINSTANCE g_DllInstance;
    extern HANDLE g_MainThread;
    extern DWORD g_MainThreadId;
}