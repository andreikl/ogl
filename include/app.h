// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>

class InputBase;

class Application {
public:
    Application();
    virtual ~Application();

	/**
	* runs app cycle
	*/
	void run();

	/**
	* Get window instance and size of the window
	*/
	GLFWwindow* getWindow() const {
		return window;
	};
	int getWidth() const {
		return width;
	};
	int getHeight() const {
		return height;
	};

// gets and sets view camera
public:
	glm::mat4 getView() const {
		return this->view;
	};
	void setView(glm::mat4 view) {
		this->view = view;
	};

protected:
    /**
    * settings of the application window.
    */
    const char* title = "Ogl";
	int width = 768;
    int height = 1024;
    /**
    * world matrices
    */
    glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
	/**
	* input controller
	*/
	InputBase* input = NULL;
	/**
	* window instance
	*/
	GLFWwindow* window;

protected:
    /**
    * draws app
    */
    virtual void draw() = 0;
    /**
    * Sets up the application
    */
    virtual void initOpenGl();
    virtual void initApplication();
    virtual void initWorld();
    virtual void dispose();

protected:
    /**
    * Inits opengl
    */
    void init();
    /**
    * Loads shaders
    */
    GLuint loadShaders(const char* vertex_file_path, const char* fragment_file_path);
};
