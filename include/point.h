#include <vector>

#include "core.h"

// physic point with rotation and mass that contains relative mesh of vertices
class PointBase {
// constructors and destructors
public:
    PointBase();
    virtual ~PointBase();

public:
    void virtual init() = 0;
    void virtual draw() = 0;

// variables
protected:
    std::vector<Vector3> vertices;
    std::vector<int> triangles;
};

class PointSphere: PointBase {
// constructors and destructors
public:
    PointSphere();
    static PointBase& Create(int columns, int rows);

public:
    void virtual init();
    void virtual draw();

private:
    GLuint programID;
    GLuint matrixID;

    GLuint vertexbuffer;
    GLuint vertexArrayID;
};
