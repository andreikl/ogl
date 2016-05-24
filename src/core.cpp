// c++
#include <vector>
#include <string>
#include <fstream>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>

#include "core.hpp"

real sleepEpsilon = ((real)0.3);

Vector3::Vector3(): x(0.0), y(0.0), z(0.0) {
}

Vector3::Vector3(const real x, const real y, const real z): x(x), y(y), z(z) {
}

real Vector3::operator[] (unsigned i) const {
    if (i == 0) return x;
    if (i == 1) return y;
    return z;
}

real& Vector3::operator[] (unsigned i) {
    if (i == 0) return x;
    if (i == 1) return y;
    return z;
}

Vector3 Vector3::operator+(const Vector3& v) const {
    return Vector3(x + v.x, y + v.y, z + v.z);
}

void Vector3::operator+= (const Vector3& v) {
    x += v.x;
    y += v.y;
    z += v.z;
}

Vector3 Vector3::operator- (const Vector3& v) const {
    return Vector3(x - v.x, y - v.y, z - v.z);
}

void Vector3::operator-= (const Vector3& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
}

Vector3 Vector3::operator* (const real value) const {
    return Vector3(x*value, y*value, z*value);
}

void Vector3::operator*= (const real value) {
    x *= value;
    y *= value;
    z *= value;
}

Vector3 Vector3::componentProduct(const Vector3 &vector) const {
    return Vector3(x * vector.x, y * vector.y, z * vector.z);
}

void Vector3::componentProductUpdate(const Vector3 &vector) {
    x *= vector.x;
    y *= vector.y;
    z *= vector.z;
}

Vector3 Vector3::vectorProduct(const Vector3 &vector) const {
    return Vector3(y*vector.z - z*vector.y,
        z*vector.x - x*vector.z,
        x*vector.y - y*vector.x);
}

Vector3 Vector3::operator% (const Vector3 &vector) const {
    return Vector3(y*vector.z - z*vector.y,
        z*vector.x - x*vector.z,
        x*vector.y - y*vector.x);
}

void Vector3::operator%= (const Vector3 &vector) {
    *this = vectorProduct(vector);
}

real Vector3::scalarProduct(const Vector3 &vector) const {
    return x*vector.x + y*vector.y + z*vector.z;
}

real Vector3::operator* (const Vector3 &vector) const {
    return x*vector.x + y*vector.y + z*vector.z;
}

void Vector3::addScaledVector(const Vector3& vector, real scale) {
    x += vector.x * scale;
    y += vector.y * scale;
    z += vector.z * scale;
}

real Vector3::magnitude() const {
    return real_sqrt(x*x + y*y + z*z);
}

real Vector3::squareMagnitude() const {
    return x*x + y*y + z*z;
}

void Vector3::trim(real size) {
    if (squareMagnitude() > size*size)
    {
        normalise();
        x *= size;
        y *= size;
        z *= size;
    }
}

void Vector3::normalise() {
    real l = magnitude();
    if (l > 0)
    {
        (*this) *= ((real)1) / l;
    }
}

Vector3 Vector3::unit() const {
    Vector3 result = *this;
    result.normalise();
    return result;
}

bool Vector3::operator== (const Vector3& other) const {
    return x == other.x &&
        y == other.y &&
        z == other.z;
}

bool Vector3::operator!= (const Vector3& other) const {
    return !(*this == other);
}

bool Vector3::operator< (const Vector3& other) const {
    return x < other.x && y < other.y && z < other.z;
}

bool Vector3::operator> (const Vector3& other) const {
    return x > other.x && y > other.y && z > other.z;
}

bool Vector3::operator<= (const Vector3& other) const {
    return x <= other.x && y <= other.y && z <= other.z;
}

bool Vector3::operator>= (const Vector3& other) const {
    return x >= other.x && y >= other.y && z >= other.z;
}

void Vector3::clear() {
    x = y = z = 0;
}

void Vector3::invert() {
    x = -x;
    y = -y;
    z = -z;
}

Quaternion::Quaternion(): r(1), i(0), j(0), k(0) {
}

Quaternion::Quaternion(const real r, const real i, const real j, const real k): r(r), i(i), j(j), k(k) {
}

void Quaternion::normalise() {
    real d = r*r + i*i + j*j + k*k;

    // Check for zero length quaternion, and use the no-rotation
    // quaternion in that case.
    if (d < real_epsilon) {
        r = 1;
        return;
    }

    d = ((real)1.0) / real_sqrt(d);
    r *= d;
    i *= d;
    j *= d;
    k *= d;
}

void Quaternion::operator *= (const Quaternion &multiplier) {
    Quaternion q = *this;
    r = q.r*multiplier.r - q.i*multiplier.i -
        q.j*multiplier.j - q.k*multiplier.k;
    i = q.r*multiplier.i + q.i*multiplier.r +
        q.j*multiplier.k - q.k*multiplier.j;
    j = q.r*multiplier.j + q.j*multiplier.r +
        q.k*multiplier.i - q.i*multiplier.k;
    k = q.r*multiplier.k + q.k*multiplier.r +
        q.i*multiplier.j - q.j*multiplier.i;
}

void Quaternion::addScaledVector(const Vector3& vector, real scale) {
    Quaternion q(0,
        vector.x * scale,
        vector.y * scale,
        vector.z * scale);
    q *= *this;
    r += q.r * ((real)0.5);
    i += q.i * ((real)0.5);
    j += q.j * ((real)0.5);
    k += q.k * ((real)0.5);
}

void Quaternion::rotateByVector(const Vector3& vector) {
    Quaternion q(0, vector.x, vector.y, vector.z);
    (*this) *= q;
}

Matrix4::Matrix4() {
    data[1] = data[2] = data[3] = data[4] = data[6] =
        data[7] = data[8] = data[9] = data[11] = 0;
    data[0] = data[5] = data[10] = 1;
}

void Matrix4::setDiagonal(real a, real b, real c) {
    data[0] = a;
    data[5] = b;
    data[10] = c;
}

Matrix4 Matrix4::operator*(const Matrix4 &o) const {
    Matrix4 result;
    result.data[0] = (o.data[0] * data[0]) + (o.data[4] * data[1]) + (o.data[8] * data[2]);
    result.data[4] = (o.data[0] * data[4]) + (o.data[4] * data[5]) + (o.data[8] * data[6]);
    result.data[8] = (o.data[0] * data[8]) + (o.data[4] * data[9]) + (o.data[8] * data[10]);

    result.data[1] = (o.data[1] * data[0]) + (o.data[5] * data[1]) + (o.data[9] * data[2]);
    result.data[5] = (o.data[1] * data[4]) + (o.data[5] * data[5]) + (o.data[9] * data[6]);
    result.data[9] = (o.data[1] * data[8]) + (o.data[5] * data[9]) + (o.data[9] * data[10]);

    result.data[2] = (o.data[2] * data[0]) + (o.data[6] * data[1]) + (o.data[10] * data[2]);
    result.data[6] = (o.data[2] * data[4]) + (o.data[6] * data[5]) + (o.data[10] * data[6]);
    result.data[10] = (o.data[2] * data[8]) + (o.data[6] * data[9]) + (o.data[10] * data[10]);

    result.data[3] = (o.data[3] * data[0]) + (o.data[7] * data[1]) + (o.data[11] * data[2]) + data[3];
    result.data[7] = (o.data[3] * data[4]) + (o.data[7] * data[5]) + (o.data[11] * data[6]) + data[7];
    result.data[11] = (o.data[3] * data[8]) + (o.data[7] * data[9]) + (o.data[11] * data[10]) + data[11];

    return result;
}

Vector3 Matrix4::operator*(const Vector3 &vector) const {
    return Vector3(
        vector.x * data[0] +
        vector.y * data[1] +
        vector.z * data[2] + data[3],

        vector.x * data[4] +
        vector.y * data[5] +
        vector.z * data[6] + data[7],

        vector.x * data[8] +
        vector.y * data[9] +
        vector.z * data[10] + data[11]
        );
}

Vector3 Matrix4::transform(const Vector3 &vector) const {
    return (*this) * vector;
}

real Matrix4::getDeterminant() const {
    return -data[8] * data[5] * data[2] +
        data[4] * data[9] * data[2] +
        data[8] * data[1] * data[6] -
        data[0] * data[9] * data[6] -
        data[4] * data[1] * data[10] +
        data[0] * data[5] * data[10];
}

void Matrix4::setInverse(const Matrix4 &m) {
    // Make sure the determinant is non-zero.
    real det = getDeterminant();
    if (det == 0) return;
    det = ((real)1.0) / det;

    data[0] = (-m.data[9] * m.data[6] + m.data[5] * m.data[10])*det;
    data[4] = (m.data[8] * m.data[6] - m.data[4] * m.data[10])*det;
    data[8] = (-m.data[8] * m.data[5] + m.data[4] * m.data[9])*det;

    data[1] = (m.data[9] * m.data[2] - m.data[1] * m.data[10])*det;
    data[5] = (-m.data[8] * m.data[2] + m.data[0] * m.data[10])*det;
    data[9] = (m.data[8] * m.data[1] - m.data[0] * m.data[9])*det;

    data[2] = (-m.data[5] * m.data[2] + m.data[1] * m.data[6])*det;
    data[6] = (+m.data[4] * m.data[2] - m.data[0] * m.data[6])*det;
    data[10] = (-m.data[4] * m.data[1] + m.data[0] * m.data[5])*det;

    data[3] = (m.data[9] * m.data[6] * m.data[3]
        - m.data[5] * m.data[10] * m.data[3]
        - m.data[9] * m.data[2] * m.data[7]
        + m.data[1] * m.data[10] * m.data[7]
        + m.data[5] * m.data[2] * m.data[11]
        - m.data[1] * m.data[6] * m.data[11])*det;
    data[7] = (-m.data[8] * m.data[6] * m.data[3]
        + m.data[4] * m.data[10] * m.data[3]
        + m.data[8] * m.data[2] * m.data[7]
        - m.data[0] * m.data[10] * m.data[7]
        - m.data[4] * m.data[2] * m.data[11]
        + m.data[0] * m.data[6] * m.data[11])*det;
    data[11] = (m.data[8] * m.data[5] * m.data[3]
        - m.data[4] * m.data[9] * m.data[3]
        - m.data[8] * m.data[1] * m.data[7]
        + m.data[0] * m.data[9] * m.data[7]
        + m.data[4] * m.data[1] * m.data[11]
        - m.data[0] * m.data[5] * m.data[11])*det;
}


Matrix4 Matrix4::inverse() const {
    Matrix4 result;
    result.setInverse(*this);
    return result;
}

void Matrix4::invert() {
    setInverse(*this);
}

Vector3 Matrix4::transformDirection(const Vector3 &vector) const {
    return Vector3(
        vector.x * data[0] +
        vector.y * data[1] +
        vector.z * data[2],

        vector.x * data[4] +
        vector.y * data[5] +
        vector.z * data[6],

        vector.x * data[8] +
        vector.y * data[9] +
        vector.z * data[10]
        );
}

Vector3 Matrix4::transformInverseDirection(const Vector3 &vector) const {
    return Vector3(
        vector.x * data[0] +
        vector.y * data[4] +
        vector.z * data[8],

        vector.x * data[1] +
        vector.y * data[5] +
        vector.z * data[9],

        vector.x * data[2] +
        vector.y * data[6] +
        vector.z * data[10]
    );
}

Vector3 Matrix4::transformInverse(const Vector3 &vector) const {
    Vector3 tmp = vector;
    tmp.x -= data[3];
    tmp.y -= data[7];
    tmp.z -= data[11];
    return Vector3(
        tmp.x * data[0] +
        tmp.y * data[4] +
        tmp.z * data[8],

        tmp.x * data[1] +
        tmp.y * data[5] +
        tmp.z * data[9],

        tmp.x * data[2] +
        tmp.y * data[6] +
        tmp.z * data[10]
        );
}

Vector3 Matrix4::getAxisVector(int i) const {
    return Vector3(data[i], data[i + 4], data[i + 8]);
}

void Matrix4::setOrientationAndPos(const Quaternion &q, const Vector3 &pos) {
    data[0] = 1 - (2 * q.j*q.j + 2 * q.k*q.k);
    data[1] = 2 * q.i*q.j + 2 * q.k*q.r;
    data[2] = 2 * q.i*q.k - 2 * q.j*q.r;
    data[3] = pos.x;

    data[4] = 2 * q.i*q.j - 2 * q.k*q.r;
    data[5] = 1 - (2 * q.i*q.i + 2 * q.k*q.k);
    data[6] = 2 * q.j*q.k + 2 * q.i*q.r;
    data[7] = pos.y;

    data[8] = 2 * q.i*q.k + 2 * q.j*q.r;
    data[9] = 2 * q.j*q.k - 2 * q.i*q.r;
    data[10] = 1 - (2 * q.i*q.i + 2 * q.j*q.j);
    data[11] = pos.z;
}

void Matrix4::fillGLArray(float array[16]) const {
    array[0] = (float)data[0];
    array[1] = (float)data[4];
    array[2] = (float)data[8];
    array[3] = (float)0;

    array[4] = (float)data[1];
    array[5] = (float)data[5];
    array[6] = (float)data[9];
    array[7] = (float)0;

    array[8] = (float)data[2];
    array[9] = (float)data[6];
    array[10] = (float)data[10];
    array[11] = (float)0;

    array[12] = (float)data[3];
    array[13] = (float)data[7];
    array[14] = (float)data[11];
    array[15] = (float)1;
}

Matrix3::Matrix3() {
    data[0] = data[1] = data[2] = data[3] = data[4] = data[5] = data[6] = data[7] = data[8] = 0;
}

Matrix3::Matrix3(const Vector3 &compOne, const Vector3 &compTwo, const Vector3 &compThree) {
    setComponents(compOne, compTwo, compThree);
}

Matrix3::Matrix3(real c0, real c1, real c2, real c3, real c4, real c5, real c6, real c7, real c8) {
    data[0] = c0; data[1] = c1; data[2] = c2;
    data[3] = c3; data[4] = c4; data[5] = c5;
    data[6] = c6; data[7] = c7; data[8] = c8;
}

void Matrix3::setDiagonal(real a, real b, real c) {
    setInertiaTensorCoeffs(a, b, c);
}

void Matrix3::setInertiaTensorCoeffs(real ix, real iy, real iz, real ixy, real ixz, real iyz) {
    data[0] = ix;
    data[1] = data[3] = -ixy;
    data[2] = data[6] = -ixz;
    data[4] = iy;
    data[5] = data[7] = -iyz;
    data[8] = iz;
}

void Matrix3::setBlockInertiaTensor(const Vector3 &halfSizes, real mass) {
    Vector3 squares = halfSizes.componentProduct(halfSizes);
    setInertiaTensorCoeffs(0.3f*mass*(squares.y + squares.z),
        0.3f*mass*(squares.x + squares.z),
        0.3f*mass*(squares.x + squares.y));
}

void Matrix3::setSkewSymmetric(const Vector3 vector) {
    data[0] = data[4] = data[8] = 0;
    data[1] = -vector.z;
    data[2] = vector.y;
    data[3] = vector.z;
    data[5] = -vector.x;
    data[6] = -vector.y;
    data[7] = vector.x;
}

void Matrix3::setComponents(const Vector3 &compOne, const Vector3 &compTwo, const Vector3 &compThree) {
    data[0] = compOne.x;
    data[1] = compTwo.x;
    data[2] = compThree.x;
    data[3] = compOne.y;
    data[4] = compTwo.y;
    data[5] = compThree.y;
    data[6] = compOne.z;
    data[7] = compTwo.z;
    data[8] = compThree.z;
}

Vector3 Matrix3::operator*(const Vector3 &vector) const {
    return Vector3(
        vector.x * data[0] + vector.y * data[1] + vector.z * data[2],
        vector.x * data[3] + vector.y * data[4] + vector.z * data[5],
        vector.x * data[6] + vector.y * data[7] + vector.z * data[8]
        );
}

Vector3 Matrix3::transform(const Vector3 &vector) const {
    return (*this) * vector;
}

Vector3 Matrix3::transformTranspose(const Vector3 &vector) const {
    return Vector3(
        vector.x * data[0] + vector.y * data[3] + vector.z * data[6],
        vector.x * data[1] + vector.y * data[4] + vector.z * data[7],
        vector.x * data[2] + vector.y * data[5] + vector.z * data[8]
    );
}

Vector3 Matrix3::getRowVector(int i) const {
    return Vector3(data[i * 3], data[i * 3 + 1], data[i * 3 + 2]);
}

Vector3 Matrix3::getAxisVector(int i) const {
    return Vector3(data[i], data[i + 3], data[i + 6]);
}

void Matrix3::setInverse(const Matrix3 &m) {
    real t4 = m.data[0] * m.data[4];
    real t6 = m.data[0] * m.data[5];
    real t8 = m.data[1] * m.data[3];
    real t10 = m.data[2] * m.data[3];
    real t12 = m.data[1] * m.data[6];
    real t14 = m.data[2] * m.data[6];

    // Calculate the determinant
    real t16 = (t4*m.data[8] - t6*m.data[7] - t8*m.data[8] +
        t10*m.data[7] + t12*m.data[5] - t14*m.data[4]);

    // Make sure the determinant is non-zero.
    if (t16 == (real)0.0f) return;
    real t17 = 1 / t16;

    data[0] = (m.data[4] * m.data[8] - m.data[5] * m.data[7])*t17;
    data[1] = -(m.data[1] * m.data[8] - m.data[2] * m.data[7])*t17;
    data[2] = (m.data[1] * m.data[5] - m.data[2] * m.data[4])*t17;
    data[3] = -(m.data[3] * m.data[8] - m.data[5] * m.data[6])*t17;
    data[4] = (m.data[0] * m.data[8] - t14)*t17;
    data[5] = -(t6 - t10)*t17;
    data[6] = (m.data[3] * m.data[7] - m.data[4] * m.data[6])*t17;
    data[7] = -(m.data[0] * m.data[7] - t12)*t17;
    data[8] = (t4 - t8)*t17;
}

Matrix3 Matrix3::inverse() const {
    Matrix3 result;
    result.setInverse(*this);
    return result;
}

void Matrix3::invert() {
    setInverse(*this);
}

void Matrix3::setTranspose(const Matrix3 &m) {
    data[0] = m.data[0];
    data[1] = m.data[3];
    data[2] = m.data[6];
    data[3] = m.data[1];
    data[4] = m.data[4];
    data[5] = m.data[7];
    data[6] = m.data[2];
    data[7] = m.data[5];
    data[8] = m.data[8];
}

Matrix3 Matrix3::transpose() const {
    Matrix3 result;
    result.setTranspose(*this);
    return result;
}

Matrix3 Matrix3::operator*(const Matrix3 &o) const {
    return Matrix3(
        data[0] * o.data[0] + data[1] * o.data[3] + data[2] * o.data[6],
        data[0] * o.data[1] + data[1] * o.data[4] + data[2] * o.data[7],
        data[0] * o.data[2] + data[1] * o.data[5] + data[2] * o.data[8],

        data[3] * o.data[0] + data[4] * o.data[3] + data[5] * o.data[6],
        data[3] * o.data[1] + data[4] * o.data[4] + data[5] * o.data[7],
        data[3] * o.data[2] + data[4] * o.data[5] + data[5] * o.data[8],

        data[6] * o.data[0] + data[7] * o.data[3] + data[8] * o.data[6],
        data[6] * o.data[1] + data[7] * o.data[4] + data[8] * o.data[7],
        data[6] * o.data[2] + data[7] * o.data[5] + data[8] * o.data[8]
        );
}

void Matrix3::operator*=(const Matrix3 &o) {
    real t1;
    real t2;
    real t3;

    t1 = data[0] * o.data[0] + data[1] * o.data[3] + data[2] * o.data[6];
    t2 = data[0] * o.data[1] + data[1] * o.data[4] + data[2] * o.data[7];
    t3 = data[0] * o.data[2] + data[1] * o.data[5] + data[2] * o.data[8];
    data[0] = t1;
    data[1] = t2;
    data[2] = t3;

    t1 = data[3] * o.data[0] + data[4] * o.data[3] + data[5] * o.data[6];
    t2 = data[3] * o.data[1] + data[4] * o.data[4] + data[5] * o.data[7];
    t3 = data[3] * o.data[2] + data[4] * o.data[5] + data[5] * o.data[8];
    data[3] = t1;
    data[4] = t2;
    data[5] = t3;

    t1 = data[6] * o.data[0] + data[7] * o.data[3] + data[8] * o.data[6];
    t2 = data[6] * o.data[1] + data[7] * o.data[4] + data[8] * o.data[7];
    t3 = data[6] * o.data[2] + data[7] * o.data[5] + data[8] * o.data[8];
    data[6] = t1;
    data[7] = t2;
    data[8] = t3;
}

void Matrix3::operator*=(const real scalar) {
    data[0] *= scalar; data[1] *= scalar; data[2] *= scalar;
    data[3] *= scalar; data[4] *= scalar; data[5] *= scalar;
    data[6] *= scalar; data[7] *= scalar; data[8] *= scalar;
}

void Matrix3::operator+=(const Matrix3 &o) {
    data[0] += o.data[0]; data[1] += o.data[1]; data[2] += o.data[2];
    data[3] += o.data[3]; data[4] += o.data[4]; data[5] += o.data[5];
    data[6] += o.data[6]; data[7] += o.data[7]; data[8] += o.data[8];
}

void Matrix3::setOrientation(const Quaternion &q) {
    data[0] = 1 - (2 * q.j*q.j + 2 * q.k*q.k);
    data[1] = 2 * q.i*q.j + 2 * q.k*q.r;
    data[2] = 2 * q.i*q.k - 2 * q.j*q.r;
    data[3] = 2 * q.i*q.j - 2 * q.k*q.r;
    data[4] = 1 - (2 * q.i*q.i + 2 * q.k*q.k);
    data[5] = 2 * q.j*q.k + 2 * q.i*q.r;
    data[6] = 2 * q.i*q.k + 2 * q.j*q.r;
    data[7] = 2 * q.j*q.k - 2 * q.i*q.r;
    data[8] = 1 - (2 * q.i*q.i + 2 * q.j*q.j);
}

Matrix3 Matrix3::linearInterpolate(const Matrix3& a, const Matrix3& b, real prop) {
    Matrix3 result;
    for (unsigned i = 0; i < 9; i++) {
        result.data[i] = a.data[i] * (1 - prop) + b.data[i] * prop;
    }
    return result;
}

GLuint loadShaders(const char* vertex_file_path, const char* fragment_file_path) {
    // Read the Vertex Shader code from the file
    std::string vertexShaderCode;
    std::ifstream vertexShaderStream(vertex_file_path, std::ios::in);
    if (vertexShaderStream.is_open()) {
        std::string line;
        while (getline(vertexShaderStream, line)) {
            vertexShaderCode += "\n" + line;
        }
        vertexShaderStream.close();
    }
    else {
        throw (std::string("Impossible to open ") + vertex_file_path + ".").c_str();
    }

    // Read the Fragment Shader code from the file
    std::string fragmentShaderCode;
    std::ifstream fragmentShaderStream(fragment_file_path, std::ios::in);
    if (fragmentShaderStream.is_open()) {
        std::string line;
        while (getline(fragmentShaderStream, line)) {
            fragmentShaderCode += "\n" + line;
        }
        fragmentShaderStream.close();
    }
    else {
        throw (std::string("Impossible to open ") + fragment_file_path + ".").c_str();
    }

    GLint result = GL_FALSE;
    int infoLogLength;

    // Compile Vertex Shader
    char const * vertexSourcePointer = vertexShaderCode.c_str();
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderID, 1, &vertexSourcePointer, NULL);
    glCompileShader(vertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (result == GL_FALSE) {
        std::vector<char> vertexShaderErrorMessage(infoLogLength + 1);
        glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
        throw (std::string("Vertex shader error: ") + &vertexShaderErrorMessage[0]).c_str();
    }

    // Compile Fragment Shader
    char const * fragmentSourcePointer = fragmentShaderCode.c_str();
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderID, 1, &fragmentSourcePointer, NULL);
    glCompileShader(fragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (result == GL_FALSE) {
        std::vector<char> fragmentShaderErrorMessage(infoLogLength + 1);
        glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, &fragmentShaderErrorMessage[0]);
        throw (std::string("Fragment shader error: ") + &fragmentShaderErrorMessage[0]).c_str();
    }

    // Link the program
    GLuint programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);

    // Check the program
    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (result == GL_FALSE) {
        std::vector<char> programErrorMessage(infoLogLength + 1);
        throw (std::string("Shader program error: ") + &programErrorMessage[0]).c_str();
    }

    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    return programID;
}

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

GLuint loadDDS(const char * imagepath) {
    unsigned char header[124];

    FILE *fp;

    /* try to open the file */
    fp = fopen(imagepath, "rb");
    if (fp == NULL){
        printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", imagepath); getchar();
        return 0;
    }

    /* verify the type of file */
    char filecode[4];
    fread(filecode, 1, 4, fp);
    if (strncmp(filecode, "DDS ", 4) != 0) {
        fclose(fp);
        return 0;
    }

    /* get the surface desc */
    fread(&header, 124, 1, fp);

    unsigned int height = *(unsigned int*)&(header[8]);
    unsigned int width = *(unsigned int*)&(header[12]);
    unsigned int linearSize = *(unsigned int*)&(header[16]);
    unsigned int mipMapCount = *(unsigned int*)&(header[24]);
    unsigned int fourCC = *(unsigned int*)&(header[80]);

    unsigned char * buffer;
    unsigned int bufsize;
    /* how big is it going to be including all mipmaps? */
    bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
    buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
    fread(buffer, 1, bufsize, fp);
    /* close the file pointer */
    fclose(fp);

    unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4;
    unsigned int format;
    switch (fourCC)
    {
    case FOURCC_DXT1:
        format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
        break;
    case FOURCC_DXT3:
        format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
        break;
    case FOURCC_DXT5:
        format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
        break;
    default:
        free(buffer);
        return 0;
    }

    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    unsigned int offset = 0;

    /* load the mipmaps */
    for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
    {
        unsigned int size = ((width + 3) / 4)*((height + 3) / 4)*blockSize;
        glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
            0, size, buffer + offset);

        offset += size;
        width /= 2;
        height /= 2;

        // Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
        if (width < 1) width = 1;
        if (height < 1) height = 1;

    }

    free(buffer);

    return textureID;
}

//#include <vector>
//#include <cstring>

//#include <GL/glew.h>

//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//using namespace glm;
//
//#include "shader.hpp"
//#include "texture.hpp"
//
//#include "text2D.hpp"
//
unsigned int Text2DTextureID;
unsigned int Text2DVertexBufferID;
unsigned int Text2DUVBufferID;
unsigned int Text2DShaderID;
unsigned int Text2DUniformID;

void initText2D(const char * texturePath){
    // Initialize texture
    Text2DTextureID = loadDDS(texturePath);

    // Initialize VBO
    glGenBuffers(1, &Text2DVertexBufferID);
    glGenBuffers(1, &Text2DUVBufferID);

    // Initialize Shader
    Text2DShaderID = loadShaders("TextVertexShader.vertexshader", "TextVertexShader.fragmentshader");

    // Initialize uniforms' IDs
    Text2DUniformID = glGetUniformLocation(Text2DShaderID, "myTextureSampler");

}

void printText2D(const char * text, int x, int y, int size) {

    size_t length = strlen(text);

    // Fill buffers
    std::vector<glm::vec2> vertices;
    std::vector<glm::vec2> UVs;
    for (unsigned int i = 0; i<length; i++) {

        glm::vec2 vertex_up_left = glm::vec2(x + i*size, y + size);
        glm::vec2 vertex_up_right = glm::vec2(x + i*size + size, y + size);
        glm::vec2 vertex_down_right = glm::vec2(x + i*size + size, y);
        glm::vec2 vertex_down_left = glm::vec2(x + i*size, y);

        vertices.push_back(vertex_up_left);
        vertices.push_back(vertex_down_left);
        vertices.push_back(vertex_up_right);

        vertices.push_back(vertex_down_right);
        vertices.push_back(vertex_up_right);
        vertices.push_back(vertex_down_left);

        char character = text[i];
        float uv_x = (character % 16) / 16.0f;
        float uv_y = (character / 16) / 16.0f;

        glm::vec2 uv_up_left = glm::vec2(uv_x, uv_y);
        glm::vec2 uv_up_right = glm::vec2(uv_x + 1.0f / 16.0f, uv_y);
        glm::vec2 uv_down_right = glm::vec2(uv_x + 1.0f / 16.0f, (uv_y + 1.0f / 16.0f));
        glm::vec2 uv_down_left = glm::vec2(uv_x, (uv_y + 1.0f / 16.0f));
        UVs.push_back(uv_up_left);
        UVs.push_back(uv_down_left);
        UVs.push_back(uv_up_right);

        UVs.push_back(uv_down_right);
        UVs.push_back(uv_up_right);
        UVs.push_back(uv_down_left);
    }
    glBindBuffer(GL_ARRAY_BUFFER, Text2DVertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, Text2DUVBufferID);
    glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(glm::vec2), &UVs[0], GL_STATIC_DRAW);

    // Bind shader
    glUseProgram(Text2DShaderID);

    // Bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Text2DTextureID);
    // Set our "myTextureSampler" sampler to user Texture Unit 0
    glUniform1i(Text2DUniformID, 0);

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, Text2DVertexBufferID);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // 2nd attribute buffer : UVs
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, Text2DUVBufferID);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Draw call
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    glDisable(GL_BLEND);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

}

void cleanupText2D() {

    // Delete buffers
    glDeleteBuffers(1, &Text2DVertexBufferID);
    glDeleteBuffers(1, &Text2DUVBufferID);

    // Delete texture
    glDeleteTextures(1, &Text2DTextureID);

    // Delete shader
    glDeleteProgram(Text2DShaderID);
}
