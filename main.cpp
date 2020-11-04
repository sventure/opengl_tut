//#include"libs.h"

#include"libs.h"

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,                     //triangle vertices
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
	};	

	/* In the main function we first initialize GLFW with glfwInit, after which we can configure GLFW using glfwWindowHint.
	The first argument of glfwWindowHint tells us what option we want to configure, where we can select the option from a
	large enum of possible options prefixed with GLFW_. The second argument is an integer that sets the value of our option. */



	glfwInit();                                                         //initialize glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                      //sets major and minor version to 3.0+
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);      //glfw to use core-profile, telling GLFW we want to use the core-profile means we'll get access to a smaller subset of OpenGL features without backwards-compatible features we no longer need.

	GLFWwindow* window = glfwCreateWindow(800, 600, "Hello Window", NULL, NULL);    // create window 800x600 with name hellowindow
	if (window == NULL)
	{
		cout << "Failed to create window" << endl;       
		glfwTerminate();                                               
		return -1;
	}
	glfwMakeContextCurrent(window);



	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;                            //initialize glad
		return -1;
	}

	unsigned int VBO;
	glGenBuffers(1, &VBO);                                                      //generate a vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);                                         //binds the created buffer to GL_ARRAY_BUFFER buffer type

	glViewport(0, 0, 800, 600);                                                 //create viewport
	
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// ^^^ When the window is first displayed framebuffer_size_callback gets called as well with the resulting window dimensions.

	while (!glfwWindowShouldClose(window)) 
	{
		processInput(window);

		glClearColor(0.7f, 0.2f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);              //clear the color buffer, the entire color buffer will be filled with the color as configured  

		glfwSwapBuffers(window);         //will swap the color buffer that is used to render to during this render iteration and show it as output to the screen.
		glfwPollEvents();                //checks if any events are triggered
	}

	glfwTerminate();                     //clean/delete all of GLFW's resources that were allocated.
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

/* ^^^ The framebuffer size function takes a GLFWwindow as its first argument and two integers indicating the new window dimensions.
Whenever the window changes in size, GLFW calls this function and fills in the proper arguments for you to process. */

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)             //checks for key inputs
		glfwSetWindowShouldClose(window, true);
}