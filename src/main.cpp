#include "common.hpp"

namespace NewBase
{
    DWORD Main(void*)
    {
        while (g_Running)
        {
            std::this_thread::sleep_for(100ms);
        }

        CloseHandle(g_MainThread);
        FreeLibraryAndExitThread(g_DllInstance, EXIT_SUCCESS);

        return EXIT_SUCCESS;
    }
}

BOOL WINAPI DllMain(HINSTANCE dllInstance, DWORD reason, void*)
{
    using namespace NewBase;

    DisableThreadLibraryCalls(dllInstance);

    if (reason == DLL_PROCESS_ATTACH)
    {
        g_DllInstance = dllInstance;

        g_MainThread = CreateThread(nullptr, 0, Main, nullptr, 0, &g_MainThreadId);
    }
    return true;
}