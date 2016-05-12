// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// user includes
#include "input.h"
#include "app.h"

Application::Application() {
}

Application::~Application() {
    this->dispose();
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

void Application::run() {
    do {
        // Clear the screen.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (this->input) {
			this->input->handle();
		}
        this->draw();

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

	//glfwPollEvents();

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    //glDepthFunc(GL_GREATER);

	// Cull triangles which normal is not towards the camera
	//glEnable(GL_CULL_FACE);
}

void Application::initWorld() {
    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    this->projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    // Or, for an ortho camera :
    //this->projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.0f); // In world coordinates
}

void Application::dispose() {
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
}
