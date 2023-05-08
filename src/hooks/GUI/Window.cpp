#include "hooking/DetourHook.hpp"
#include "hooks/Hooks.hpp"
#include "renderer/Renderer.hpp"

namespace NewBase
{
	LRESULT Window::WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
	{
		if (g_Running)
			Renderer::WndProc(hwnd, umsg, wparam, lparam);

		if (umsg == WM_KEYUP && wparam == VK_DELETE) // fallback to unload
			g_Running = false;

		return BaseHook::Get<Window::WndProc, DetourHook<WNDPROC, WNDPROC>>()->Original<WNDPROC>()(hwnd, umsg, wparam, lparam);
	}
}