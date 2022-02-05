#include "Renderer.h"
#include "chunky/core/Logger.h"
#include "chunky/renderer/Batch.h"

#include <glad/gl.h>
#include <glfw/glfw3.h>

namespace Chunky
{
	struct RendererData
	{
		std::vector<Batch> m_Batches;
	};

	static bool s_Initialised = false;
	static RendererData* s_Data = nullptr;

	void Renderer::Initialise()
	{
		if (s_Initialised)
		{
			Logger::Warn("Renderer is already active !!!");
			return;
		}

		s_Initialised = true;
		s_Data = new RendererData();

		// Dump info
		Logger::Trace("Renderer Initialised...");
		Logger::Info("OpenGL Info:\n\tVersion: {0}\n\tVendor: {1}\n\tDevice: {2}",
			glGetString(GL_VERSION), glGetString(GL_VENDOR), glGetString(GL_RENDERER));
	}

	void Renderer::Shutdown()
	{
		if (!s_Initialised)
		{
			Logger::Warn("Renderer isn't active !!!");
			return;
		}

		delete s_Data;

		s_Initialised = false;
	}

	void Renderer::Submit(const Batch& batch)
	{
		if (!s_Initialised)
		{
			Logger::Warn("Renderer isn't active !!!");
			return;
		}

		s_Data->m_Batches.push_back(batch);
	}

	void Renderer::BeginFrame()
	{
		if (!s_Initialised)
		{
			Logger::Warn("Renderer isn't active !!!");
			return;
		}
	}

	void Renderer::EndFrame()
	{
		if (!s_Initialised)
		{
			Logger::Warn("Renderer isn't active !!!");
			return;
		}

		for (auto batch : s_Data->m_Batches)
			batch.Render();

		s_Data->m_Batches.clear();
	}
}