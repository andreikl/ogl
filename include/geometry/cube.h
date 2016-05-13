#include <vector>

class Application;
class RigidBody;

class Cube: RigidBody {
// constructors and destructors
public:
    Cube();
    ~Cube();
    static RigidBody* Create();

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
