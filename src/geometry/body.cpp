// c/c++
#include "math.h"

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>

#include "core.h"
#include "geometry/body.h"

RigidBody::RigidBody() {
}

RigidBody::~RigidBody() {
}

void RigidBody::setMass(const real mass) {
    assert(mass != 0);
    inverseMass = ((real)1.0) / mass;
}

real RigidBody::getMass() const {
    if (inverseMass == 0) {
        return REAL_MAX;
    } else {
        return ((real)1.0) / inverseMass;
    }
}

void RigidBody::setInverseMass(const real inverseMass) {
    RigidBody::inverseMass = inverseMass;
}

real RigidBody::getInverseMass() const {
    return inverseMass;
}

bool RigidBody::hasFiniteMass() const {
    return inverseMass >= 0.0f;
}

void RigidBody::setInertiaTensor(const Matrix3 &inertiaTensor) {
    inverseInertiaTensor.setInverse(inertiaTensor);
}

void RigidBody::getInertiaTensor(Matrix3 *inertiaTensor) const {
    inertiaTensor->setInverse(inverseInertiaTensor);
}

Matrix3 RigidBody::getInertiaTensor() const {
    Matrix3 it;
    getInertiaTensor(&it);
    return it;
}

void RigidBody::getInertiaTensorWorld(Matrix3 *inertiaTensor) const {
    inertiaTensor->setInverse(inverseInertiaTensorWorld);
}

Matrix3 RigidBody::getInertiaTensorWorld() const {
    Matrix3 it;
    getInertiaTensorWorld(&it);
    return it;
}

void RigidBody::setInverseInertiaTensor(const Matrix3 &inverseInertiaTensor) {
    RigidBody::inverseInertiaTensor = inverseInertiaTensor;
}

void RigidBody::getInverseInertiaTensor(Matrix3 *inverseInertiaTensor) const {
    *inverseInertiaTensor = RigidBody::inverseInertiaTensor;
}

Matrix3 RigidBody::getInverseInertiaTensor() const {
    return inverseInertiaTensor;
}

void RigidBody::getInverseInertiaTensorWorld(Matrix3 *inverseInertiaTensor) const {
    *inverseInertiaTensor = inverseInertiaTensorWorld;
}

Matrix3 RigidBody::getInverseInertiaTensorWorld() const {
    return inverseInertiaTensorWorld;
}

void RigidBody::setDamping(const real linearDamping, const real angularDamping) {
    RigidBody::linearDamping = linearDamping;
    RigidBody::angularDamping = angularDamping;
}

void RigidBody::setLinearDamping(const real linearDamping) {
    RigidBody::linearDamping = linearDamping;
}

real RigidBody::getLinearDamping() const {
    return linearDamping;
}

void RigidBody::setAngularDamping(const real angularDamping) {
    RigidBody::angularDamping = angularDamping;
}

real RigidBody::getAngularDamping() const {
    return angularDamping;
}

void RigidBody::setPosition(const Vector3 &position) {
    RigidBody::position = position;
}

void RigidBody::setPosition(const real x, const real y, const real z) {
    position.x = x;
    position.y = y;
    position.z = z;
}

void RigidBody::getPosition(Vector3 *position) const {
    *position = RigidBody::position;
}

Vector3 RigidBody::getPosition() const {
    return position;
}

Vector3 RigidBody::getPointInLocalSpace(const Vector3 &point) const {
    return transformMatrix.transformInverse(point);
}

Vector3 RigidBody::getPointInWorldSpace(const Vector3 &point) const {
    return transformMatrix.transform(point);
}

void RigidBody::setOrientation(const Quaternion &orientation) {
    RigidBody::orientation = orientation;
    RigidBody::orientation.normalise();
}

void RigidBody::setOrientation(const real r, const real i, const real j, const real k) {
    orientation.r = r;
    orientation.i = i;
    orientation.j = j;
    orientation.k = k;
    orientation.normalise();
}

void RigidBody::getOrientation(Quaternion *orientation) const {
    *orientation = RigidBody::orientation;
}

Quaternion RigidBody::getOrientation() const {
    return orientation;
}

void RigidBody::getOrientation(Matrix3 *matrix) const {
    getOrientation(matrix->data);
}

void RigidBody::getOrientation(real matrix[9]) const {
    matrix[0] = transformMatrix.data[0];
    matrix[1] = transformMatrix.data[1];
    matrix[2] = transformMatrix.data[2];

    matrix[3] = transformMatrix.data[4];
    matrix[4] = transformMatrix.data[5];
    matrix[5] = transformMatrix.data[6];

    matrix[6] = transformMatrix.data[8];
    matrix[7] = transformMatrix.data[9];
    matrix[8] = transformMatrix.data[10];
}

Vector3 RigidBody::getDirectionInLocalSpace(const Vector3 &direction) const {
    return transformMatrix.transformInverseDirection(direction);
}

Vector3 RigidBody::getDirectionInWorldSpace(const Vector3 &direction) const {
    return transformMatrix.transformDirection(direction);
}

void RigidBody::setVelocity(const Vector3 &velocity) {
    RigidBody::velocity = velocity;
}

void RigidBody::setVelocity(const real x, const real y, const real z) {
    velocity.x = x;
    velocity.y = y;
    velocity.z = z;
}

void RigidBody::getVelocity(Vector3 *velocity) const {
    *velocity = RigidBody::velocity;
}

Vector3 RigidBody::getVelocity() const {
    return velocity;
}

void RigidBody::addVelocity(const Vector3 &deltaVelocity) {
    velocity += deltaVelocity;
}

void RigidBody::setRotation(const Vector3 &rotation) {
    RigidBody::rotation = rotation;
}

void RigidBody::setRotation(const real x, const real y, const real z) {
    rotation.x = x;
    rotation.y = y;
    rotation.z = z;
}

void RigidBody::getRotation(Vector3 *rotation) const {
    *rotation = RigidBody::rotation;
}

Vector3 RigidBody::getRotation() const {
    return rotation;
}

void RigidBody::addRotation(const Vector3 &deltaRotation) {
    rotation += deltaRotation;
}

void RigidBody::getLastFrameAcceleration(Vector3 *acceleration) const
{
    *acceleration = lastFrameAcceleration;
}

Vector3 RigidBody::getLastFrameAcceleration() const
{
    return lastFrameAcceleration;
}

void RigidBody::clearAccumulators() {
    forceAccum.clear();
    torqueAccum.clear();
}

void RigidBody::addForce(const Vector3 &force) {
    forceAccum += force;
    isAwake = true;
}

void RigidBody::addForceAtBodyPoint(const Vector3 &force, const Vector3 &point) {
    // Convert to coordinates relative to center of mass.
    Vector3 pt = getPointInWorldSpace(point);
    addForceAtPoint(force, pt);

}

void RigidBody::addForceAtPoint(const Vector3 &force, const Vector3 &point) {
    // Convert to coordinates relative to center of mass.
    Vector3 pt = point;
    pt -= position;

    forceAccum += force;
    torqueAccum += pt % force;

    isAwake = true;
}

void RigidBody::addTorque(const Vector3 &torque) {
    torqueAccum += torque;
    isAwake = true;
}

void RigidBody::setAcceleration(const Vector3 &acceleration) {
    RigidBody::acceleration = acceleration;
}

void RigidBody::setAcceleration(const real x, const real y, const real z) {
    acceleration.x = x;
    acceleration.y = y;
    acceleration.z = z;
}

void RigidBody::getAcceleration(Vector3 *acceleration) const {
    *acceleration = RigidBody::acceleration;
}

Vector3 RigidBody::getAcceleration() const {
    return acceleration;
}

void RigidBody::getTransform(Matrix4 *transform) const {
    memcpy(transform, &transformMatrix.data, sizeof(Matrix4));
}

void RigidBody::getTransform(real matrix[16]) const {
    memcpy(matrix, transformMatrix.data, sizeof(real) * 12);
    matrix[12] = matrix[13] = matrix[14] = 0;
    matrix[15] = 1;
}

void RigidBody::getGLTransform(float matrix[16]) const {
    matrix[0] = (float)transformMatrix.data[0];
    matrix[1] = (float)transformMatrix.data[4];
    matrix[2] = (float)transformMatrix.data[8];
    matrix[3] = 0;

    matrix[4] = (float)transformMatrix.data[1];
    matrix[5] = (float)transformMatrix.data[5];
    matrix[6] = (float)transformMatrix.data[9];
    matrix[7] = 0;

    matrix[8] = (float)transformMatrix.data[2];
    matrix[9] = (float)transformMatrix.data[6];
    matrix[10] = (float)transformMatrix.data[10];
    matrix[11] = 0;

    matrix[12] = (float)transformMatrix.data[3];
    matrix[13] = (float)transformMatrix.data[7];
    matrix[14] = (float)transformMatrix.data[11];
    matrix[15] = 1;
}

Matrix4 RigidBody::getTransform() const {
    return transformMatrix;
}

bool RigidBody::getAwake() const {
    return isAwake;
}

void RigidBody::setAwake(const bool awake) {
    if (awake) {
        isAwake = true;

        // Add a bit of motion to avoid it falling asleep immediately.
        motion = sleepEpsilon*2.0f;
    }
    else {
        isAwake = false;
        velocity.clear();
        rotation.clear();
    }
}

bool RigidBody::getCanSleep() const {
    return canSleep;
}

void RigidBody::setCanSleep(const bool canSleep) {
    RigidBody::canSleep = canSleep;

    if (!canSleep && !isAwake) setAwake();
}
