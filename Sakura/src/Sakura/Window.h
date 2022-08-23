#pragma once

#include "Sakura/Core.h"
#include "Sakura/Events/Event.h"

#include <string>

namespace Sakura
{
	struct WindowSpecification
	{
		std::string Title;
		uint32 Width = 1280;
		uint32 Height = 720;
	};

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual uint32 GetWidth() const = 0;
		virtual uint32 GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

		virtual void* GetNativeWindow() const = 0;

		static std::unique_ptr<Window> Create(const WindowSpecification& spec);
	};
}

