#include<iostream>
#include<cmath>
#include<random>

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<shaders/shader_s.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG
#include<image/stb_image.h>

glm::vec3 cameraPos   = glm::vec3(1.0f, 0.0f,  10.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

	const float cameraSpeed = 0.009f; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraUp;
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraUp;
	// std::cout<<cameraPos.x<<", "<<cameraPos.y<<", "<<cameraPos.z<<std::endl;
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_ANY_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(800, 800, "Opengl", NULL, NULL);
	if(window == NULL)
	{
		std::cout<<"Failed to create GLFW window."<<std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout<<"Failed to initialize GLAD"<<std::endl;
		return -1;
	}
	glViewport( 0, 0, 800, 800);

	Shader ourShader("shader_class/vert.vs","shader_class/frag.fs");

	float vertices[] = {
    // positions           
     0.5f,  0.5f, -0.5f,      // top right
     0.5f, -0.5f, -0.5f,      // bottom right
    -0.5f, -0.5f, -0.5f,      // bottom left
    -0.5f,  0.5f, -0.5f,      // top left 
     0.5f,  0.5f,  0.5f,      
     0.5f, -0.5f,  0.5f,      
    -0.5f, -0.5f,  0.5f,      
    -0.5f,  0.5f,  0.5f,   

	// colors
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 0.0f,

	// texture coords
	1.0f, 1.0f,
	1.0f, 0.0f,
	0.0f, 0.0f,
	0.0f, 1.0f,
	0.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 0.0f     
	};
	// float vertices[] = {
    // // positions          // colors           // texture coords
    //  0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
    //  0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    // -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    // -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // top left 
    //  0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   
    //  0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   
    // -0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   
    // -0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f     
	// };

	// float vertices[] = {
	// 	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    //  0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
    //  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    //  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    // -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    // -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    // -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    //  0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    //  0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    //  0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    // -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    // -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    // -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    // -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    // -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    // -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    // -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    // -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    //  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    //  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    //  0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    //  0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    //  0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    //  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    // -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    //  0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
    //  0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    //  0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    // -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    // -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    // -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    //  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    //  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    //  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    // -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    // -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	// };

	unsigned int indices[] = {
		 0,  1,  3,
		 1,  3,  2,
		 0,  1,  5,
		 0,  4,  5,
		 4,  5,  6,
		 6,  7,  4,
		 3,  2,  6,
		 7,  6,  3,
		 0,  3,  7,
		 0,  4,  7,
		 5,  6,  2,
		 1,  2,  5
	};

	glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -1.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -1.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -1.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f),
        glm::vec3(-0.6f,  0.0f,  0.0f)
    };
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(float), (void*)(24 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0 * sizeof(float), (void*)(48 * sizeof(float)));
	glEnableVertexAttribArray(2); 

	

    unsigned int texture1;
    unsigned int texture2;
    
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1); 
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); 
    
    const char* path_1 = "../resource/container.jpg";
    unsigned char *data = stbi_load(path_1, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    
    
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
	const char* path_2 = "../resource/awesomeface.png";
    data = stbi_load(path_2, &width, &height, &nrChannels, 0);
    if (data)
    {
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

	ourShader.use();
    ourShader.setInt("texture1", 0);    
    ourShader.setInt("texture2", 1);
    
    
	 

	// glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection;

	projection = glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f);
	ourShader.setMat4("projection", projection);	
	
	glEnable(GL_DEPTH_TEST);
			
    
    // float j = 0;	
    // float bc;
    // float time ;
    
    // glm::mat4 model_1 = glm::mat4(1.0f);
    // model_1 = glm::translate(model_1, glm::vec3(0.6f, 2.1f, -3.5f));
    // model_1 = glm::rotate(model_1, glm::radians(45.0f), glm::vec3(1.0f,-1.0f,0.0f));
    // std::cout.precision(10);
    // for(int i = 0; i < 4; i++)
    // {
    //     for(int j = 0; j < 4; j++)
    //     {
    //         std::cout<<"\t"<<model_1[i][j];
    //     }
    //     std::cout<<"\n";
    // }
    
    
    // glm::mat4 model_2 = glm::mat4(1.0f);
    // model_2 = glm::translate(model_2, glm::vec3(0.6f, -2.1f, -3.5f));
    
    std::random_device rd;
    std::uniform_real_distribution<double> dist(-1.0,1.0);

    // glm::vec3 tempdirection = glm::vec3( (float)dist(rd),  (float)dist(rd), (float)dist(rd) );

    // new data
    int noOfCube = 10;
    glm::vec3 newCubePos[noOfCube];
    int gaping = 4;
    for(int i=0; i<noOfCube; i++){
        newCubePos[i] = glm::vec3( (float)(dist(rd)*gaping), (float)(dist(rd)*gaping),(float)(dist(rd)*gaping) );
    }
    glm::vec3 newCubeDir[noOfCube];
    for(int i=0; i<noOfCube; i++){
        newCubeDir[i] = glm::vec3( (float)dist(rd), (float)dist(rd), (float)dist(rd) );
    }
    float angle = 0.0f;

	while(!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor( 0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // time = glfwGetTime();
        // bc = (sin(time)/2.0f + 0.5f)/2;
        // ourShader.setVec3("uColor", 0.7843137255f, 0.3921568627f, bc);
        
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		ourShader.setMat4("view", view);
		
        // model_1 = glm::rotate( model_1, glm::radians(1.0f), tempdirection );
        // ourShader.setMat4("model", model_1);
        // glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        // ourShader.setMat4("model", model_2);
        // glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            glm::mat4 model[sizeof(newCubePos)] = glm::mat4(1.0f);
            
		    angle += (0.5f );
            if((angle/90.0f)==0){angle += 0.5f;}
            if(angle >= 360.0f){ angle = 0.0f;} 
		    for(int i =0; i<sizeof(newCubePos)/12; i++)
            {
		       model[i] = glm::translate(model[i], newCubePos[i]);
            //    std::cout<<angle<<std::endl;
               model[i] = glm::rotate(model[i], glm::radians(angle), newCubeDir[i]);
		       ourShader.setMat4("model", model[i]);
               glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		        //    glDrawArrays(GL_TRIANGLES, 0, 36);
            }
            // j = j + 0.1;

		


		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glDeleteTextures(1, &texture);
	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &VBO);
	glDeleteVertexArrays(1, &EBO);

	glfwTerminate();

	return 0;
}