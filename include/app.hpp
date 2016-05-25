class InputBase;

class Application {
public:
    Application();
    virtual ~Application();

public:
	// Get window instance and size of the window
	GLFWwindow* getWindow() const;
	int getWidth() const;
	int getHeight() const;
    // gets and sets view camera
	glm::mat4 getView() const;
	void setView(glm::mat4 view);
    // gets projection matrix
    glm::mat4 getProjection() const;
    // get time between frames and app strat time
    double getStartTime() const;
    double getLastFrameDelta() const;

public:
    // runs app cycle
    void run();

protected:
    // window instance
    GLFWwindow* window;
    // settings of the application window.
    const char* title = "Ogl";
	int width = 768;
    int height = 1024;
    // world matrices
    glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
	// input controller
	InputBase* input = NULL;
    // time between frames and app strat time
    double lastFrameDelta;
    double startTime;


protected:
    // draws app
    virtual void draw() = 0;
    // handles keyboard and mouse
    virtual void handleButton(int button, int action, int mods) = 0;
    virtual void handleKey(int key, int scancode, int action, int mods) = 0;
    // Sets up the application
    virtual void initOpenGl();
    virtual void initApplication();
    virtual void initWorld();
    virtual void dispose();

protected:
    // Inits opengl
    void init();
};
