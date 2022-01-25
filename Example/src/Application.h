#pragma once
#include "chunky/core/Application.h"

class Application : public Chunky::Application
{
public:
	Application() = default;
	~Application() = default;

	void Initialise() override;
	void Shutdown() override;

protected:
	void Run() override;

private:
	bool m_Running = false;
};