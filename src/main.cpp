#include "common.hpp"
#include "pointers/Pointers.hpp"
#include "hooking/Hooking.hpp"

namespace NewBase
{
    DWORD Main(void*)
    {
        LogHelper::Init("henlo", "./cout.log");

        Pointers.Init();
        Hooking::Init();

        while (g_Running && !GetAsyncKeyState(VK_DELETE))
        {
            std::this_thread::sleep_for(100ms);
        }

        Hooking::Destroy();
        LogHelper::Destroy();

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