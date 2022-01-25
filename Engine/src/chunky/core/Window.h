#pragma once
#include <string>

struct GLFWwindow;

namespace Chunky
{
	struct WindowInfo
	{
		std::string Title;
		int Width, Height;
		bool IsFullscreen;
	};

	class Window
	{
	private:
		struct WindowPtrData
		{
			std::string Title;
			uint16_t Width = 0, Height = 0;
			bool Fullscreen = false;
		};

	public:
		Window(const WindowInfo& windowInfo);
		~Window();

	private:
		void SetCallbacks();

	private:
		GLFWwindow* m_WindowHandle = nullptr;
		WindowPtrData m_PtrData;
	};
}