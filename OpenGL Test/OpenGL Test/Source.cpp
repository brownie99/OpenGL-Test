#define _USE_MATH_DEFINES
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <include/glad/glad.h>
#include <glfw-3.3.bin.WIN32/include/GLFW/glfw3.h>
#include <stb_image.h>
#include <cstdlib>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include <Shader.h>

float mixer = 0.5f;
float xScale = 1.0f;



int main()
{
	float r;
	float g;
	float b;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glViewport(0, 0, 800, 600);

	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	glfwSetKeyCallback(window, key_callback);

	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	float tringley[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 

	};

	float texCoords[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.5f, 0.0f
	};
	
	unsigned int trings[] = {
		0, 1, 2,
		0, 3, 2
	};

	float triangle2[] = {
	-1.0f, -1.0f, 0.0f,
	-1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 1.0f
	};


	unsigned int indices[] = {  // note that we start from 0!
		0, 4, 7,   // first triangle
		7, 4, 1,    // second triangle
		1, 4, 8,
		8, 4, 2,
		2, 4, 5,
		5, 4, 3,
		3, 4, 6,
		6, 4, 0
	};

	std::cout << "Making Shader" << std::endl;
	Shader ourShader("vShader.vs", "fShader.fs");

	
	



	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);

	unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	if (data) 
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);


	unsigned int texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	unsigned char *data2 = stbi_load("blue.jpg", &width, &height, &nrChannels, 0);
	if (data2)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);

	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data2);

	unsigned int EBO;
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	unsigned int VBOs[3], VAOs[3];
	glGenVertexArrays(3, VAOs);
	glGenBuffers(3, VBOs);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int tringles;
	glGenBuffers(1, &tringles);
	glBindVertexArray(VAOs[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tringley), tringley, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tringles);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(trings), trings, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAOs[1]);	// note that we bind to a different VAO now
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);	// and a different VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
	glEnableVertexAttribArray(0);

	

	void processInput(GLFWwindow *window);
	
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		
		r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		r = 0.3f;
		g = 0.5f;
		b = 0.6f;
		//std::cout << r << std::endl;

		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue + (M_PI/3)) / 2.0f) + 0.5f;
		float blueValue = (sin(timeValue + ((M_PI*2) / 3)) / 2.0f) + 0.5f;
		float redValue = (sin(timeValue) / 2.0f) + 0.5f;
		//int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

		glClearColor(r, g, b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//glBindVertexArray(VAOs[0]);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		ourShader.use();
		ourShader.setFloat4f("ourColor",redValue, greenValue, blueValue, 1.0f);
		glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
		glUniform1i(glGetUniformLocation(ourShader.ID, "texture2"), 1);
		glUniform1f(glGetUniformLocation(ourShader.ID, "mixer"), mixer);
		

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));


		glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);

		glm::mat4 projection = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);

		projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		

		int modelLoc = glGetUniformLocation(ourShader.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		int viewLoc = glGetUniformLocation(ourShader.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		int projectionLoc = glGetUniformLocation(ourShader.ID, "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
		
		// note that we're translating the scene in the reverse direction of where we want to move
		

		glm::mat4 trans = glm::mat4(1.0f);
		bool shouldTrans = false;
		if (shouldTrans) {
			trans = glm::translate(trans, glm::vec3(0.5f, 0.5f, 0.0f));
			trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
			trans = glm::scale(trans, glm::vec3(xScale, 1.0, 1.0));
		}
		unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
		
		glBindVertexArray(VAOs[2]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//glBindVertexArray(VAOs[2]);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[1]);
		//glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 6);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}



void processInput(GLFWwindow *window)
{
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	std::cout << "input" << std::endl;
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		//mixer = mixer + 0.1f;
		std::cout << "" << std::endl;
	}

	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		//mixer = mixer - 0.1f;
		std::cout << "" << std::endl;

	}

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		std::cout << "scale up" << std::endl;
		xScale = xScale * 2.0f;
	}

	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		xScale = xScale * 0.5f;
	}
}


