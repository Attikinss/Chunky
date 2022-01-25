#pragma once
#include "chunky/core/Application.h"
#include "chunky/core/Window.h"

class Application : public Chunky::Application
{
public:
	Application() = default;
	~Application() = default;

	bool Initialise() override;
	void Shutdown() override;
	void Run() override;

private:
	bool m_Running = false;
	Chunky::Window* m_Window = nullptr;
};