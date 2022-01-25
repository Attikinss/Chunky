#pragma once

namespace Chunky
{
	class Application
	{
	public:
		Application() = default;
		virtual ~Application() = default;

		virtual bool Initialise() = 0;
		virtual void Shutdown() = 0;
		virtual void Run() = 0;
	};
}