#include <vector>

class Application;

// physic point with rotation and mass that contains relative mesh of vertices
class RigidBodyBase {
// constructors and destructors
public:
    RigidBodyBase();
    virtual ~RigidBodyBase();

public:
    void virtual init() = 0;
    void virtual draw(const Application& app) = 0;

// variables
protected:
    std::vector<Vector3> vertices;
    std::vector<unsigned short> indices;
};
