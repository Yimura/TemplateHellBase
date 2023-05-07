#include "Pointers.hpp"

#include "memory/ModuleMgr.hpp"
#include "memory/PatternScanner.hpp"
#include "util/Joaat.hpp"

namespace NewBase
{
	bool Pointers::Init()
	{
		auto mgr = ModuleMgr();
		mgr.LoadModules();

		auto scanner = PatternScanner(mgr.Get("GTA5.exe"_J));

		constexpr auto swapchainPtrn = Pattern<"48 8B 0D ? ? ? ? 48 85 C9 0F 84 02 02 00 00">("IDXGISwapChain");
		scanner.Add(swapchainPtrn, [this](PointerCalculator ptr) {
			SwapChain = ptr.Add(3).Rip().As<IDXGISwapChain**>();
		});

		constexpr auto wndProcPtrn = Pattern<"48 8B C4 48 89 58 08 4C 89 48 20 55 56 57 41 54 41 55 41 56 41 57 48 8D 68 A1 48 81 EC F0">("WNDPROC");
		scanner.Add(wndProcPtrn, [this](PointerCalculator ptr) {
			WndProc = ptr.As<WNDPROC>();
		});

		scanner.Scan();

		return true;
	}
}