#include "Renderer.h"
#include "chunky/core/Logger.h"
#include "chunky/renderer/Batch.h"
#include "chunky/renderer/Camera.h"
#include "chunky/renderer/Shader.h"

#include <glad/gl.h>
#include <glfw/glfw3.h>

namespace Chunky
{
	struct RendererData
	{
		std::vector<Batch> m_Batches;
		Shader* TestShader = nullptr;
		Matrix4f CameraProjection;

		RendererData()
		{
			TestShader = new Shader("assets/shaders/basic.glsl");
			CameraProjection = Matrix4f(1.0);
		}

		~RendererData()
		{
			delete TestShader;
		}
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

	void Renderer::BeginFrame(const Camera& camera)
	{
		if (!s_Initialised)
		{
			Logger::Warn("Renderer isn't active !!!");
			return;
		}

		s_Data->CameraProjection = camera.GetViewProjection();

		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	}

	void Renderer::EndFrame()
	{
		if (!s_Initialised)
		{
			Logger::Warn("Renderer isn't active !!!");
			return;
		}

		/* -------- TEMPORARY -------- */

		static float rot = 0.0f;
		rot += 1.0f;
		Matrix4f model = Matrix4f::Translate(Matrix4f(1.0f), { 0.0f, 0.0f, -1.5f })
			* Matrix4f::Rotate(Matrix4f(1.0f), Math::Deg2Rad * rot, { (float)Math::Sin(rot * 0.01), 1.0f, (float)Math::Sin(rot * 0.01) });

		/* --------------------------- */

		s_Data->TestShader->Bind();
		s_Data->TestShader->SetMatrix4("u_ViewProjectionMatrix", s_Data->CameraProjection);
		s_Data->TestShader->SetMatrix4("u_ModelMatrix", model);

		for (auto batch : s_Data->m_Batches)
			batch.Render();

		s_Data->TestShader->Unbind();

		s_Data->m_Batches.clear();
	}
}