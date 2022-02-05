#pragma once
#include "VertexBufferLayout.h"

namespace Chunky
{
	class VertexBuffer
	{
	public:
		VertexBuffer(unsigned int size);
		VertexBuffer(unsigned int size, void* data);
		~VertexBuffer();

		void SetData(unsigned int size, void* data, unsigned int offset = 0);
		void SetLayout(const VertexBufferLayout& layout);

		void Bind();
		void Unbind();

		VertexBufferLayout& GetLayout() { return m_Layout; }
		unsigned int GetSize() const { return m_Size; }

	private:
		unsigned int m_ID = 0;
		unsigned int m_Size = 0;

		VertexBufferLayout m_Layout;
	};
}