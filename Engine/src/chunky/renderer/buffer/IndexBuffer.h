#pragma once

namespace Chunky
{
	class IndexBuffer
	{
	public:
		IndexBuffer(unsigned int count);
		IndexBuffer(unsigned int count, void* data);
		~IndexBuffer();

		void SetData(unsigned int size, void* data, unsigned int offset = 0);
		void Bind();
		void Unbind();

		unsigned int GetCount() const { return m_Count; }

	private:
		unsigned int m_ID = 0;
		unsigned int m_Count = 0;
	};
}