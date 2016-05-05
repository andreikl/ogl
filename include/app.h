
class Application {
public:
    Application();
    virtual ~Application();
    /**
    * runs app cycle
    */
    int run();

protected:
    /**
    * settings of the application window.
    */
    const char* title;
    int height;
    int width;

protected:
    /**
    * draws app
    */
    virtual int draw() = 0;
    /**
    * Sets up the application
    */
    virtual int initOpenGl();
    virtual int initApplication();
    virtual int disposeApplication();
};
