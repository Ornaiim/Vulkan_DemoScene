#define STB_IMAGE_IMPLEMENTATION
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <vector>
#include <iostream>

#include "VulkanRenderer.h"

GLFWwindow* window;
VulkanRenderer vulkanRenderer;

void initWindow(std::string wName = "Test window", const int width = 800, const int height = 600)
{
	// Initialise GLFW
	glfwInit();

	// Set GLFW to NOT work with OpenGL
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(width, height, wName.c_str(), nullptr, nullptr);
}

int main()
{
	// Create window
	initWindow("Test window", 1366, 768);

	// Create Vulkan renderer instance
	if (vulkanRenderer.init(window) == EXIT_FAILURE)
	{
		return EXIT_FAILURE;
	}

	float angle = 0.0f;
	float deltaTime = 0.0f;
	float lastTime = 0.0f;

	int helicopter = vulkanRenderer.createMeshModel("Models/uh60.obj");

	// Loop until close
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		float now = glfwGetTime();
		deltaTime = now - lastTime;
		lastTime = now;

		angle += 10.0f * deltaTime;
		if (angle > 360.0f) { angle -= 360.0f; }

		/*glm::mat4 firstModel(1.0f);
		glm::mat4 secondModel(1.0f);

		firstModel = glm::translate(firstModel, glm::vec3(-1.0f, 0.0f, -1.0f));
		firstModel = glm::rotate(firstModel, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));

		secondModel = glm::translate(secondModel, glm::vec3(1.0f, 0.0f, -3.0f));
		secondModel = glm::rotate(secondModel, glm::radians(-angle * 10), glm::vec3(0.0f, 0.0f, 1.0f));

		vulkanRenderer.updateModel(0, firstModel);
		vulkanRenderer.updateModel(1, secondModel);*/

		glm::mat4 testMat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
		testMat = glm::rotate(testMat, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		vulkanRenderer.updateModel(helicopter, testMat);

		vulkanRenderer.draw();
	}

	vulkanRenderer.cleanup();

	// Destroy GLFW window and stop GLFW
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}