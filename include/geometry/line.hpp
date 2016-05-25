class Application;
class RigidBody;

class Line: RigidBody {
// constructors and destructors
public:
    Line();
    ~Line();
    static RigidBody* Create();

public:
    void virtual init();
    void virtual draw(const Application& app);

private:
    GLuint programID;
    GLuint matrixID;
    GLuint colorID;

    GLuint vertexbuffer;
};
