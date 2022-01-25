#include "Application.h"

void Application::Initialise()
{
	m_Running = true;

	Run();
}

void Application::Run()
{
	while (m_Running);
}

void Application::Shutdown()
{
	m_Running = false;
}
