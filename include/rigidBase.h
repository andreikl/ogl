class BodyBase;

// contains an array of physic points and/or array of child rigid structure
class RigidBase {
// constructors and destructors
public:
    RigidBase(BodyBase& body);

// methods
public:
    virtual void init() = 0;

// variables
protected:
    BodyBase& body;
};
