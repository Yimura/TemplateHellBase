#pragma once

#include <Windows.h>

#include <filesystem>
#include <fstream>
#include <iostream>

#include <atomic>
#include <chrono>
#include <memory>
#include <thread>

#include <array>

#include <cstddef>
#include <string_view>

#include <AsyncLogger/Logger.hpp>
using namespace al;

#include "logger/LogHelper.hpp"


namespace NewBase
{
    using namespace std::chrono_literals;

    extern std::atomic<bool> g_Running;
    extern HINSTANCE g_DllInstance;
    extern HANDLE g_MainThread;
    extern DWORD g_MainThreadId;
}