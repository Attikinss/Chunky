#pragma once
#include "math/vector/Vector2f.h"
#include "math/vector/Vector3f.h"
#include "math/vector/Vector4f.h"
#include "math/matrix/Matrix3f.h"
#include "math/matrix/Matrix4f.h"

#include <string>
#include <unordered_map>

namespace Chunky
{
	class Shader
	{
	public:
		Shader(const std::string& filepath);

		void Reload();
		void Bind();
		void Unbind();

		void BindAttribute(unsigned int index, const std::string& name);
		void SetUint(const std::string& name, unsigned int value);
		void SetInt(const std::string& name, int value);
		void SetFloat(const std::string& name, float value);
		void SetVector2(const std::string& name, const Vector2f& value);
		void SetVector3(const std::string& name, const Vector3f& value);
		void SetVector4(const std::string& name, const Vector4f& value);
		void SetMatrix3(const std::string& name, const Matrix3f& value);
		void SetMatrix4(const std::string& name, const Matrix4f& value);

		void Load(const std::string& source);
		void Compile();
		unsigned int GetUniformLocation(const std::string& name) const;

	private:
		unsigned int m_ID = 0;
		std::string m_Name;
		std::string m_Filepath;

		std::unordered_map<uint32_t, std::string> m_ShaderSource;
		mutable std::unordered_map<std::string, uint32_t> m_UniformLocations;
	};
}