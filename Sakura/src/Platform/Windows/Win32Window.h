#pragma once

#include <Windows.h>

#include "Sakura/Window.h"

namespace Sakura
{
	class Win32Window : public Window
	{
	public:
		Win32Window(const WindowSpecification& spec);
		~Win32Window();

		virtual void OnUpdate() override;

		virtual uint32 GetWidth() const override { return m_Spec.Width; }
		virtual uint32 GetHeight() const override { return m_Spec.Height; }

		virtual std::shared_ptr<RendererContext> GetContext() override { return m_Context; }

		virtual void* GetNativeWindow() override { return (void*)m_Handle; }

		virtual void SetEventCallback(const EventCallbackFn& callback) override { m_EventCallback = callback; }

	private:
		LRESULT WindowCallback(HWND Window, UINT Message, WPARAM wParam, LPARAM lParam);

		static LRESULT WindowCallbackSetup(HWND Window, UINT Message, WPARAM wParam, LPARAM lParam);
		static LRESULT WindowCallbackForward(HWND Window, UINT Message, WPARAM wParam, LPARAM lParam);

	private:
		HWND m_Handle;
		WindowSpecification m_Spec;
		EventCallbackFn m_EventCallback;
		std::shared_ptr<RendererContext> m_Context;
	};
}