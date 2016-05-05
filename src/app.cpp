// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// c++
#include <vector>
#include <string>
#include <fstream>

// Include GLM
#include <glm/gtc/matrix_transform.hpp>

// user includes
#include "inputBase.h"
#include "app.h"

Application::Application() {
}

Application::~Application() {
    this->dispose();
}

void Application::run() {
    do {
        // Clear the screen.
        glClear(GL_COLOR_BUFFER_BIT);

		if (this->input) {
			this->input->handle(*this);
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

    //glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
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

	// Cull triangles which normal is not towards the camera
	//glEnable(GL_CULL_FACE);
}

void Application::initWorld() {
    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    this->projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    // Or, for an ortho camera :
    //this->projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.0f); // In world coordinates

    // Camera matrix
    this->view = glm::lookAt(
        glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
        glm::vec3(0, 0, 0), // and looks at the origin
        glm::vec3(0, 1, 0));  // Head is up (set to 0,-1,0 to look upside-down)

}

void Application::dispose() {
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
}

GLuint Application::loadShaders(const char* vertex_file_path, const char* fragment_file_path) {
    // Read the Vertex Shader code from the file
    std::string vertexShaderCode;
    std::ifstream vertexShaderStream(vertex_file_path, std::ios::in);
    if (vertexShaderStream.is_open()) {
        std::string line;
        while (getline(vertexShaderStream, line)) {
            vertexShaderCode += "\n" + line;
        }
        vertexShaderStream.close();
    } else {
        throw (std::string("Impossible to open ") + vertex_file_path + ".").c_str();
    }

    // Read the Fragment Shader code from the file
    std::string fragmentShaderCode;
    std::ifstream fragmentShaderStream(fragment_file_path, std::ios::in);
    if (fragmentShaderStream.is_open()) {
        std::string line;
        while (getline(fragmentShaderStream, line)) {
            fragmentShaderCode += "\n" + line;
        }
        fragmentShaderStream.close();
    }
    else {
        throw (std::string("Impossible to open ") + fragment_file_path + ".").c_str();
    }

    GLint result = GL_FALSE;
    int infoLogLength;

    // Compile Vertex Shader
    char const * vertexSourcePointer = vertexShaderCode.c_str();
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderID, 1, &vertexSourcePointer, NULL);
    glCompileShader(vertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (result == GL_FALSE) {
        std::vector<char> vertexShaderErrorMessage(infoLogLength + 1);
        glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
        throw (std::string("Vertex shader error: ") + &vertexShaderErrorMessage[0]).c_str();
    }

    // Compile Fragment Shader
    char const * fragmentSourcePointer = fragmentShaderCode.c_str();
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderID, 1, &fragmentSourcePointer, NULL);
    glCompileShader(fragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (result == GL_FALSE) {
        std::vector<char> fragmentShaderErrorMessage(infoLogLength + 1);
        glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, &fragmentShaderErrorMessage[0]);
        throw (std::string("Fragment shader error: ") + &fragmentShaderErrorMessage[0]).c_str();
    }

    // Link the program
    GLuint programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);

    // Check the program
    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (result == GL_FALSE) {
        std::vector<char> programErrorMessage(infoLogLength + 1);
        throw (std::string("Shader program error: ") + &programErrorMessage[0]).c_str();
    }

    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    return programID;
}
