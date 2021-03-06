#include "IndexBuffer.h"

#include <glad/gl.h>

// Temp - used for memcpy reference
#include <vcruntime_string.h>

namespace Chunky
{
	IndexBuffer::IndexBuffer(unsigned int size)
		: m_Count(size / sizeof(unsigned int))
	{
		// Create and write to buffer
		glCreateBuffers(1, &m_ID);
		glNamedBufferData(m_ID, size, nullptr, GL_DYNAMIC_DRAW);
	}

	IndexBuffer::IndexBuffer(unsigned int size, void* data)
		: m_Count(size / sizeof(unsigned int))
	{
		// Create buffer and assign size but leave it empty
		glCreateBuffers(1, &m_ID);
		glNamedBufferData(m_ID, size, data, GL_STATIC_DRAW);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_ID);
		m_ID = 0;
	}

	void IndexBuffer::SetData(unsigned int size, void* data, unsigned int offset)
	{
		void* buffer = glMapNamedBuffer(m_ID, GL_WRITE_ONLY | GL_MAP_UNSYNCHRONIZED_BIT);
		memcpy((&buffer)[offset], data, size);

		glUnmapNamedBuffer(m_ID);
	}

	void IndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
	}

	void IndexBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}