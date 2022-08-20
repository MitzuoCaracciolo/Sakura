#pragma once

#include "Sakura/Events/Event.h"

namespace Sakura
{
	class WindowCloseEvent : public Event
	{
	public:
		virtual EventType GetEventType() override { return EventType::WindowClose; }
		static EventType GetStaticEventType() { return EventType::WindowClose; }
	};
}