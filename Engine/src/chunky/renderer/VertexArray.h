#pragma once
#include "buffer/IndexBuffer.h"
#include "buffer/VertexBuffer.h"

namespace Chunky
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void Bind();
		void Unbind();

		void AddVertexBuffer(VertexBuffer* buffer);
		void SetIndexBuffer(IndexBuffer* buffer);

		const std::vector<VertexBuffer*>& GetVertexBuffers() const { return m_VertexBuffers;  }
		const IndexBuffer& GetIndexBuffer() const { return *m_IndexBuffer; }

	private:
		std::vector<VertexBuffer*> m_VertexBuffers;
		IndexBuffer* m_IndexBuffer;

		unsigned int m_ID = 0;
		unsigned int m_AttributeCount = 0;
	};
}