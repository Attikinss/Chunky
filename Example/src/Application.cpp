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
	camera.SetView(Matrix4f::Inverse(Matrix4f::Translate(Matrix4f(1.0f), { 0.0f, 0.0f, -5.0f })));

	std::vector<Chunky::Vertex> toFace = Chunky::Quad::TopFace().ToVertexData();
	std::vector<Chunky::Vertex> boFace = Chunky::Quad::BottomFace().ToVertexData();
	std::vector<Chunky::Vertex> leFace = Chunky::Quad::LeftFace().ToVertexData();
	std::vector<Chunky::Vertex> riFace = Chunky::Quad::RightFace().ToVertexData();
	std::vector<Chunky::Vertex> frFace = Chunky::Quad::FrontFace().ToVertexData();
	std::vector<Chunky::Vertex> baFace = Chunky::Quad::BackFace().ToVertexData();

	std::vector<Chunky::Vertex> vertices;
	vertices.insert(vertices.end(), toFace.begin(), toFace.end());
	vertices.insert(vertices.end(), boFace.begin(), boFace.end());
	vertices.insert(vertices.end(), leFace.begin(), leFace.end());
	vertices.insert(vertices.end(), riFace.begin(), riFace.end());
	vertices.insert(vertices.end(), frFace.begin(), frFace.end());
	vertices.insert(vertices.end(), baFace.begin(), baFace.end());

	Chunky::Batch batch(144*2);
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
