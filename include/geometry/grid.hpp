#include <vector>

class RigidBody;
class Application;

class Grid: RigidBody {
// constructors and destructors
public:
    Grid();
    ~Grid();
    static RigidBody* Create(int columns = 100, int rows = 100);

public:
    void virtual init();
    void virtual draw(const Application& app);

private:
    GLuint programID;
    GLuint matrixID;
    GLuint colorID;

    GLuint vertexbuffer;
};
