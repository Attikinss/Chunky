#pragma once
#include "Renderer.h"
#include "Vertex.h"
#include "VertexArray.h"

#include <vector>

namespace Chunky
{
	class Batch final
	{
	public:
		Batch();
		Batch(int vertexCount);
		~Batch();

		bool Add(Vertex vertex);
		bool Add(const std::vector<Vertex>& vertices);
		void Clear();
		bool IsEmpty();
		bool IsFull();
		bool HasSpace(int count);
		void Render();
		void SubmitToRenderer();

		const std::vector<Vertex>& GetVertices() const { return m_Vertices; }

		Batch& operator=(const Batch& other) = delete;

	private:
		std::vector<Vertex> m_Vertices;
		int m_Capacity = 0;
		int m_CurrentPosition = 0;

		VertexArray* m_VAO = nullptr;
	};
}