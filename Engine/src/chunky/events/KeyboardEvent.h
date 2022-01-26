#pragma once
#include "Event.h"

namespace Chunky
{
	class KeyboardEvent : public Event
	{
	protected:
		KeyboardEvent(int keycode)
			: m_KeyCode(keycode) { }

	public:
		inline int GetKeyCode() const { return m_KeyCode; }

	protected:
		int m_KeyCode;
	};

	class KeyPressEvent : public KeyboardEvent
	{
	public:
		KeyPressEvent(int keycode, int repeatCount)
			: KeyboardEvent(keycode), m_RepeatCount(repeatCount) { }

		int GetRepeatCount() const { return m_RepeatCount; }

		static EventType GetStaticType() { return EventType::KEY_PRESSED; }
		EventType GetType() const override { return GetStaticType(); }
		const char* GetName() const override { return "KEY_PRESSED"; }

		std::string ToString() const override
		{
			std::string string  = GetName();
			string += ": " + std::to_string(m_KeyCode) + " (" + std::to_string(m_RepeatCount) + " repeats)";
			return string;
		}

	private:
		int m_RepeatCount;
	};

	class KeyReleaseEvent : public KeyboardEvent
	{
	public:
		KeyReleaseEvent(int keycode)
			: KeyboardEvent(keycode) { }

		static EventType GetStaticType() { return EventType::KEY_RELEASED; }
		EventType GetType() const override { return GetStaticType(); }
		const char* GetName() const override { return "KEY_RELEASED"; }

		std::string ToString() const override
		{
			std::string string = GetName();
			string += ": " + std::to_string(m_KeyCode);
			return string;
		}
	};

	class KeyTypeEvent : public KeyboardEvent
	{
	public:
		KeyTypeEvent(int keycode)
			: KeyboardEvent(keycode) { }

		static EventType GetStaticType() { return EventType::KEY_TYPED; }
		EventType GetType() const override { return GetStaticType(); }
		const char* GetName() const override { return "KEY_TYPED"; }

		std::string ToString() const override
		{
			std::string string = GetName();
			string += ": " + std::to_string(m_KeyCode);
			return string;
		}
	};
}