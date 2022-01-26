#pragma once
#include <functional>
#include <string>

namespace Chunky
{
	class Event;
	using EventCallback = std::function<void(Event&)>;

	enum class EventType
	{
		NONE = 0,
		FILE_DROPPED,
		KEY_PRESSED, KEY_RELEASED, KEY_TYPED,
		MOUSE_PRESSED, MOUSE_RELEASED, MOUSE_MOVED, MOUSE_SCROLLED,
		WINDOW_CLOSED, WINDOW_RESIZED, WINDOW_MOVED, WINDOW_FOCUSED,
	};

	class Event
	{
	public:
		virtual ~Event() = default;

		virtual EventType GetType() const = 0;
		virtual const char* GetName() const = 0;
		virtual std::string ToString() const { return GetName(); }

	public:
		bool Used = false;
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFunction = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& evt)
			: m_Event(evt) { }

		template<typename T>
		bool Dispatch(const EventFunction<T>& func)
		{
			if (m_Event.GetType() == T::GetStaticType())
			{
				// Execute the function and mark as handled
				// if the event is blocked for further use
				m_Event.Used |= func(static_cast<T&>(m_Event));
				return true;
			}

			return false;
		}

	private:
		Event& m_Event;
	};
}