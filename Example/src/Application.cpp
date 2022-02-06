#include "Application.h"
#include "chunky/core/Defines.h"
#include "chunky/events/WindowEvent.h"

#include "chunky/core/Logger.h"

#include "chunky/renderer/Batch.h"
#include "chunky/renderer/Camera.h"
#include "chunky/renderer/Renderer.h"
#include "chunky/renderer/Quad.h"


void Application::Run()
{
	if (m_Running)
	{
		Chunky::Logger::Warn("Application already running !!!");
		return;
	}

	m_Running = Initialise();

	/* -------- TEMPORARY -------- */

	Chunky::Camera camera({ 1280.0f, 720.0f }, Chunky::Projection::Perspective);

	Chunky::Quad toFace = Chunky::Quad::Top;
	Chunky::Quad boFace = Chunky::Quad::Bottom;
	Chunky::Quad leFace = Chunky::Quad::Left;
	Chunky::Quad riFace = Chunky::Quad::Right;
	Chunky::Quad frFace = Chunky::Quad::Front;
	Chunky::Quad baFace = Chunky::Quad::Back;
	std::vector<Chunky::Vertex> toVerts = toFace.ToVertexData();
	std::vector<Chunky::Vertex> boVerts = boFace.ToVertexData();
	std::vector<Chunky::Vertex> leVerts = leFace.ToVertexData();
	std::vector<Chunky::Vertex> riVerts = riFace.ToVertexData();
	std::vector<Chunky::Vertex> frVerts = frFace.ToVertexData();
	std::vector<Chunky::Vertex> baVerts = baFace.ToVertexData();

	std::vector<Chunky::Vertex> vertices;
	vertices.insert(vertices.end(), toVerts.begin(), toVerts.end());
	vertices.insert(vertices.end(), boVerts.begin(), boVerts.end());
	vertices.insert(vertices.end(), leVerts.begin(), leVerts.end());
	vertices.insert(vertices.end(), riVerts.begin(), riVerts.end());
	vertices.insert(vertices.end(), frVerts.begin(), frVerts.end());
	vertices.insert(vertices.end(), baVerts.begin(), baVerts.end());

	Chunky::Batch batch(144);
	batch.Add(vertices);

	/* --------------------------- */

	while (m_Running)
	{
		m_Window->PollEvents();

		Chunky::Renderer::BeginFrame(camera);

		batch.SubmitToRenderer();

		Chunky::Renderer::EndFrame();

		m_Window->SwapBuffers();
	}

	Shutdown();
}

bool Application::Initialise()
{
	Chunky::Logger::Initialise("ENGINE");

	Chunky::WindowInfo info;
	info.Title = "Example";
	info.Width = 1280;
	info.Height = 720;
	info.IsFullscreen = false;
	
	m_Window = new Chunky::Window(info);
	m_Window->SetWindowCallback(BIND_FUNCTION_SCOPED(HandleEvent));
	m_Running = true;

	Chunky::Renderer::Initialise();

	return true;
}

void Application::HandleEvent(Chunky::Event& evt)
{
	Chunky::EventDispatcher dispatcher(evt);
	dispatcher.Dispatch<Chunky::WindowCloseEvent>(BIND_FUNCTION_SCOPED(OnWindowClose));

	m_Window->HandleEvent(evt);
}

void Application::Shutdown()
{
	Chunky::Renderer::Shutdown();
	delete m_Window;
}

bool Application::OnWindowClose(Chunky::WindowCloseEvent& evt)
{
	m_Running = false;
	return false;
}
