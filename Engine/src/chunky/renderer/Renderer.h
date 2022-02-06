#pragma once

namespace Chunky
{
	class Batch;
	class Camera;

	class Renderer
	{
	public:
		static void Initialise();
		static void Shutdown();
		static void Submit(const Batch& batch);

		static void BeginFrame(const Camera& camera);
		static void EndFrame();
	};
}