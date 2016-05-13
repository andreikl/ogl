#include <vector>

class Application;
class RigidBodyBase;

class Sphere: RigidBodyBase {
// constructors and destructors
public:
    Sphere();
    ~Sphere();
    static RigidBodyBase* Create(int columns = 10, int rows = 5);

public:
    void virtual init();
    void virtual draw(const Application& app);

private:
    GLuint programID;
    GLuint matrixID;

    GLuint vertexbuffer;
    GLuint elementbuffer;
};
