#pragma once

#include "Sakura/Core.h"
#include "Sakura/Events/Event.h"
#include "Sakura/Renderer/RendererContext.h"

#include <string>
#include <memory>

namespace Sakura
{
	using EventCallbackFn = std::function<void(Event&)>;

	struct WindowSpecification
	{
		std::string Title;
		uint32 Width = 1280;
		uint32 Height = 720;
		EventCallbackFn EventCallback;
	};

	class Window
	{
	public:
		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual uint32 GetWidth() const = 0;
		virtual uint32 GetHeight() const = 0;

		virtual std::shared_ptr<RendererContext> GetContext() = 0;

		virtual void* GetNativeWindow() = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

		static std::shared_ptr<Window> Create(const WindowSpecification& spec);
	};
}

