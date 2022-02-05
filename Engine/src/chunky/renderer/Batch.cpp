#include "Batch.h"

#include <glad/gl.h>

namespace Chunky
{
	Batch::Batch()
		: m_Capacity(1024)
	{
		m_Vertices.reserve(1024);

		auto vbo = new VertexBuffer(m_Capacity * sizeof(Vertex));
		vbo->SetLayout({
			{ DataType::Float3, "a_Position" },
			{ DataType::Float3, "a_Normal" },
			{ DataType::Float2, "a_UV" },
		});

		m_VAO = new VertexArray();
		m_VAO->AddVertexBuffer(vbo);
	}

	Batch::Batch(int vertexCount)
		: m_Capacity(vertexCount)
	{
		m_Vertices.reserve(vertexCount);

		auto vbo = new VertexBuffer(m_Capacity * sizeof(Vertex));
		vbo->SetLayout({
			{ DataType::Float3, "a_Position" },
			{ DataType::Float3, "a_Normal" },
			{ DataType::Float2, "a_UV" },
		});

		m_VAO = new VertexArray();
		m_VAO->AddVertexBuffer(vbo);
	}

	Batch::~Batch()
	{
		Clear();
	}

	bool Batch::Add(Vertex vertex)
	{
		if (IsFull())
			return false;

		m_Vertices.push_back(vertex);
		return true;
	}

	bool Batch::Add(const std::vector<Vertex>& vertices)
	{
		if (vertices.size() == 0 || IsFull() || !HasSpace((int)vertices.size()))
			return false;

		m_Vertices.insert(m_Vertices.end(), vertices.begin(), vertices.end());
		return true;
	}

	void Batch::Clear()
	{
		m_Vertices.clear();
	}

	bool Batch::IsEmpty()
	{
		return m_Vertices.size() == 0;
	}

	bool Batch::IsFull()
	{
		return m_Vertices.size() == m_Capacity;
	}

	bool Batch::HasSpace(int count)
	{
		return m_Capacity - m_Vertices.size() >= count;
	}

	void Batch::Render()
	{
		m_VAO->Bind();
		glDrawArrays(GL_TRIANGLES, 0, (int)m_Vertices.size());
		m_VAO->Unbind();
	}

	void Batch::SubmitToRenderer()
	{
		Renderer::Submit(*this);
	}
}