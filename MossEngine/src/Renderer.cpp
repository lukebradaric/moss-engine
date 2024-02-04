#include "Renderer.h"
#include <iostream>
#include <sstream>
#include "Logger.h"

void GLClearError()
{
	// While there are errors
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	// While there are errors
	while (GLenum error = glGetError())
	{
		std::stringstream errorStream;
		errorStream << error << " " << function << " " << file << ":" << line;
		Logger::LogError(errorStream.str().c_str(), "OpenGL Error");
		return false;
	}

	return true;
}

void Renderer::Clear() const
{

}

void Renderer::Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const
{
	shader.Bind();
	vertexArray.Bind();
	indexBuffer.Bind();

	GLCall(glDrawElements(GL_TRIANGLES, indexBuffer.GetCount(), GL_UNSIGNED_INT, nullptr));
}