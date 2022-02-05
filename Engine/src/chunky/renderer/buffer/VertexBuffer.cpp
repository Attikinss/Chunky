#include "VertexBuffer.h"

#include <glad/gl.h>

// Temp - used for memcpy reference
#include <vcruntime_string.h>

namespace Chunky
{
	VertexBuffer::VertexBuffer(unsigned int size)
		: m_Size(size)
	{
		// Create buffer and assign size but leave it empty
		glCreateBuffers(1, &m_ID);
		glNamedBufferData(m_ID, size, nullptr, GL_DYNAMIC_DRAW);
	}

	VertexBuffer::VertexBuffer(unsigned int size, void* data)
		: m_Size(size)
	{
		// Create and write to buffer
		glCreateBuffers(1, &m_ID);
		glNamedBufferData(m_ID, size, data, GL_STATIC_DRAW);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_ID);
		m_ID = 0;
	}

	void VertexBuffer::SetData(unsigned int size, void* data, unsigned int offset)
	{
		void* buffer = glMapNamedBuffer(m_ID, GL_WRITE_ONLY | GL_MAP_UNSYNCHRONIZED_BIT);
		memcpy((&buffer)[offset], data, size);

		glUnmapNamedBuffer(m_ID);
	}

	void VertexBuffer::SetLayout(const VertexBufferLayout& layout)
	{
		m_Layout = layout;
	}

	void VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	}

	void VertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}