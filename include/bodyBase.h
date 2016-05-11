class Application;

// contains an array of rigid sructure and a conversion matrix
class BodyBase {
// constructors and destructors
public:
    BodyBase(Application& app);

// methods
public:
    virtual void init() = 0;

 // variables
protected:
    Application& app;
};
