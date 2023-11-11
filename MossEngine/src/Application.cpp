#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Renderer.h"
#include "Shader.cpp"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "Logger.h"


int main(void)
{
	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
	{
		Logger::LogError("Glew Init Error.");
	}

	Logger::LogInfo((const char*)glGetString(GL_VERSION));

	{
		float positions[] =
		{
		   -0.5f, -0.5f,
			0.5f, -0.5f,
			0.5f,  0.5f,
		   -0.5f,  0.5f
		};

		unsigned int indices[] =
		{
			0, 1, 2,
			2, 3, 0
		};

		unsigned int vao;
		GLCall(glGenVertexArrays(1, &vao));
		GLCall(glBindVertexArray(vao));

		VertexBuffer vertexBuffer(positions, 4 * 2 * sizeof(float));

		GLCall(glEnableVertexAttribArray(0));
		GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));

		IndexBuffer indexBuffer(indices, 6);

		ShaderProgramSource shaderSource = ParseShader("res/shaders/Basic.shader");
		unsigned int shaderProgram = CreateShader(shaderSource.VertexSource, shaderSource.FragmentSource);
		GLCall(glUseProgram(shaderProgram));

		GLCall(int location = glGetUniformLocation(shaderProgram, "u_Color"));
		ASSERT(location != -1);
		GLCall(glUniform4f(location, 0.0f, 1.0f, 1.0f, 1.0f));

		GLCall(glBindVertexArray(0));
		GLCall(glUseProgram(0));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

		while (!glfwWindowShouldClose(window))
		{
			GLCall(glClear(GL_COLOR_BUFFER_BIT));

			GLCall(glUseProgram(shaderProgram));
			GLCall(glUniform4f(location, 1.0f, 0.4f, 0.8f, 1.0f));

			GLCall(glBindVertexArray(vao));
			indexBuffer.Bind();

			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

			glfwSwapBuffers(window);

			glfwPollEvents();
		}

		GLCall(glDeleteProgram(shaderProgram));
	}

	glfwTerminate();
	return 0;
}