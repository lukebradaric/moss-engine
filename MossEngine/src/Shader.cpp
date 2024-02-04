#include "Shader.h"

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Logger.h"
#include "Renderer.h"
#include <sstream>

Shader::Shader(const std::string& filePath)
	: _filePath(filePath),
	_rendererId(0)
{
	ShaderProgramSource shaderProgramSource = ParseShader(filePath);
	_rendererId = CreateShader(shaderProgramSource.VertexSource, shaderProgramSource.FragmentSource);
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(_rendererId));
}

void Shader::Bind() const
{
	GLCall(glUseProgram(_rendererId));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3)
{
	unsigned int location = GetUniformLocation(name);
	GLCall(glUniform4f(location, f0, f1, f2, f3));
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (_uniformLocationCache.contains(name))
	{
		return _uniformLocationCache[name];
	}

	GLCall(int location = glGetUniformLocation(_rendererId, name.c_str()));

	if (location == -1)
	{
		std::stringstream stringStream;
		stringStream << "Unform location " << name << " doesn't exist.";
		Logger::LogWarning(stringStream.str().c_str());
	}

	_uniformLocationCache.insert({ name, location });
	return location;
}

ShaderProgramSource Shader::ParseShader(const std::string& filePath)
{
	std::ifstream stream(filePath);

	enum class ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				// vertex mode
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				// fragment mode
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	return
	{
		ss[0].str(),
		ss[1].str()
	};
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	GLCall(unsigned int id = glCreateShader(type));
	const char* src = source.c_str();
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == false)
	{
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		GLCall(glGetShaderInfoLog(id, length, &length, message));
		Logger::LogError("Failed to compile shader.");
		Logger::LogError(message);
		GLCall(glDeleteShader(id));
		return 0;
	}

	return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	GLCall(unsigned int program = glCreateProgram());
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return program;
}