class Application;
class RigidBodyBase;

// shows sphere and provides orbit mouse input
class Tutorial1 : Application {
public:
    static Application* Create();

protected:
    virtual void draw();
    virtual void initWorld();
    virtual void dispose();

private:
    RigidBodyBase* body;
};
