//#include"libs.h"

#include"libs.h"

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"                                                                          //a basic vertex shader
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"   ourColor = aColor;\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"                                                                          //orange fragment shader
"{\n"
"   FragColor = vec4(ourColor, 1.0);\n"
"}\n\0";

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

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);                            //create vertex shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);                                              //attach created vertex shader to the vertex shader source (init at the top of the code)

	int success;
	char infoLog[512];

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);	                                                                            
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;                      //checks if vertex shader works
	}

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);                        //create fragment shader
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);                                            //attach created fragment shader to the fragment shader source (init at the top of the code)
	
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;         //checks if fragment shader works
	}

	unsigned int shaderProgram;                            
	shaderProgram = glCreateProgram();                       //create shader program to render

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);           //attach/link both shaders to the program
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);                             //checks if program works
		cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);                    //delete vertex and fragment shader after usnig them



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

		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;                               //changing color
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
	
		glUseProgram(shaderProgram);                           //uses previously defined shader program
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);       //finds uniform var location with corresponding 4 floats (colors in this case)
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