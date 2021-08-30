#include <iostream>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "gl_utils.h"

glm::mat4 model(1.0f);

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	
	glm::mat4 matriz_inicial(1.0f);
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		model = glm::scale(matriz_inicial, glm::vec3(2.0f, 0.5f, 3.0f));

	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		model = glm::rotate(matriz_inicial, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		model = glm::translate(matriz_inicial, glm::vec3(-0.5f, -0.5f, 0.0f));
}

const int canvasWidth = 900;
const int canvasHeight = canvasWidth;

int main()
{
	if (!glfwInit())
	{
		std::cout << "Falha ao inicializar GLFW" << std::endl;
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(canvasWidth, canvasHeight, "Learn OpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Falha ao criar janela com GLFW" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (gl3wInit())
	{
		std::cout << "Falha ao inicializar o GL3W" << std::endl;
		return -1;
	}

	if (!gl3wIsSupported(3, 2))
	{
		std::cout << "OpenGL 3.2 not supported\n" << std::endl;
		return -1;
	}

	glViewport(0, 0, canvasWidth, canvasHeight);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// create and bind vertex data
	float vertices[] =
	{
		// first triangle
		 0.2f,  0.2f, 0.0f,  /* top right */		1.0f, 0.5f, 0.2f,
		 0.2f, -0.2f, 0.0f,  /* bottom right */		1.0f, 0.5f, 0.2f,
		-0.2f,  0.2f, 0.0f,  /* top left */			1.0f, 0.5f, 0.2f,
		// second triangle
		 0.2f, -0.2f, 0.0f,  /* bottom right */		1.0f, 0.5f, 0.2f,
		-0.2f, -0.2f, 0.0f,  /* bottom left */		1.0f, 0.5f, 0.2f,
		-0.2f,  0.2f, 0.0f,  /* top left */			1.0f, 0.5f, 0.2f,

		// third triangle (roof)
		 0.2f,  0.2f, 0.0f,  /* bottom right */		1.0f, 1.0f, 0.0f,
		-0.2f,  0.2f, 0.0f,  /* bottom left */		1.0f, 1.0f, 0.0f,
		 0.0f,  0.6f, 0.0f,  /* top */				1.0f, 1.0f, 0.0f,
	};

	unsigned int vbo, vao;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Colors
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//

	// create, compile and link shaders
	const int sourceMaxSize = 1024 * 256;
	char vertexShaderSource[sourceMaxSize];
	parse_file_into_str("vertex_shader.glsl", vertexShaderSource, sourceMaxSize);

	unsigned int vertexShaderId = glCreateShader(GL_VERTEX_SHADER);

	const GLchar* vShaderSource = (const GLchar*)vertexShaderSource;
	glShaderSource(vertexShaderId, 1, &vShaderSource, NULL);
	glCompileShader(vertexShaderId);

	char fragmentShaderSource[sourceMaxSize];
	parse_file_into_str("fragment_shader.glsl", fragmentShaderSource, sourceMaxSize);

	unsigned int fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar* fShaderSource = (const GLchar*)fragmentShaderSource;
	glShaderSource(fragmentShaderId, 1, &fShaderSource, NULL);
	glCompileShader(fragmentShaderId);

	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShaderId);
	glAttachShader(shaderProgram, fragmentShaderId);
	glLinkProgram(shaderProgram);

	glUseProgram(shaderProgram);

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);
	//

	unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 9);

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteProgram(shaderProgram);
	glfwTerminate();
	return 0;
}