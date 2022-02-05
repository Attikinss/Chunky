#pragma once

namespace Chunky
{
	class Batch;

	class Renderer
	{
	public:
		static void Initialise();
		static void Shutdown();
		static void Submit(const Batch& batch);

		static void BeginFrame();
		static void EndFrame();
	};
}