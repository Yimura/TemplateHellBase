#include "common.hpp"
#include "memory/Pattern.hpp"

namespace NewBase
{
    DWORD Main(void*)
    {
        LogHelper::Init("henlo", "./cout.log");

        constexpr auto pat = Pattern("Henlo", "48 ?? FF ?? 55");
        pat.Signature();

        LOG(INFO) << "Test log!";

        while (g_Running && !GetAsyncKeyState(VK_DELETE))
        {
            std::this_thread::sleep_for(100ms);
        }

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