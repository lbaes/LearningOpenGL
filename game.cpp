//https://learnopengl.com/

#include <shader.h>
#include <glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>
#include <texture.h>
#include <triangle.h>
#include <cube.h>
#include <camera.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window, Camera * Cam);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void clearRGB(float, float, float, float);

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;
#define RES_DIR "./resources/"

float deltaTime = 0.0f;
bool firstMouse = true;
float lastX, lastY, yaw, pitch;

int main(int argc, char const *argv[])
{

	// glfw: initialize and configure
	std::cout << "Initializing glfw" << std::endl;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

	// glfw window creation
	std::cout << "Creating Window" << std::endl;
	GLFWwindow *window = glfwCreateWindow(SCR_WIDTH/2, SCR_HEIGHT/2, "LearnOpenGL", NULL, NULL); //glfwGetPrimaryMonitor()
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// glad: load all OpenGL function pointers
	std::cout << "Loading OpenGL Function Pointers" << std::endl;
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Print GL Version
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	// Shaders
	std::cout << "Creating Shaders" << std::endl;
	Shader shader(RES_DIR"/shaders/vShader.glsl", RES_DIR"/shaders/fShader.glsl");
	Shader lightShader(RES_DIR"/shaders/vLightShader.glsl", RES_DIR"/shaders/fLightShader.glsl");

	// Textures
	Texture texture1(RES_DIR"/wood.jpg", GL_RGB);

	// Cube
	Cube cube = Cube();
	Cube light = Cube();
	Camera cam(1920, 1080);
	glfwSetWindowUserPointer(window, (void *)&cam);

	shader.use();
	shader.set("Texture1", 0);
	texture1.bind(GL_TEXTURE0);

	glm::mat4 model, view, projection;
	model = glm::mat4(1.0f);
	
	glm::vec3 model_pos[] = {
		glm::vec3(-2.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(2.0f, 0.0f, 0.0f),
	};

	glm::vec3 light_pos;
	
	glEnable(GL_DEPTH_TEST);
	float lastFrameTime = 0.0f;
	float currentFrameTime = 0.0f;

	// Render loop
	while (!glfwWindowShouldClose(window))
	{
		// Delta Time
		currentFrameTime = glfwGetTime();
		deltaTime = currentFrameTime - lastFrameTime;
		lastFrameTime = currentFrameTime;

		// Input
		processInput(window, &cam);
		
		// Clear
		//clearRGB(49, 225, 140, 255);
		clearRGB(255, 255, 255, 255);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw
		shader.use();
		shader.set("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
		shader.set("lightColor",  glm::vec3(1.0f, 1.0f, 1.0f));
		shader.set("view", cam.getViewMatrix());
		shader.set("viewPos", cam.getCameraPos());
		shader.set("projection", cam.getProjectionMatrix());

		//Light Cube
		lightShader.use();
		light_pos = glm::vec3(0.0f, cos(currentFrameTime) * 2.0f, sin(currentFrameTime) * 2.0f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, light_pos);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		lightShader.set("view", cam.getViewMatrix());
		lightShader.set("projection", cam.getProjectionMatrix());
		lightShader.set("model", model);
		
		glBindVertexArray(light.getVAO());
		glDrawArrays(GL_TRIANGLES, 0, 36);

		shader.use();
		// Draws 3 cubes in different positions
		for (int i = 0; i < 3; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, model_pos[i]);
			shader.set("model", model);
			shader.set("lightPos", light_pos);
			glBindVertexArray(cube.getVAO());
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
	return 0;
}

// Process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window, Camera * cam)
{
	const float cameraSpeed = 1.0f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cam->processKeyboardInput('F', cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cam->processKeyboardInput('B', cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cam->processKeyboardInput('L', cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cam->processKeyboardInput('R', cameraSpeed);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	Camera * cam = (Camera *) glfwGetWindowUserPointer(window);
	if (cam == nullptr){
		return;
	}

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;


    cam->processMouseInput(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
	Camera * cam = (Camera *) glfwGetWindowUserPointer(window);
	if (cam == nullptr){
		return;
	}
	cam->processMouseScroll(yoffset);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// maps (0 - 255) to (0.0f - 1.0f)
float normalizeRGB(unsigned int value){
	return (float(value % 255)/255) * 1.0f;
}

// Set glClearColor using RGB values
void clearRGB(float v1, float v2, float v3, float v4){
glClearColor(	normalizeRGB(v1),
				normalizeRGB(v2),
				normalizeRGB(v3),
				normalizeRGB(v4));
}
