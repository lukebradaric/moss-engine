#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Shader.cpp"
#include "Logger.hpp"

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	//glewInit();
	if (glewInit() != GLEW_OK)
	{
		Logger::LogError("Glew Init Error.");
	}

	Logger::LogInfo((const char*)glGetString(GL_VERSION));

	float positions[6] =
	{
	   -0.5f, -0.5f,
		0.0f,  0.5f,
		0.5f, -0.5f
	};

	// Generate a buffer, and assign ID to buffer int
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	ShaderProgramSource shaderSource = ParseShader("res/shaders/Basic.shader");
	unsigned int shaderProgram = CreateShader(shaderSource.VertexSource, shaderSource.FragmentSource);
	glUseProgram(shaderProgram);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;
}