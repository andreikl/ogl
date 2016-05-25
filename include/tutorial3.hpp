#include <vector>

class Application;
class RigidBody;

// ballistic demo
class Tutorial3 : Application {
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
    std::vector<RigidBody*> rays;
    RigidBody* dice;
    RigidBody* grid;
};
