class Application;
class RigidBody;

class Sphere: RigidBody {
// constructors and destructors
public:
    Sphere();
    ~Sphere();
    static RigidBody* Create(int columns = 10, int rows = 5);

public:
    void virtual init();
    void virtual draw(const Application& app);

private:
    GLuint programID;
    GLuint matrixID;
    GLuint colorID;

    GLuint vertexbuffer;
    GLuint elementbuffer;
};
