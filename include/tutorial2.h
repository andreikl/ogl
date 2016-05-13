class Application;
class RigidBody;

// ballistic demo
class Tutorial2 : Application {
public:
    static Application* Create();

protected:
    virtual void draw();
    virtual void initWorld();
    virtual void dispose();

private:
    RigidBody* dice;
    RigidBody* grid;
};
