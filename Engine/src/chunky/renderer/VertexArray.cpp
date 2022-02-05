#include "VertexArray.h"

#include <glad/gl.h>

namespace Chunky
{
	namespace Utils
	{
		static GLenum DataTypeToOpenGLType(DataType type)
		{
			switch (type)
			{
			case DataType::Bool:
				return GL_BOOL;

			case DataType::Float:
			case DataType::Float2:
			case DataType::Float3:
			case DataType::Float4:
			case DataType::Mat3:
			case DataType::Mat4:
				return GL_FLOAT;

			case DataType::Int:
			case DataType::Int2:
			case DataType::Int3:
			case DataType::Int4:
				return GL_INT;
			}

			return GL_NONE;
		}
	}

	VertexArray::VertexArray()
	{

	}

	VertexArray::~VertexArray()
	{

	}

	void VertexArray::Bind()
	{
		glBindVertexArray(m_ID);

		for (uint32_t i = 0; i < m_AttributeCount; i++)
			glEnableVertexAttribArray(i);
	}

	void VertexArray::Unbind()
	{
		glBindVertexArray(0);

		for (uint32_t i = 0; i < m_AttributeCount; i++)
			glDisableVertexAttribArray(i);
	}

	void VertexArray::AddVertexBuffer(VertexBuffer* buffer)
	{
		Bind();
		buffer->Bind();

		unsigned int index = 0;
		const auto& layout = buffer->GetLayout();
		auto elements = layout.GetElements();

		for (const auto& element : elements)
		{
			unsigned int componentCount = element.GetComponentCount();
			unsigned int valueType = Utils::DataTypeToOpenGLType(element.Type);
			unsigned int normalised = element.Normalised ? GL_TRUE : GL_FALSE;
			unsigned int stride = layout.GetStride();
			unsigned int offset = element.Offset;

			unsigned int glAttribs = componentCount < 4 ? 1 : 4 % componentCount;
			for (unsigned int j = 0; j < glAttribs; j++)
			{
				// This assumes the data is always of float type
				unsigned int dataOffset = offset + componentCount * j;

				glEnableVertexAttribArray(m_AttributeCount + index);
				glVertexAttribPointer(m_AttributeCount + index, componentCount / glAttribs, valueType, normalised, stride, (void*)((unsigned long long)dataOffset));

				if (element.Instanced)
					glVertexAttribDivisor(m_AttributeCount + index, 1);

				index++;
			}
		}

		m_AttributeCount += index;

		Unbind();
		buffer->Unbind();

		m_VertexBuffers.push_back(buffer);
	}

	void VertexArray::SetIndexBuffer(IndexBuffer* buffer)
	{
		Bind();
		buffer->Bind();

		Unbind();
		buffer->Unbind();

		m_IndexBuffer = buffer;
	}
}