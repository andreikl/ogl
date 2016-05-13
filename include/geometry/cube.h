#include <vector>

class Application;
class RigidBodyBase;

class Cube: RigidBodyBase {
// constructors and destructors
public:
    Cube();
    ~Cube();
    static RigidBodyBase* Create();

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
