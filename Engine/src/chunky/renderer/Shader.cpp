#include "Shader.h"
#include "chunky/core/Logger.h"

#include <fstream>
#include <glad/gl.h>

namespace Chunky
{
	namespace Utils
	{
		static std::string ReadShaderFromFile(const std::string& filePath)
		{
			std::string contents;
			std::ifstream fileStream(filePath.c_str(), std::ios::in | std::ios::binary);

			if (fileStream)
			{
				fileStream.seekg(0, std::ios::end);
				contents.resize(fileStream.tellg());
				fileStream.seekg(0, std::ios::beg);
				fileStream.read(&contents[0], contents.size());
			}

			fileStream.close();
			return contents;
		}

		static std::string GetNameFromFilePath(const std::string& filepath)
		{
			std::string name;
			unsigned long long found = filepath.find_last_of("/\\");
			name = found != std::string::npos ? filepath.substr(found + 1) : filepath;
			found = name.find_last_of(".");
			name = found != std::string::npos ? name.substr(0, found) : name;

			return name;
		}

		static GLenum ShaderTypeFromString(const std::string& type)
		{
			if (type == "vertex")	return GL_VERTEX_SHADER;
			if (type == "fragment")	return GL_FRAGMENT_SHADER;

			return GL_NONE;
		}

		static std::unordered_map<unsigned int, std::string> ReadFromSource(const std::string& source)
		{
			// Collection of shaders within the file (assumes the file has multiple shaders within it)
			std::unordered_map<GLenum, std::string> shaderSources;

			// Declare shader type token(i.e. declaration of where each shader begins in the same file)
			const char* typeToken = "#shader-type";

			// Define the length of the token
			unsigned long long typeTokenLength = strlen(typeToken);

			// Locate the position of the first token
			unsigned long long tokenPosition = source.find(typeToken, 0);

			// Only continue if there is a token present in the file
			while (tokenPosition != std::string::npos)
			{
				// Define where the end of the token line is
				unsigned long long endOfLine = source.find_first_of("\r\n", tokenPosition);

				// The starting point of the shader type name
				unsigned long long begin = tokenPosition + typeTokenLength + 1;

				// Cache the shader type name
				std::string type = source.substr(begin, endOfLine - begin);

				// Get the next line (this is where the actual shader code begins)
				unsigned long long nextLinePos = source.find_first_not_of("\r\n", endOfLine);

				// Search for the next token in the source
				// Code before the token will be stored as part of this source
				tokenPosition = source.find(typeToken, nextLinePos);

				// Define the type of shader the current source is
				GLenum shaderType = ShaderTypeFromString(type);

				// Add the section of shader code to the sources collection
				shaderSources[shaderType] = source.substr(nextLinePos, tokenPosition - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
			}

			return shaderSources;
		}
	}

	Shader::Shader(const std::string& filepath)
		: m_Filepath(filepath)
	{
		m_Name = Utils::GetNameFromFilePath(filepath);

		Reload();
	}

	void Shader::Load(const std::string& source)
	{
		m_ShaderSource = Utils::ReadFromSource(source);
	}

	void Shader::Compile()
	{
		// Delete existing shader program handle first
		if (m_ID)
		{
			glDeleteProgram(m_ID);
			m_UniformLocations.clear();
		}

		// Create new shader program
		m_ID = glCreateProgram();

		// Used to keep track of how many shaders were attached to the program
		std::vector<unsigned int> attachedShaders;

		// Create all shaders
		for (auto& source : m_ShaderSource)
		{
			// Cache shader source code
			const char* sourceCode = source.second.c_str();

			// OpenGL handle to the shader
			unsigned int shaderHandle = 0;

			// Create a new shader
			shaderHandle = glCreateShader(source.first);

			// Copy source code into shader
			glShaderSource(shaderHandle, 1, &sourceCode, nullptr);

			// Compile the shader
			glCompileShader(shaderHandle);

			// Check compilation status
			int success;
			char infoLog[1024];
			glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &success);

			if (!success)
			{
				// Freak out if it didn't work
				glGetShaderInfoLog(shaderHandle, 1024, NULL, infoLog);
				Logger::Error("Shader compilation failed: [{0}]\n\t\t{1}", m_Name, infoLog);

				// Delete the shader
				glDeleteShader(shaderHandle);
			}
			else
			{
				// Attach it to the shader program
				glAttachShader(m_ID, shaderHandle);
				attachedShaders.push_back(shaderHandle);
			}
		}

		// Uh oh...
		if (attachedShaders.empty())
		{
			glDeleteProgram(m_ID);
			return;
		}

		// Link the program to the attached shaders
		glLinkProgram(m_ID);

		// Check compilation status
		int success;
		char infoLog[1024];
		glGetProgramiv(m_ID, GL_LINK_STATUS, &success);

		if (!success)
		{
			// Freak out if it didn't work
			glGetProgramInfoLog(m_ID, 1024, NULL, infoLog);
			Logger::Error("Shader linking failed\n{0}", infoLog);

			// Delete the shader program
			glDeleteProgram(m_ID);
		}

		// Delete shaders now they're no longer in use
		for (auto& shader : attachedShaders)
			glDeleteShader(shader);

		// Clear for good measure
		attachedShaders.clear();

		glUseProgram(0);
	}

	void Shader::Reload()
	{
		std::string source = Utils::ReadShaderFromFile(m_Filepath);

		Load(source);
		Compile();
	}

	void Shader::Bind()
	{
		if (m_ID == 0)
			Reload();

		glUseProgram(m_ID);
	}

	void Shader::Unbind()
	{
		glUseProgram(0);
	}

	/* EVERYTHING BELOW IS HERE ONLY TEMPORARILY - MOVE ASAP */

	void Shader::BindAttribute(unsigned int index, const std::string& name)
	{
		glBindAttribLocation(m_ID, index, name.c_str());
	}

	unsigned int Shader::GetUniformLocation(const std::string& name) const
	{
		// Check that the uniform exists
		if (m_UniformLocations.find(name) != m_UniformLocations.end())
			return m_UniformLocations[name];

		int uniformLocation = glGetUniformLocation(m_ID, name.c_str());

		if (uniformLocation != -1)
			m_UniformLocations[name] = uniformLocation;
		else
			Logger::Error("Invalid uniform name called: {0}", name);

		return uniformLocation;
	}

	void Shader::SetUint(const std::string& name, unsigned int value)
	{
		int location = GetUniformLocation(name.c_str());
		glUniform1ui(location, value);
	}

	void Shader::SetInt(const std::string& name, int value)
	{
		int location = GetUniformLocation(name.c_str());
		glUniform1i(location, value);
	}

	void Shader::SetFloat(const std::string& name, float value)
	{
		int location = GetUniformLocation(name.c_str());
		glUniform1f(location, value);
	}

	void Shader::SetVector2(const std::string& name, const Vector2f& value)
	{
		int location = GetUniformLocation(name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void Shader::SetVector3(const std::string& name, const Vector3f& value)
	{
		int location = GetUniformLocation(name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void Shader::SetVector4(const std::string& name, const Vector4f& value)
	{
		int location = GetUniformLocation(name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void Shader::SetMatrix3(const std::string& name, const Matrix3f& value)
	{
		int location = GetUniformLocation(name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, &value[0][0]);
	}

	void Shader::SetMatrix4(const std::string& name, const Matrix4f& value)
	{
		int location = GetUniformLocation(name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
	}
}