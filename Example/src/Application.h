#pragma once
#include "chunky/core/Application.h"
#include "chunky/core/Window.h"

#include "chunky/events/WindowEvent.h"

class Application : public Chunky::Application
{
public:
	Application() = default;
	~Application() = default;

	void Run() override;
	void HandleEvent(Chunky::Event& evt);

protected:
	bool Initialise() override;
	void Shutdown() override;

private:
	bool OnWindowClose(Chunky::WindowCloseEvent& evt);

private:
	bool m_Running = false;
	Chunky::Window* m_Window = nullptr;
};