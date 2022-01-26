#pragma once
#include "Event.h"

namespace Chunky
{
	class MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(int x, int y)
			: m_PosX(x), m_PosY(y), m_DeltaX(0), m_DeltaY(0) { }

		MouseMoveEvent(int posX, int posY, int deltaX, int deltaY)
			: m_PosX(posX), m_PosY(posY), m_DeltaX(deltaX), m_DeltaY(deltaY) { }

		static EventType GetStaticType() { return EventType::MOUSE_MOVED; }
		EventType GetType() const override { return GetStaticType(); }
		const char* GetName() const override { return "MOUSE_MOVED"; }

		std::string ToString() const override
		{
			std::string string = GetName();
			string += ": " + std::to_string(m_PosX) + ", " + std::to_string(m_PosY);

			if (m_DeltaX != 0 || m_DeltaY != 0)
				string += " - (delta: " + std::to_string(m_DeltaX) + ", " + std::to_string(m_DeltaY) + ")";

			return string;
		}

		std::pair<int, int> GetPosition() const { return { m_PosX, m_PosY }; }
		std::pair<int, int> GetDelta() const { return { m_DeltaX, m_DeltaY }; }

	private:
		float m_PosX, m_PosY;
		float m_DeltaX, m_DeltaY;
	};

	class MouseScrollEvent : public Event
	{
	public:
		MouseScrollEvent(int xOffset, int yOffset)
			: m_OffsetX(xOffset), m_OffsetY(yOffset) { }

		static EventType GetStaticType() { return EventType::MOUSE_SCROLLED; }
		EventType GetType() const override { return GetStaticType(); }
		const char* GetName() const override { return "MOUSE_SCROLLED"; }

		std::string ToString() const override
		{
			std::string string = GetName();
			string += ": " + std::to_string(m_OffsetX) + ", " + std::to_string(m_OffsetY);
			return string;
		}

		std::pair<int, int> GetOffset() const { return { m_OffsetX, m_OffsetY }; }

	private:
		float m_OffsetX, m_OffsetY;
	};

	class MouseButtonEvent : public Event
	{
	protected:
		MouseButtonEvent(int button)
			: m_Button(button) { }

	public:
		int GetButton() const { return m_Button; }

	protected:
		int m_Button;
	};

	class MouseButtonPressEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressEvent(int button)
			: MouseButtonEvent(button) { }

		static EventType GetStaticType() { return EventType::MOUSE_PRESSED; }
		EventType GetType() const override { return GetStaticType(); }
		const char* GetName() const override { return "MOUSE_PRESSED"; }

		std::string ToString() const override
		{
			std::string string = GetName();
			string += ": " + std::to_string(m_Button);
			return string;
		}
	};

	class MouseButtonReleaseEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleaseEvent(int button)
			: MouseButtonEvent(button) { }

		static EventType GetStaticType() { return EventType::MOUSE_RELEASED; }
		EventType GetType() const override { return GetStaticType(); }
		const char* GetName() const override { return "MOUSE_RELEASED"; }

		std::string ToString() const override
		{
			std::string string = GetName();
			string += ": " + std::to_string(m_Button);
			return string;
		}
	};
}