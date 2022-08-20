#pragma once

namespace Sakura
{
	enum class EventType
	{
		None = 0,
		WindowResize, WindowClose,
		KeyPressed, KeyReleased
	};

	class Event
	{
	public:
		virtual EventType GetEventType() = 0;

		bool Handled = false;
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& e)
			: m_Event(e)
		{}

		template<typename T>
		bool Dispatch(EventFn<T> function)
		{
			if (m_Event.GetEventType() == T::GetStaticEventType())
			{
				m_Event.Handled = function(reinterpret_cast<T&>(m_Event));
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};
}