#pragma once
#include <string>
#include "chunky/Events/WindowEvent.h"

struct GLFWwindow;

namespace Chunky
{
	struct WindowInfo
	{
		std::string Title;
		int Width = 0, Height = 0;
		bool IsFullscreen = false;
	};

	class Window
	{
	private:
		struct WindowPtrData
		{
			std::string Title;
			int Width = 0, Height = 0;
			bool Fullscreen = false;

			EventCallback Callback = EventCallback();
		};

	public:
		Window(const WindowInfo& windowInfo);
		~Window();

		void SetWindowCallback(const EventCallback& callback) { m_PtrData.Callback = callback; };
		void PollEvents();
		void SwapBuffers();

		void HandleEvent(Event& evt);

	private:
		void SetCallbacks();
		bool OnWindowMove(Chunky::WindowMoveEvent& evt);
		bool OnWindowResize(Chunky::WindowResizeEvent& evt);

	private:
		GLFWwindow* m_WindowHandle = nullptr;
		WindowPtrData m_PtrData;
	};
}