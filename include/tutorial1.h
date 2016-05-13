class Application;
class RigidBody;

// shows sphere and provides orbit mouse input
class Tutorial1 : Application {
public:
    static Application* Create();

protected:
    virtual void draw();
    virtual void initWorld();
    virtual void dispose();

private:
    RigidBody* body;
};
