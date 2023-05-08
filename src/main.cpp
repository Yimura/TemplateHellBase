#include "common.hpp"
#include "frontend/GUI.hpp"
#include "pointers/Pointers.hpp"
#include "hooking/Hooking.hpp"
#include "renderer/Renderer.hpp"

namespace NewBase
{
    DWORD Main(void*)
    {
        LogHelper::Init("henlo", "./cout.log");

        if (!Pointers.Init())
            goto unload;
        Renderer::Init();
        GUI::Init();
        Hooking::Init();

        while (g_Running)
        {
            std::this_thread::sleep_for(100ms);
        }

unload:
        Hooking::Destroy();
        Renderer::Destroy();
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