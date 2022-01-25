#pragma once

namespace Chunky
{
	class Application
	{
	public:
		Application() = default;
		virtual ~Application() = default;

		virtual void Initialise() = 0;
		virtual void Shutdown() = 0;
	
	protected:
		virtual void Run() = 0;
	};
}