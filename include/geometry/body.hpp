#include <vector>

class Application;

// physic point with rotation and mass that contains relative mesh of vertices
class RigidBody {
// constructors and destructors
public:
    RigidBody();
    virtual ~RigidBody();

public:
    void virtual init() = 0;
    void virtual draw(const Application& app) = 0;

// Rigid body mass
public:
    // Calculates internal data from state data.
    void calculateDerivedData();
    //Integrates the rigid body forward in time by the given amount.
    void integrate(real duration);
    // Sets the mass of the rigid body.
    void setMass(const real mass);
    // Gets the mass of the rigid body.
    real getMass() const;
    // Sets the inverse mass of the rigid body.
    void setInverseMass(const real inverseMass);
    // Gets the inverse mass of the rigid body.
    real getInverseMass() const;
    // Returns true if the mass of the body is not-infinite.
    bool hasFiniteMass() const;

// Rigid body inertia tensor
public:
    // Sets the intertia tensor for the rigid body.
    void setInertiaTensor(const Matrix3 &inertiaTensor);
    // Copies the current inertia tensor of the rigid body into the given matrix.
    void getInertiaTensor(Matrix3 *inertiaTensor) const;
    // Gets a copy of the current inertia tensor of the rigid body.
    Matrix3 getInertiaTensor() const;
    // Copies the current inertia tensor of the rigid body into the given matrix.
    void getInertiaTensorWorld(Matrix3 *inertiaTensor) const;
    // Gets a copy of the current inertia tensor of the rigid body.
    Matrix3 getInertiaTensorWorld() const;
    // Sets the inverse intertia tensor for the rigid body.
    void setInverseInertiaTensor(const Matrix3 &inverseInertiaTensor);
    // Copies the current inverse inertia tensor of the rigid body into the given matrix.
    void getInverseInertiaTensor(Matrix3 *inverseInertiaTensor) const;
    // Gets a copy of the current inverse inertia tensor of the rigid body.
    Matrix3 getInverseInertiaTensor() const;
    // Copies the current inverse inertia tensor of the rigid body into the given matrix.
    void getInverseInertiaTensorWorld(Matrix3 *inverseInertiaTensor) const;
    // Gets a copy of the current inverse inertia tensor of the rigid body.
    Matrix3 getInverseInertiaTensorWorld() const;

// Rigid body dampings
public:
    // Sets both linear and angular damping in one function call.
    void setDamping(const real linearDamping, const real angularDamping);
    // Sets the linear damping for the rigid body.
    void setLinearDamping(const real linearDamping);
    // Gets the current linear damping value.
    real getLinearDamping() const;
    // Sets the angular damping for the rigid body.
    void setAngularDamping(const real angularDamping);
    // Gets the current angular damping value.
    real getAngularDamping() const;

// Rigid body position
public:
    // Sets the position of the rigid body.
    void setPosition(const Vector3 &position);
    // Sets the position of the rigid body by component.
    void setPosition(const real x, const real y, const real z);
    // Fills the given vector with the position of the rigid body.
    void getPosition(Vector3 *position) const;
    // Gets the position of the rigid body.
    Vector3 getPosition() const;
    // Converts the given point from world space into the body's local space.
    Vector3 getPointInLocalSpace(const Vector3 &point) const;
    // Converts the given point from world space into the body's local space.
    Vector3 getPointInWorldSpace(const Vector3 &point) const;

// Rigid body orientation
public:
    // Sets the orientation of the rigid body.
    void setOrientation(const Quaternion &orientation);
    // Sets the orientation of the rigid body by component.
    void setOrientation(const real r, const real i, const real j, const real k);
    // Fills the given quaternion with the current value of the rigid body's orientation.
    void getOrientation(Quaternion *orientation) const;
    // Gets the orientation of the rigid body.
    Quaternion getOrientation() const;
    // Fills the given matrix with a transformation representing the rigid body's orientation.
    void getOrientation(Matrix3 *matrix) const;
    // Fills the given matrix data structure with a transformation representing the rigid body's orientation.
    void getOrientation(real matrix[9]) const;
    // Converts the given direction from world space into the body's local space.
    Vector3 getDirectionInLocalSpace(const Vector3 &direction) const;
    // Converts the given direction from world space into the body's local space.
    Vector3 getDirectionInWorldSpace(const Vector3 &direction) const;

// Rigid body velocity and rotation
public:
    // Sets the velocity of the rigid body.
    void setVelocity(const Vector3 &velocity);
    // Sets the velocity of the rigid body by component. The velocity is given in world space.
    void setVelocity(const real x, const real y, const real z);
    // Fills the given vector with the velocity of the rigid body.
    void getVelocity(Vector3 *velocity) const;
    // Gets the velocity of the rigid body.
    Vector3 getVelocity() const;
    // Applies the given change in velocity.
    void addVelocity(const Vector3 &deltaVelocity);
    // Sets the rotation of the rigid body.
    void setRotation(const Vector3 &rotation);
    // Sets the rotation of the rigid body by component. The rotation is given in world space.
    void setRotation(const real x, const real y, const real z);
    // Fills the given vector with the rotation of the rigid body.
    void getRotation(Vector3 *rotation) const;
    // Gets the rotation of the rigid body.
    Vector3 getRotation() const;
    // Applies the given change in rotation.
    void addRotation(const Vector3 &deltaRotation);

// Rigid body acceleration
public:
    // Fills the given vector with the current accumulated value for linear acceleration.
    void getLastFrameAcceleration(Vector3 *linearAcceleration) const;
    // Gets the current accumulated value for linear acceleration
    Vector3 getLastFrameAcceleration() const;
    // Clears the forces and torques in the accumulators.
    void clearAccumulators();
    // Adds the given force to centre of mass of the rigid body.
    void addForce(const Vector3 &force);
    // Adds the given force to the given point on the rigid body.
    void addForceAtPoint(const Vector3 &force, const Vector3 &point);
    // Adds the given force to the given point on the rigid body.
    void addForceAtBodyPoint(const Vector3 &force, const Vector3 &point);
    // Adds the given torque to the rigid body.
    void addTorque(const Vector3 &torque);
    // Sets the constant acceleration of the rigid body.
    void setAcceleration(const Vector3 &acceleration);
    // Sets the constant acceleration of the rigid body by component.
    void setAcceleration(const real x, const real y, const real z);
    // Fills the given vector with the acceleration of the rigid body.
    void getAcceleration(Vector3 *acceleration) const;
    // Gets the acceleration of the rigid body.
    Vector3 getAcceleration() const;

// Rigid body transform
public:
    // Fills the given matrix with a transformation representing the rigid body's position and orientation.
    void getTransform(Matrix4 *transform) const;
    // Fills the given matrix data structure with a transformation representing the rigid body's position and orientation.
    void getTransform(real matrix[16]) const;
    // Fills the given matrix data structure with atransformation representing the rigid body's position andorientation.
    void getGLTransform(float matrix[16]) const;
    // Gets a transformation representing the rigid body's position and orientation.
    Matrix4 getTransform() const;

// Rigid body integration
public:
    // Returns true if the body is awake and responding to integration.
    double getAwakeTime() const;
    // Sets the awake state of the body
    void setAwakeTime(const double awakeTime);
    // Returns true if the body is allowed to go to sleep at any time.
    //bool getCanSleep() const;
    // Sets whether the body is ever allowed to go to sleep.
    //void setCanSleep(const bool canSleep = true);

// Variety of Vertices
protected:
    std::vector<Vector3> vertices;
    std::vector<unsigned short> indices;

// Rigid body variables
protected:
    // Holds the inverse of the mass of the rigid body.
    real inverseMass;
    //Holds the inverse of the body's inertia tensor.
    Matrix3 inverseInertiaTensor;
    // Holds the amount of damping applied to linear motion.
    real linearDamping;
    // Holds the amount of damping applied to angular motion.
    real angularDamping;
    // Holds the linear position of the rigid body in world space.
    Vector3 position;
    // Holds the angular orientation of the rigid body in world space.
    Quaternion orientation;
    // Holds the linear velocity of the rigid body in world space.
    Vector3 velocity;
    // Holds the angular velocity, or rotation, or the rigid body in world space.
    Vector3 rotation;

// Force and Torque Accumulators
protected:
    // Holds the accumulated force to be applied at the next integration step.
    Vector3 forceAccum;
    // Holds the accumulated torque to be applied at the next integration step.
    Vector3 torqueAccum;
    // Holds the acceleration of the rigid body.
    Vector3 acceleration;
    // Holds the linear acceleration of the rigid body, for the previous frame.
    Vector3 lastFrameAcceleration;

// Derived Data
protected:
    // Holds the inverse inertia tensor of the body in world space.
    Matrix3 inverseInertiaTensorWorld;
    // Holds the amount of motion of the body.
    real motion;
    // A body can be put to sleep to avoid it being updated
    double awakeTime;

    // Some bodies may never be allowed to fall asleep.
    // bool canSleep;
    // Holds a transform matrix for converting body space into world space and vice versa.
    Matrix4 transformMatrix;
};
