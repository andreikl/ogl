// Include standard headers
#include <stdio.h>
#include <stdlib.h>

#include <iostream> // std::cout, std::fixed
#include <iomanip> // precision
#include <sstream> // stringstream
#include <string> // string

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// user includes
#include "core.hpp"
#include "input.hpp"
#include "app.hpp"

//#include "core.h"

// test draw ------------
GLuint programID;
GLuint vertexbuffer;
GLuint vertexArrayID;
// end test draw --------

// Application
Application* that = nullptr;

Application::Application() {
    this->startTime = 0.0f;

    if (that) {
        throw "instance of Application is already created!";
    }
    that = this;
}

Application::~Application() {
    this->dispose();
    that = nullptr;
}

/**
* Get window instance and size of the window
*/
GLFWwindow* Application::getWindow() const {
    return window;
};
int Application::getWidth() const {
    return width;
};
int Application::getHeight() const {
    return height;
};
// gets and sets view camera
glm::mat4 Application::getView() const {
    return this->view;
};
void Application::setView(glm::mat4 view) {
    this->view = view;
};

// gets projection matrix
glm::mat4 Application::getProjection() const {
    return this->projection;
};

double Application::getStartTime() const {
    return this->startTime;
}

double Application::getLastFrameDelta() const {
    return this->lastFrameDelta;
}

void Application::run() {
    double lastTime = 0.0;
    double lastFrameTime = 0.0;

    do {
        double currentTime = glfwGetTime();
        lastFrameDelta = currentTime - lastFrameTime;
        lastFrameTime = currentTime;

        // Clear the screen.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (this->input) {
			this->input->handle();
		}
        this->draw();

        std::stringstream str_time;
        str_time << std::fixed << std::setprecision(1) << glfwGetTime() - this->getStartTime();
        printText2D(str_time.str().c_str(), 10, 10, 10);

		// end test draw ------------
		//glUseProgram(programID);
		//glEnableVertexAttribArray(0);
		//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		//glVertexAttribPointer(
		//	0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		//	3,                  // size
		//	GL_FLOAT,           // type
		//	GL_FALSE,           // normalized?
		//	0,                  // stride
		//	(void*)0            // array buffer offset
		//);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDisableVertexAttribArray(0);
		// end test draw ------------

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

        // Check if the ESC key was pressed or the window was closed
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
}

void Application::init() {
    this->initOpenGl();
    this->initApplication();
    this->initWorld();
}

void Application::initOpenGl() {
    // Initialise GLFW
    if (!glfwInit()) {
        throw "Failed to initialize GLFW\n";
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Application::initApplication() {
    // Open a window and create its OpenGL context
    window = glfwCreateWindow(1024, 768, "Ogl", NULL, NULL);
    if (window == NULL) {
        throw "Failed to open GLFW window.\n";
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        throw "Failed to initialize GLEW\n";
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    //glDepthFunc(GL_GREATER);

	// Cull triangles which normal is not towards the camera
    //glDisable(GL_CULL_FACE);
	//glEnable(GL_CULL_FACE);

    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    initText2D("Holstein.DDS");

    glfwSetKeyCallback(this->window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        that->handleKey(key, scancode, action, mods);
        //std::cout << "key pressed: " << key << std::endl;
    });
}

void Application::initWorld() {
    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    this->projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    // Or, for an ortho camera :
    //this->projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.0f); // In world coordinates

	// test draw ----------
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	programID = loadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );

	static const GLfloat g_vertex_buffer_data[] = { 
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
	};

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	// end test draw ------
}

void Application::dispose() {
	// test draw --------------
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &vertexArrayID);
	glDeleteProgram(programID);
	// end test draw ----------

    // Close OpenGL window and terminate GLFW
    glfwTerminate();
}
