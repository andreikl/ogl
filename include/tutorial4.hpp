#include <vector>

class Application;
class RigidBody;

// Bounding volumes hierarchy
class Tutorial4 : Application {
public:
    static Application* Create();

protected:
    virtual void handleKey(int key, int scancode, int action, int mods);
    virtual void handleButton(int button, int action, int mods);
    virtual void draw();

protected:
    virtual void initWorld();
    virtual void dispose();

private:
    std::vector<RigidBody*> cubes;
    RigidBody* world;
    RigidBody* grid;
};
