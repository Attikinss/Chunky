#pragma once
#include "Event.h"

namespace Chunky
{
	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(int width, int height)
			: m_Width(width), m_Height(height)
		{
		}

		static EventType GetStaticType() { return EventType::WINDOW_RESIZED; }
		EventType GetType() const override { return GetStaticType(); }
		const char* GetName() const override { return "WINDOW_RESIZED"; }

		std::string ToString() const override
		{
			std::string string = GetName();
			string += ": " + std::to_string(m_Width) + ", " + std::to_string(m_Height);
			return string;
		}

		std::pair<int, int> GetSize() const { return { m_Width, m_Height }; }

	private:
		int m_Width, m_Height;
	};

	class WindowMoveEvent : public Event
	{
	public:
		WindowMoveEvent(int x, int y)
			: m_PosX(x), m_PosY(y), m_DeltaX(0), m_DeltaY(0) { }

		WindowMoveEvent(int posX, int posY, int deltaX, int deltaY)
			: m_PosX(posX), m_PosY(posY), m_DeltaX(deltaX), m_DeltaY(deltaY) { }

		static EventType GetStaticType() { return EventType::WINDOW_MOVED; }
		EventType GetType() const override { return GetStaticType(); }
		const char* GetName() const override { return "WINDOW_MOVED"; }

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
		int m_PosX, m_PosY;
		int m_DeltaX, m_DeltaY;
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		static EventType GetStaticType() { return EventType::WINDOW_CLOSED; }
		EventType GetType() const override { return GetStaticType(); }
		const char* GetName() const override { return "WINDOW_CLOSED"; }
	};

	class FileDropEvent : public Event
	{
	public:
		FileDropEvent(int count, const char* paths[])
			: m_PathCount(count)
		{
			m_Paths.reserve(count);
			for (int i = 0; i < count; i++)
				m_Paths.emplace_back(paths[i]);
		}

		static EventType GetStaticType() { return EventType::FILE_DROPPED; }
		EventType GetType() const override { return GetStaticType(); }
		const char* GetName() const override { return "FILE_DROPPED"; }

		std::string ToString() const override
		{
			std::string string = GetName();
			string += ':';

			for (auto path : m_Paths)
				string.append("\n\t" + path);

			return string;
		}

		std::vector<std::string> GetFilepaths() const { return m_Paths; }

	private:
		int m_PathCount;
		std::vector<std::string> m_Paths;
	};
}