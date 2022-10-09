#include "skpch.h"
#include "Win32Window.h"

#include "Sakura/Window.h"
#include "Sakura/Events/WindowEvents.h"

namespace Sakura
{
	std::shared_ptr<Window> Window::Create(const WindowSpecification& spec)
	{
		return std::make_unique<Win32Window>(spec);
	}

	Sakura::Win32Window::Win32Window(const WindowSpecification& spec)
		: m_Spec(spec)
	{
		HMODULE instance = GetModuleHandle(NULL);

		WNDCLASSA wndClass = { };
		wndClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
		wndClass.lpfnWndProc = WindowCallbackSetup;
		wndClass.hInstance = instance;
		wndClass.lpszClassName = "WindowClass"; //Need to change this to be diferent for every instance on window

		RegisterClassA(&wndClass);

		RECT ClientRect = { };
		ClientRect.left = 0;
		ClientRect.right = m_Spec.Width;
		ClientRect.top = 0;
		ClientRect.bottom = m_Spec.Height;
		AdjustWindowRect(&ClientRect, WS_OVERLAPPEDWINDOW | WS_VISIBLE, FALSE);

		m_Handle = CreateWindowExA(0, wndClass.lpszClassName, m_Spec.Title.c_str(),
			WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			CW_USEDEFAULT, CW_USEDEFAULT,
			ClientRect.right - ClientRect.left,
			ClientRect.bottom - ClientRect.top,
			0, 0, instance, this);

		ShowWindow(m_Handle, SW_SHOWDEFAULT);

		RendererContextSpecification rendererSpec = { };
		rendererSpec.WindowHandle = m_Handle;
		rendererSpec.Width = m_Spec.Width;
		rendererSpec.Height = m_Spec.Height;

		m_Context = RendererContext::Create(rendererSpec);
	}

	Sakura::Win32Window::~Win32Window()
	{
	}

	void Sakura::Win32Window::OnUpdate()
	{
		MSG Message;
		while (PeekMessageA(&Message, 0, 0, 0, PM_REMOVE))
		{
			if (Message.message == WM_QUIT)
			{
				WindowCloseEvent e;
				m_Spec.EventCallback(e);
			}

			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
	}

	LRESULT Sakura::Win32Window::WindowCallback(HWND Window, UINT Message, WPARAM wParam, LPARAM lParam)
	{
		LRESULT result = 0;

		switch (Message)
		{
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			result = 0;
		} break;

		case WM_SIZE:
		{
			m_Spec.Width  = (uint32)LOWORD(lParam);
			m_Spec.Height = (uint32)HIWORD(lParam);

			//if (m_Context != nullptr && wParam != SIZE_MINIMIZED)
			//	m_Context->ResizeViewport(m_Spec.Width, m_Spec.Height);

			// Later we need to decide what to do when the window is minimized
			//if (m_EventCallback != nullptr && wParam != SIZE_MINIMIZED)
			//{
			//	WindowResizeEvent e(m_Width, m_Height);
			//	m_EventCallback(e);
			//}
		} break;

		default:
		{
			result = DefWindowProcA(Window, Message, wParam, lParam);
		} break;
		}

		return result;
	}

	LRESULT Sakura::Win32Window::WindowCallbackSetup(HWND Window, UINT Message, WPARAM wParam, LPARAM lParam)
	{
		if (Message == WM_NCCREATE)
		{
			const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
			Win32Window* const pWnd = static_cast<Win32Window*>(pCreate->lpCreateParams);
			SetWindowLongPtr(Window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
			SetWindowLongPtr(Window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WindowCallbackForward));
			return pWnd->WindowCallback(Window, Message, wParam, lParam);
		}
		return DefWindowProc(Window, Message, wParam, lParam);
	}

	LRESULT Sakura::Win32Window::WindowCallbackForward(HWND Window, UINT Message, WPARAM wParam, LPARAM lParam)
	{
		Win32Window* const pWnd = reinterpret_cast<Win32Window*>(GetWindowLongPtr(Window, GWLP_USERDATA));
		return pWnd->WindowCallback(Window, Message, wParam, lParam);
	}
}