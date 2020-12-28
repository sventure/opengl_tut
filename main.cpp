//#include"libs.h"

#include "libs.h"
#include "shaders.h"
#include "stb_image.h"

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);


int main()
{
	glfwInit();                                                         //initialize glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                      //sets major and minor version to 3.0+
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);      //glfw to use core-profile, telling GLFW we want to use the core-profile means we'll get access to a smaller subset of OpenGL features without backwards-compatible features we no longer need.

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Pogchamp poggers", NULL, NULL);    // create window 800x600 with name hellowindow
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

	glEnable(GL_DEPTH_TEST);                               //enables Z buffer

	Shader ourShader("D:/Visual Studio repo/opengl_tut/shaders/vertexShader.vs","D:/Visual Studio repo/opengl_tut/shaders/fragmentShader.fs");      //use shader files



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

	unsigned int indices[] = {
		0, 1, 3,          //first triangle
		1, 2, 3           //second triangle
	};

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),                                    //different cube positions in the world
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);    //check https://learnopengl.com/Getting-started/Hello-Triangle under "Linking Vertex Attributes" for reference
	glEnableVertexAttribArray(0);

	//color attrib
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3* sizeof(float)));    
	//glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);


	//texture 1
	unsigned int texture1;
	glGenTextures(1, &texture1);  //takes as input how many textures we want to generate and stores them in a unsigned int array given as its second argument
	glBindTexture(GL_TEXTURE_2D, texture1);  //bind textures
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  //tex wrapping for x coord (s)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  //tex wrapping for y coord (t)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  //tex filtering for minify
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  //tex filtering for magnify
	// load and generate the texture
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("D:/Visual Studio repo/opengl_tut/Textures/container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		
		/* ^^^  1st argument specifies the texture target
			    2nd argument specifies the mipmap level
			    3rd argument tells OpenGL in what kind of format we want to store the texture
			    4th and 5th argument sets the width and height of the resulting texture. 
				7th and 8th argument specify the format and datatype of the source image.
				The last argument is the actual image data.*/

	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	//texture 1
	unsigned int texture2;
	glGenTextures(1, &texture2);  //takes as input how many textures we want to generate and stores them in a unsigned int array given as its second argument
	glBindTexture(GL_TEXTURE_2D, texture2);  //bind textures
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  //tex wrapping for x coord (s)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  //tex wrapping for y coord (t)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  //tex filtering for minify
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  //tex filtering for magnify
	// load and generate the texture
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load("D:/Visual Studio repo/opengl_tut/Textures/pepsi.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);   //rgba here for alpha (png transparency)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	ourShader.use(); // don't forget to activate the shader before setting uniforms!  
	glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0); // set it manually
	ourShader.setInt("texture2", 1); // or with shader class

	glViewport(0, 0, 800, 600);                                                 //create viewport
	
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// ^^^ When the window is first displayed framebuffer_size_callback gets called as well with the resulting window dimensions.\

	while (!glfwWindowShouldClose(window)) 
	{
		processInput(window);

		glClearColor(0.7f, 0.2f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);              //clear the color and depth buffer 
/*
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;                               //changing color
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
	
		glUseProgram(shaderProgram);                           //uses previously defined shader program
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);       //finds uniform var location with corresponding 4 floats (colors in this case)
		*/

		glActiveTexture(GL_TEXTURE0);                          //activate texture 1
		glBindTexture(GL_TEXTURE_2D, texture1);                //bind texture 1
		glActiveTexture(GL_TEXTURE1);                          //activate texture 2
		glBindTexture(GL_TEXTURE_2D, texture2);                //bind texture 2 
		ourShader.use();
		glBindVertexArray(VAO);                                //bind VAO again with updated settings 
		glBindBuffer(GL_ARRAY_BUFFER, EBO);                    //bind EBO again with updated settings 
	//  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);             //wireframe mode
	//	glDrawArrays(GL_TRIANGLES, 0, 36);                      //draw Triangle
	//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);   //draw elements



		glm::mat4 view = glm::mat4(1.0f);                                                     //view matrix
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));                            //move it ahead in the z axis

		glm::mat4 projection;                                                                 //projection matrix
		projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);    //give it perspective vision

		int viewLoc = glGetUniformLocation(ourShader.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));                       //set view value

		int projLoc = glGetUniformLocation(ourShader.ID, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));                 //set pr value

		glm::mat4 model = glm::mat4(1.0f);                                                    //model matrix

		for (unsigned int i = 0; i < 10; i++)
		{
			//glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
			int modelLoc = glGetUniformLocation(ourShader.ID, "model");
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			model = glm::mat4(1.0f);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

	//	model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));         //rotate it in the x axis


	    /*glm::mat4 trans = glm::mat4(1.0f);                                                    //trans is a identity matrix
        trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));            //rotate it by 90 degrees in z axis (Our polygon is in XY plane)
        trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));                                  //scale it down to half the size

        unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");          //find uniform transform in our shader code
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans)); */

		/*glm::mat4 trans = glm::mat4(1.0f);                                                 //identity matrix
		trans = glm::translate(trans, glm::vec3(sin((float)glfwGetTime() * 2), cos((float)glfwGetTime() * 2), sin((float)glfwGetTime() * 2))); //place it to the bottom right if the screen
		trans = glm::rotate(trans, (float)glfwGetTime() * 5.0f, glm::vec3(0.0f, 0.0f, 1.0f));                                                 //rotate it in the z axis by time
		trans = glm::scale(trans, glm::vec3(sin((float)glfwGetTime() * 2), sin((float)glfwGetTime() * 2), sin((float)glfwGetTime() * 2)));   //keeps increasing and decreasing the size from 1 to 0 to 1

		unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");          //find uniform transform in our shader code
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans)); 

		/* ^^^      1st argument specifies the uniform location
					2nd argument tells OpenGL how many matrices we'd like to send
					3rd argument asks us if we want to transpose our matrix, that is to swap the columns and rows
					The last argument is the actual matrix data, we convert the data with GLM's built-in function value_ptr to match OpenGL's expectations */ 

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