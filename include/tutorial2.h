class Application;
class RigidBodyBase;

// ballistic demo
class Tutorial2 : Application {
public:
    static Application* Create();

protected:
    virtual void draw();
    virtual void initWorld();
    virtual void dispose();

private:
    RigidBodyBase* sphere;
    RigidBodyBase* grid;
};
