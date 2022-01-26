#pragma once

namespace Chunky
{
	class Application
	{
	public:
		Application() = default;
		virtual ~Application() = default;

		virtual void Run() = 0;

	protected:
		virtual bool Initialise() = 0;
		virtual void Shutdown() = 0;
	};
}