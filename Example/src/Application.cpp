#include "Application.h"

bool Application::Initialise()
{
	Chunky::WindowInfo info;
	info.Title = "Example";
	info.Width = 1280;
	info.Height = 720;
	info.IsFullscreen = false;
	
	m_Window = new Chunky::Window(info);
	m_Running = true;

	return true;
}

void Application::Run()
{
	while (m_Running);
}

void Application::Shutdown()
{
	m_Running = false;
	delete m_Window;
}
