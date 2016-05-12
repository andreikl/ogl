#include <vector>

#include "core.h"

class Application;

// physic point with rotation and mass that contains relative mesh of vertices
class ParticleBase {
// constructors and destructors
public:
    ParticleBase();
    virtual ~ParticleBase();

public:
    void virtual init() = 0;
    void virtual draw(const Application& app) = 0;

// variables
protected:
    std::vector<Vector3> vertices;
    std::vector<unsigned short> indices;
};

class ParticleSphere : ParticleBase {
// constructors and destructors
public:
    ParticleSphere();
    ~ParticleSphere();
    static ParticleBase* Create(int columns = 10, int rows = 5);

public:
    void virtual init();
    void virtual draw(const Application& app);

private:
    GLuint programID;
    GLuint matrixID;

    GLuint vertexbuffer;
    GLuint elementbuffer;
};
