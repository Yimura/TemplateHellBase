#include "common.hpp"

namespace NewBase
{
    DWORD Main(void*)
    {


        CloseHandle(g_MainThread);
        FreeLibraryAndExitThread(g_DllInstance, EXIT_SUCCESS);

        return EXIT_SUCCESS;
    }
}

BOOL WINAPI DllMain(
    HINSTANCE dllInstance,  // handle to DLL module
    DWORD reason,     // reason for calling function
    void*)  // reserved
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