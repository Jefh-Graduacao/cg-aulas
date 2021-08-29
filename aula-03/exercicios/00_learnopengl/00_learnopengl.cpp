#include <iostream>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "gl_utils.h"

float dx = 0.0f, dy = 0.0f, dz = 5.0f;

glm::mat4 model(1.0f);
glm::mat4 viewMatrix = glm::mat4(1.0);

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	static bool gWireframe = 0;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_M && action == GLFW_PRESS)
	{
		gWireframe = !gWireframe;
		if (gWireframe)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		dx -= 1.0;
	}

	else if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		dx += 1.0;
	}
	else if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		dy += 1.0;
	}
	else if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		dy -= 1.0;
	}
	else if (key == GLFW_KEY_Q && action == GLFW_PRESS)
	{
		dz += 1.0;
	}
	else if (key == GLFW_KEY_Z && action == GLFW_PRESS)
	{
		dz -= 1.0;
	}
	else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		dx = dy = 0.0f;
		dz = 5.0;
	}
	else if (key == GLFW_KEY_P && action == GLFW_PRESS) {
		std::cout << "dx,dy,dz = (" << dx << "," << dy << "," << dz << ")" << std::endl;
		std::cout << "view matrix " << glm::to_string(viewMatrix) << std::endl;
	}
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
	glfwSetKeyCallback(window, key_callback);

	// create and bind vertex data
	//float vertices[] =
	//{
	//	// first triangle
	//	 0.2f,  0.2f, 0.0f,  /* top right */		1.0f, 0.5f, 0.2f,
	//	 0.2f, -0.2f, 0.0f,  /* bottom right */		1.0f, 0.5f, 0.2f,
	//	-0.2f,  0.2f, 0.0f,  /* top left */			1.0f, 0.5f, 0.2f,
	//	// second triangle
	//	 0.2f, -0.2f, 0.0f,  /* bottom right */		1.0f, 0.5f, 0.2f,
	//	-0.2f, -0.2f, 0.0f,  /* bottom left */		1.0f, 0.5f, 0.2f,
	//	-0.2f,  0.2f, 0.0f,  /* top left */			1.0f, 0.5f, 0.2f,

	//	// third triangle (roof)
	//	 0.2f,  0.2f, 0.0f,  /* bottom right */		1.0f, 1.0f, 0.0f,
	//	-0.2f,  0.2f, 0.0f,  /* bottom left */		1.0f, 1.0f, 0.0f,
	//	 0.0f,  0.6f, 0.0f,  /* top */				1.0f, 1.0f, 0.0f,
	//};

	float vertices[] =
	{
		// positions          // colors           
		 0.5f,  0.5f, 0.5f,   1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, 0.5f,   1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, 0.5f,   1.0f, 1.0f, 0.0f,

		// positions          // colors           
		 0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,

		-0.5f,  0.5f, 0.5f,   1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, 0.5f,   1.0f, 1.0f, 1.0f,
		 0.0f,  0.1f, 0.5f,   1.0f, 1.0f, 1.0f,

		 -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,   1.0f, 1.0f,  1.0f,
		 0.0f,  0.1f, -0.5f,   1.0f, 1.0f,  1.0f,
	};

	unsigned int index[] = 
	{
		3, 1, 0, // near / front
		1, 3, 2,
		5, 7, 4, // far / near
		7, 5, 6,
		5, 0, 1, // right
		0, 5, 4,
		7, 0, 4, // top
		0, 7, 3,
		6, 1, 2, // bottom
		1, 6, 5,
		6, 3, 7,
		3, 6, 2
	};

	unsigned int vbo, vao, ibo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

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

	// Modification matrix (manipulated in the callbacks)
	unsigned int modelMatrixId = glGetUniformLocation(shaderProgram, "model");

	// Camera

	unsigned int viewMatrixId = glGetUniformLocation(shaderProgram, "view");

	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	glm::mat4 projection(1.0);
	projection = glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.4f, 10.0f);

	unsigned int projectionMatrixId = glGetUniformLocation(shaderProgram, "projection");
	glUniformMatrix4fv(projectionMatrixId, 1, GL_FALSE, glm::value_ptr(projection));

	// 

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		// Camera transformation
		viewMatrix = glm::mat4(1.0f);
		viewMatrix = glm::lookAt(glm::vec3(dx, dy, dz), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(viewMatrixId, 1, GL_FALSE, &viewMatrix[0][0]);
		//

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(vao);
		
		//glDrawArrays(GL_TRIANGLES, 0, 9);
		glDrawElements(GL_TRIANGLES, sizeof(index), GL_UNSIGNED_INT, 0);


		glUniformMatrix4fv(modelMatrixId, 1, GL_FALSE, glm::value_ptr(model));

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);

	glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;
}