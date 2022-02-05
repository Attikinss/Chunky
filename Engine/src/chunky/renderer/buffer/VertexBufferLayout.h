#pragma once
#include <string>
#include <vector>

namespace Chunky
{
	enum class DataType
	{
		None = 0,
		Bool,
		Float, Float2, Float3, Float4,
		Int, Int2, Int3, Int4,
		Mat3, Mat4,
	};

	static unsigned int ShaderDataTypeSize(DataType type)
	{
		switch (type)
		{
			case DataType::Bool:     return 1;
			case DataType::Float:    return 4;
			case DataType::Float2:   return 4 * 2;
			case DataType::Float3:   return 4 * 3;
			case DataType::Float4:   return 4 * 4;
			case DataType::Int:      return 4;
			case DataType::Int2:     return 4 * 2;
			case DataType::Int3:     return 4 * 3;
			case DataType::Int4:     return 4 * 4;
			case DataType::Mat3:     return 4 * 3 * 3;
			case DataType::Mat4:     return 4 * 4 * 4;
		}

		return 0;
	}

	struct BufferElement
	{
		std::string Name;

		bool Normalised;
		bool Instanced;

		// The element's shader data type
		DataType Type;

		//The size of the element in bytes
		unsigned int Size;

		// The element's offset in the buffer
		unsigned int Offset;

		// VBO element default constructor
		BufferElement() = default;

		BufferElement(DataType type, const std::string& name, bool instanced = false, bool normalised = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Instanced(instanced), Normalised(normalised) { }

		unsigned int GetComponentCount() const
		{
			switch (Type)
			{
				case DataType::Bool:    return 1;
				case DataType::Float:   return 1;
				case DataType::Float2:  return 2;
				case DataType::Float3:  return 3;
				case DataType::Float4:  return 4;
				case DataType::Int:     return 1;
				case DataType::Int2:    return 2;
				case DataType::Int3:    return 3;
				case DataType::Int4:    return 4;
				case DataType::Mat3:    return 3 * 3;
				case DataType::Mat4:    return 4 * 4;
			}

			return 0;
		}
	};

	class VertexBufferLayout
	{
	public:
		VertexBufferLayout() = default;
		VertexBufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		unsigned int GetStride() const { return m_Stride; }
		const std::vector<BufferElement>& GetElements() const { return m_Elements; }
		unsigned int GetElementCount() const { return (unsigned int)m_Elements.size(); }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

	private:
		// Calculates the offsets and stride of all elements in the layout
		void CalculateOffsetsAndStride()
		{
			unsigned int offset = 0;
			m_Stride = 0;

			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}

	private:
		// Collection of elements in the layout
		std::vector<BufferElement> m_Elements;

		// The running stride of each element
		unsigned int m_Stride = 0;
	};
}