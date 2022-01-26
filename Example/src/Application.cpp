#include "Application.h"
#include "chunky/core/Defines.h"
#include "chunky/events/WindowEvent.h"

#include <iostream>

void Application::Run()
{
	if (!m_Running && !Initialise())
	{
		// TODO: error/exception handling
		return;
	}

	while (m_Running)
	{
		m_Window->PollEvents();
		m_Window->SwapBuffers();
	}

	Shutdown();
}

bool Application::Initialise()
{
	Chunky::WindowInfo info;
	info.Title = "Example";
	info.Width = 1280;
	info.Height = 720;
	info.IsFullscreen = false;
	
	m_Window = new Chunky::Window(info);
	m_Window->SetWindowCallback(BIND_FUNCTION(HandleEvent));
	m_Running = true;

	return true;
}

void Application::HandleEvent(Chunky::Event& evt)
{
	Chunky::EventDispatcher dispatcher(evt);
	dispatcher.Dispatch<Chunky::WindowCloseEvent>(BIND_FUNCTION(OnWindowClose));

	m_Window->HandleEvent(evt);
}

void Application::Shutdown()
{
	delete m_Window;
}

bool Application::OnWindowClose(Chunky::WindowCloseEvent& evt)
{
	m_Running = false;
	return false;
}
