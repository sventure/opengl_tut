//#include"libs.h"

#include"libs.h"
#include"shaders.h"

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);


int main()
{
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

	Shader ourShader("D:/OpenGL Shaders/vertexShader.txt","D:/OpenGL Shaders/fragmentShader.txt");



	float vertices[] = {
		//vertices      
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom left 
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom right 
	 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f   // top 
	};

	unsigned int indices[] = {
		0, 1, 2          //first triangle
	};

	unsigned int VBO, VAO, EBO;
	glGenBuffers(1, &EBO);                                                      //generate an element buffer
	glGenVertexArrays(1, &VAO);                                                 //generate a vertex array
	glGenBuffers(1, &VBO);                                                      //generate a vertex buffer

	glBindVertexArray(VAO);                                                     //binds vertex array object

	glBindBuffer(GL_ARRAY_BUFFER, VBO);                                         //binds vertex buffer to GL_ARRAY_BUFFER buffer type
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);  //copies the buffer info to the currently bound buffer

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	/* ^^^  1st argument is the type of the buffer we want to copy data into
	        2nd argument specifies the size of the data (in bytes) we want to pass to the buffer
			3rd parameter is the actual data we want to send
			4th parameter specifies how we want the graphics card to manage the given data. */

	//pos attrib
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);    //check https://learnopengl.com/Getting-started/Hello-Triangle under "Linking Vertex Attributes" for reference
	glEnableVertexAttribArray(0);

	//color attrib
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));    
	glEnableVertexAttribArray(1);

	glViewport(0, 0, 800, 600);                                                 //create viewport
	
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// ^^^ When the window is first displayed framebuffer_size_callback gets called as well with the resulting window dimensions.

	while (!glfwWindowShouldClose(window)) 
	{
		processInput(window);


		glClearColor(0.7f, 0.2f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);              //clear the color buffer, the entire color buffer will be filled with the color as configured  
/*
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;                               //changing color
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
	
		glUseProgram(shaderProgram);                           //uses previously defined shader program
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);       //finds uniform var location with corresponding 4 floats (colors in this case)
		*/
		ourShader.use();
		glBindVertexArray(VAO);                                //bind VAO again with updated settings (update the array??)
		glBindBuffer(GL_ARRAY_BUFFER, EBO);                    //bind EBO again with updated settings (update the buffer??)
	//  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);             //wireframe mode
		glDrawArrays(GL_TRIANGLES, 0, 3);                      //draw Triangle
	//	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);   //draw elements



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