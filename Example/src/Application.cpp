#include "Application.h"
#include "chunky/core/Defines.h"
#include "chunky/events/WindowEvent.h"

#include "chunky/core/Logger.h"

#include "chunky/renderer/Renderer.h"


void Application::Run()
{
	if (m_Running)
	{
		Chunky::Logger::Warn("Application already running !!!");
		return;
	}

	m_Running = Initialise();

	while (m_Running)
	{
		m_Window->PollEvents();

		Chunky::Renderer::BeginFrame();

		Chunky::Renderer::EndFrame();

		m_Window->SwapBuffers();
	}

	Shutdown();
}

bool Application::Initialise()
{
	Chunky::Logger::Initialise("ENGINE");

	Chunky::WindowInfo info;
	info.Title = "Example";
	info.Width = 1280;
	info.Height = 720;
	info.IsFullscreen = false;
	
	m_Window = new Chunky::Window(info);
	m_Window->SetWindowCallback(BIND_FUNCTION_SCOPED(HandleEvent));
	m_Running = true;

	Chunky::Renderer::Initialise();

	return true;
}

void Application::HandleEvent(Chunky::Event& evt)
{
	Chunky::EventDispatcher dispatcher(evt);
	dispatcher.Dispatch<Chunky::WindowCloseEvent>(BIND_FUNCTION_SCOPED(OnWindowClose));

	m_Window->HandleEvent(evt);
}

void Application::Shutdown()
{
	Chunky::Renderer::Shutdown();
	delete m_Window;
}

bool Application::OnWindowClose(Chunky::WindowCloseEvent& evt)
{
	m_Running = false;
	return false;
}
