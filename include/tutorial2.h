class Application;
class RigidBody;

// ballistic demo
class Tutorial2 : Application {
public:
    static Application* Create();

protected:
    virtual void handleKey(int key, int scancode, int action, int mods);
    virtual void draw();

protected:
    virtual void initWorld();
    virtual void dispose();

private:
    RigidBody* dice;
    RigidBody* grid;
};
