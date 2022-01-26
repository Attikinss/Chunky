#include "Window.h"

#include "chunky/events/MouseEvent.h"
#include "chunky/events/KeyboardEvent.h"
#include "chunky/events/WindowEvent.h"
#include "chunky/core/Defines.h"

#include <glad/gl.h>
#include <glfw/glfw3.h>

namespace Chunky
{
	static GLFWwindow* CreateWindowHandle(const std::string& title, int width, int height, bool isFullscreen)
	{
		GLFWwindow* windowHandle;
		if (isFullscreen)
		{
			// Query the primary monitor and its current state
			GLFWmonitor* monitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* mode = glfwGetVideoMode(monitor);

			// Create the window in fullscreen mode
			windowHandle = glfwCreateWindow(mode->width, mode->height, title.c_str(), monitor, nullptr);
		}
		else
		{
			// Create the window in non-fullscreen mode
			windowHandle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		}

		return windowHandle;
	}

	Window::Window(const WindowInfo& windowInfo)
	{
		// Initialise glfw
		// TODO: Move this into a renderer class
		glfwInit();

		glfwDefaultWindowHints();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// Create glfw window
		m_WindowHandle = CreateWindowHandle(windowInfo.Title, windowInfo.Width, windowInfo.Height, windowInfo.IsFullscreen);
		glfwMakeContextCurrent(m_WindowHandle);

		m_PtrData.Fullscreen = windowInfo.IsFullscreen;
		m_PtrData.Width = windowInfo.Width;
		m_PtrData.Height = windowInfo.Height;
		m_PtrData.Title = windowInfo.Title;

		// Initialise glad
		gladLoadGL((GLADloadfunc)glfwGetProcAddress);

		glfwSetWindowUserPointer(m_WindowHandle, &m_PtrData);

		SetCallbacks();
	}

	Window::~Window()
	{
		// Destroy glfw window
		glfwDestroyWindow(m_WindowHandle);

		// Shutdown glfw
		// TODO: Move this into a renderer class
		glfwTerminate();
	}

	void Window::PollEvents()
	{
		glfwPollEvents();
	}

	void Window::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

	void Window::HandleEvent(Event& evt)
	{
		Chunky::EventDispatcher dispatcher(evt);
		dispatcher.Dispatch<Chunky::WindowMoveEvent>(BIND_FUNCTION(OnWindowMove));
		dispatcher.Dispatch<Chunky::WindowResizeEvent>(BIND_FUNCTION(OnWindowResize));
	}

	void Window::SetCallbacks()
	{
		// TODO: Move this function into a glfw/environment initialiser class

		// Window resizing and minimising callback
		glfwSetWindowSizeCallback(m_WindowHandle, [](GLFWwindow* window, int width, int height)
		{
			auto& data = *((WindowPtrData*)glfwGetWindowUserPointer(window));

			WindowResizeEvent evt(width, height);
			data.Callback(evt);
			data.Width = width;
			data.Height = height;
		});

		// Window movement callback
		glfwSetWindowPosCallback(m_WindowHandle, [](GLFWwindow* window, int x, int y)
		{
			auto& data = *((WindowPtrData*)glfwGetWindowUserPointer(window));

			WindowMoveEvent evt(x, y);
			data.Callback(evt);

			// TODO: Set position in 'data' for delta calculation
		});

		// Window closing callback
		glfwSetWindowCloseCallback(m_WindowHandle, [](GLFWwindow* window)
		{
			auto& data = *((WindowPtrData*)glfwGetWindowUserPointer(window));
			
			WindowCloseEvent evt;
			data.Callback(evt);
		});

		// Key interaction callack
		glfwSetKeyCallback(m_WindowHandle, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			auto& data = *((WindowPtrData*)glfwGetWindowUserPointer(window));

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressEvent evt(key, 0);
					data.Callback(evt);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleaseEvent evt(key);
					data.Callback(evt);
					break;
				}
				case GLFW_REPEAT:
				{
					// TODO: Calculate repeats
					KeyPressEvent evt(key, 1);
					data.Callback(evt);
					break;
				}
			}
		});

		// Unicode character typing callback
		glfwSetCharCallback(m_WindowHandle, [](GLFWwindow* window, unsigned int keycode)
		{
			auto& data = *(WindowPtrData*)glfwGetWindowUserPointer(window);
			KeyTypeEvent evt(keycode);
			data.Callback(evt);
		});

		// Mouse button interaction callback
		glfwSetMouseButtonCallback(m_WindowHandle, [](GLFWwindow* window, int button, int action, int mods)
		{
			auto& data = *((WindowPtrData*)glfwGetWindowUserPointer(window));

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressEvent evt(button);
					data.Callback(evt);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleaseEvent evt(button);
					data.Callback(evt);
					break;
				}
			}
		});

		// Mouse scroll wheel callback
		glfwSetScrollCallback(m_WindowHandle, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			auto& data = *((WindowPtrData*)glfwGetWindowUserPointer(window));
			MouseScrollEvent evt((int)xOffset, (int)yOffset);
			data.Callback(evt);
		});

		// Mouse movement callback
		glfwSetCursorPosCallback(m_WindowHandle, [](GLFWwindow* window, double x, double y)
		{
			auto& data = *((WindowPtrData*)glfwGetWindowUserPointer(window));
			MouseMoveEvent evt((int)x, (int)y);
			data.Callback(evt);
		});

		// File drop callback (drag and drop external files onto window)
		glfwSetDropCallback(m_WindowHandle, [](GLFWwindow* window, int pathCount, const char* paths[])
		{
			auto& data = *((WindowPtrData*)glfwGetWindowUserPointer(window));
			FileDropEvent evt(pathCount, paths);
			data.Callback(evt);
		});
	}

	bool Window::OnWindowMove(Chunky::WindowMoveEvent& evt)
	{
		return false;
	}

	bool Window::OnWindowResize(Chunky::WindowResizeEvent& evt)
	{
		return false;
	}
}