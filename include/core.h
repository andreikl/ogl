GLuint loadShaders(const char* vertex_file_path, const char* fragment_file_path);

#define PRECISION FLOAT

#if PRECISION == FLOAT

/**
* Defines we're in single precision mode, for any code
* that needs to be conditionally compiled.
*/
#define SINGLE_PRECISION

/**
* Defines a real number precision. Cyclone can be compiled in
* single or double precision versions. By default single precision is
* provided.
*/
typedef float real;

/** Defines the highest value for the real number. */
#define REAL_MAX FLT_MAX

/** Defines the precision of the square root operator. */
#define real_sqrt sqrtf
/** Defines the precision of the absolute magnitude operator. */
#define real_abs fabsf
/** Defines the precision of the sine operator. */
#define real_sin sinf

/** Defines the precision of the cosine operator. */
#define real_cos cosf

/** Defines the precision of the exponent operator. */
#define real_exp expf
/** Defines the precision of the power operator. */
#define real_pow powf

/** Defines the precision of the floating point modulo operator. */
#define real_fmod fmodf

/** Defines the number e on which 1+e == 1 **/
#define real_epsilon FLT_EPSILON

#define R_PI 3.14159f
#else
#define DOUBLE_PRECISION
typedef double real;
#define REAL_MAX DBL_MAX
#define real_sqrt sqrt
#define real_abs fabs
#define real_sin sin
#define real_cos cos
#define real_exp exp
#define real_pow pow
#define real_fmod fmod
#define real_epsilon DBL_EPSILON
#define R_PI 3.14159265358979
#endif

/**
* Holds a vector in 3 dimensions. Four data members are allocated
* to ensure alignment in an array.
*
* @note This class contains a lot of inline methods for basic
* mathematics. The implementations are included in the header
* file.
*/
class Vector3 {
public:
    /** Holds the value along the x axis. */
    real x;

    /** Holds the value along the y axis. */
    real y;

    /** Holds the value along the z axis. */
    real z;

private:
    /** Padding to ensure 4 word alignment. */
    real pad;

public:
    /** The default constructor creates a zero vector. */
    Vector3();

    /**
    * The explicit constructor creates a vector with the given
    * components.
    */
    Vector3(const real x, const real y, const real z);

    const static Vector3 GRAVITY;
    const static Vector3 HIGH_GRAVITY;
    const static Vector3 UP;
    const static Vector3 RIGHT;
    const static Vector3 OUT_OF_SCREEN;
    const static Vector3 X;
    const static Vector3 Y;
    const static Vector3 Z;

    real operator[] (unsigned i) const;
    real& operator[] (unsigned i);

    /**
    * Returns the value of the given vector added to this.
    */
    Vector3 operator+ (const Vector3& v) const;
    /** Adds the given vector to this. */
    void operator+= (const Vector3& v);

    /**
    * Returns the value of the given vector subtracted from this.
    */
    Vector3 operator- (const Vector3& v) const;

    /** Subtracts the given vector from this. */
    void operator-= (const Vector3& v);

    /** Returns a copy of this vector scaled the given value. */
    Vector3 operator* (const real value) const;

    /** Multiplies this vector by the given scalar. */
    void operator*= (const real value);

    /**
    * Calculates and returns a component-wise product of this
    * vector with the given vector.
    */
    Vector3 componentProduct(const Vector3 &vector) const;

    /**
    * Performs a component-wise product with the given vector and
    * sets this vector to its result.
    */
    void componentProductUpdate(const Vector3 &vector);

    /**
    * Calculates and returns the vector product of this vector
    * with the given vector.
    */
    Vector3 vectorProduct(const Vector3 &vector) const;

    /**
    * Updates this vector to be the vector product of its current
    * value and the given vector.
    */
    void operator %= (const Vector3 &vector);

    /**
    * Calculates and returns the vector product of this vector
    * with the given vector.
    */
    Vector3 operator% (const Vector3 &vector) const;

    /**
    * Calculates and returns the scalar product of this vector
    * with the given vector.
    */
    real scalarProduct(const Vector3 &vector) const;

    /**
    * Calculates and returns the scalar product of this vector
    * with the given vector.
    */
    real operator *(const Vector3 &vector) const;

    /**
    * Adds the given vector to this, scaled by the given amount.
    */
    void addScaledVector(const Vector3& vector, real scale);

    /** Gets the magnitude of this vector. */
    real magnitude() const;

    /** Gets the squared magnitude of this vector. */
    real squareMagnitude() const;

    /** Limits the size of the vector to the given maximum. */
    void trim(real size);

    /** Turns a non-zero vector into a vector of unit length. */
    void normalise();

    /** Returns the normalised version of a vector. */
    Vector3 unit() const;

    /** Checks if the two vectors have identical components. */
    bool operator== (const Vector3& other) const;

    /** Checks if the two vectors have non-identical components. */
    bool operator!= (const Vector3& other) const;

    /**
    * Checks if this vector is component-by-component less than
    * the other.
    *
    * @note This does not behave like a single-value comparison:
    * !(a < b) does not imply (b >= a).
    */
    bool operator<(const Vector3& other) const;

    /**
    * Checks if this vector is component-by-component less than
    * the other.
    *
    * @note This does not behave like a single-value comparison:
    * !(a < b) does not imply (b >= a).
    */
    bool operator>(const Vector3& other) const;

    /**
    * Checks if this vector is component-by-component less than
    * the other.
    *
    * @note This does not behave like a single-value comparison:
    * !(a <= b) does not imply (b > a).
    */
    bool operator<=(const Vector3& other) const;

    /**
    * Checks if this vector is component-by-component less than
    * the other.
    *
    * @note This does not behave like a single-value comparison:
    * !(a <= b) does not imply (b > a).
    */
    bool operator>=(const Vector3& other) const;

    /** Zero all the components of the vector. */
    void clear();

    /** Flips all the components of the vector. */
    void invert();
};

extern real sleepEpsilon;

/**
* Holds a three degree of freedom orientation.
*
* Quaternions have
* several mathematical properties that make them useful for
* representing orientations, but require four items of data to
* hold the three degrees of freedom. These four items of data can
* be viewed as the coefficients of a complex number with three
* imaginary parts. The mathematics of the quaternion is then
* defined and is roughly correspondent to the math of 3D
* rotations. A quaternion is only a valid rotation if it is
* normalised: i.e. it has a length of 1.
*
* @note Angular velocity and acceleration can be correctly
* represented as vectors. Quaternions are only needed for
* orientation.
*/
class Quaternion {
public:
    union {
        struct {
            /**
            * Holds the real component of the quaternion.
            */
            real r;

            /**
            * Holds the first complex component of the
            * quaternion.
            */
            real i;

            /**
            * Holds the second complex component of the
            * quaternion.
            */
            real j;

            /**
            * Holds the third complex component of the
            * quaternion.
            */
            real k;
        };

        /**
        * Holds the quaternion data in array form.
        */
        real data[4];
    };

    // ... other Quaternion code as before ...

    /**
    * The default constructor creates a quaternion representing
    * a zero rotation.
    */
    Quaternion();

    /**
    * The explicit constructor creates a quaternion with the given
    * components.
    *
    * @param r The real component of the rigid body's orientation
    * quaternion.
    *
    * @param i The first complex component of the rigid body's
    * orientation quaternion.
    *
    * @param j The second complex component of the rigid body's
    * orientation quaternion.
    *
    * @param k The third complex component of the rigid body's
    * orientation quaternion.
    *
    * @note The given orientation does not need to be normalised,
    * and can be zero. This function will not alter the given
    * values, or normalise the quaternion. To normalise the
    * quaternion (and make a zero quaternion a legal rotation),
    * use the normalise function.
    *
    * @see normalise
    */
    Quaternion(const real r, const real i, const real j, const real k);

    /**
    * Normalises the quaternion to unit length, making it a valid
    * orientation quaternion.
    */
    void normalise();

    /**
    * Multiplies the quaternion by the given quaternion.
    *
    * @param multiplier The quaternion by which to multiply.
    */
    void operator *=(const Quaternion &multiplier);

    /**
    * Adds the given vector to this, scaled by the given amount.
    * This is used to update the orientation quaternion by a rotation
    * and time.
    *
    * @param vector The vector to add.
    *
    * @param scale The amount of the vector to add.
    */
    void addScaledVector(const Vector3& vector, real scale);

    void rotateByVector(const Vector3& vector);
};

/**
* Holds a transform matrix, consisting of a rotation matrix and
* a position. The matrix has 12 elements, it is assumed that the
* remaining four are (0,0,0,1); producing a homogenous matrix.
*/
class Matrix4 {
public:
    /**
    * Holds the transform matrix data in array form.
    */
    real data[12];

    /**
    * Creates an identity matrix.
    */
    Matrix4();

    /**
    * Sets the matrix to be a diagonal matrix with the given coefficients.
    */
    void setDiagonal(real a, real b, real c);

    /**
    * Returns a matrix which is this matrix multiplied by the given
    * other matrix.
    */
    Matrix4 operator*(const Matrix4 &o) const;

    /**
    * Transform the given vector by this matrix.
    *
    * @param vector The vector to transform.
    */
    Vector3 operator*(const Vector3 &vector) const;

    /**
    * Transform the given vector by this matrix.
    *
    * @param vector The vector to transform.
    */
    Vector3 transform(const Vector3 &vector) const;

    /**
    * Returns the determinant of the matrix.
    */
    real getDeterminant() const;

    /**
    * Sets the matrix to be the inverse of the given matrix.
    *
    * @param m The matrix to invert and use to set this.
    */
    void setInverse(const Matrix4 &m);

    /** Returns a new matrix containing the inverse of this matrix. */
    Matrix4 inverse() const;

    /**
    * Inverts the matrix.
    */
    void invert();

    /**
    * Transform the given direction vector by this matrix.
    *
    * @note When a direction is converted between frames of
    * reference, there is no translation required.
    *
    * @param vector The vector to transform.
    */
    Vector3 transformDirection(const Vector3 &vector) const;

    /**
    * Transform the given direction vector by the
    * transformational inverse of this matrix.
    *
    * @note This function relies on the fact that the inverse of
    * a pure rotation matrix is its transpose. It separates the
    * translational and rotation components, transposes the
    * rotation, and multiplies out. If the matrix is not a
    * scale and shear free transform matrix, then this function
    * will not give correct results.
    *
    * @note When a direction is converted between frames of
    * reference, there is no translation required.
    *
    * @param vector The vector to transform.
    */
    Vector3 transformInverseDirection(const Vector3 &vector) const;

    /**
    * Transform the given vector by the transformational inverse
    * of this matrix.
    *
    * @note This function relies on the fact that the inverse of
    * a pure rotation matrix is its transpose. It separates the
    * translational and rotation components, transposes the
    * rotation, and multiplies out. If the matrix is not a
    * scale and shear free transform matrix, then this function
    * will not give correct results.
    *
    * @param vector The vector to transform.
    */
    Vector3 transformInverse(const Vector3 &vector) const;

    /**
    * Gets a vector representing one axis (i.e. one column) in the matrix.
    *
    * @param i The row to return. Row 3 corresponds to the position
    * of the transform matrix.
    *
    * @return The vector.
    */
    Vector3 getAxisVector(int i) const;

    /**
    * Sets this matrix to be the rotation matrix corresponding to
    * the given quaternion.
    */
    void setOrientationAndPos(const Quaternion &q, const Vector3 &pos);

    /**
    * Fills the given array with this transform matrix, so it is
    * usable as an open-gl transform matrix. OpenGL uses a column
    * major format, so that the values are transposed as they are
    * written.
    */
    void fillGLArray(float array[16]) const;
};

/**
* Holds an inertia tensor, consisting of a 3x3 row-major matrix.
* This matrix is not padding to produce an aligned structure, since
* it is most commonly used with a mass (single real) and two
* damping coefficients to make the 12-element characteristics array
* of a rigid body.
*/
class Matrix3
{
public:
    /**
    * Holds the tensor matrix data in array form.
    */
    real data[9];

    /**
    * Creates a new matrix.
    */
    Matrix3();

    /**
    * Creates a new matrix with the given three vectors making
    * up its columns.
    */
    Matrix3(const Vector3 &compOne, const Vector3 &compTwo, const Vector3 &compThree);

    /**
    * Creates a new matrix with explicit coefficients.
    */
    Matrix3(real c0, real c1, real c2, real c3, real c4, real c5, real c6, real c7, real c8);

    /**
    * Sets the matrix to be a diagonal matrix with the given
    * values along the leading diagonal.
    */
    void setDiagonal(real a, real b, real c);

    /**
    * Sets the value of the matrix from inertia tensor values.
    */
    void setInertiaTensorCoeffs(real ix, real iy, real iz, real ixy = 0, real ixz = 0, real iyz = 0);

    /**
    * Sets the value of the matrix as an inertia tensor of
    * a rectangular block aligned with the body's coordinate
    * system with the given axis half-sizes and mass.
    */
    void setBlockInertiaTensor(const Vector3 &halfSizes, real mass);

    /**
    * Sets the matrix to be a skew symmetric matrix based on
    * the given vector. The skew symmetric matrix is the equivalent
    * of the vector product. So if a,b are vectors. a x b = A_s b
    * where A_s is the skew symmetric form of a.
    */
    void setSkewSymmetric(const Vector3 vector);

    /**
    * Sets the matrix values from the given three vector components.
    * These are arranged as the three columns of the vector.
    */
    void setComponents(const Vector3 &compOne, const Vector3 &compTwo, const Vector3 &compThree);

    /**
    * Transform the given vector by this matrix.
    *
    * @param vector The vector to transform.
    */
    Vector3 operator*(const Vector3 &vector) const;

    /**
    * Transform the given vector by this matrix.
    *
    * @param vector The vector to transform.
    */
    Vector3 transform(const Vector3 &vector) const;

    /**
    * Transform the given vector by the transpose of this matrix.
    *
    * @param vector The vector to transform.
    */
    Vector3 transformTranspose(const Vector3 &vector) const;

    /**
    * Gets a vector representing one row in the matrix.
    *
    * @param i The row to return.
    */
    Vector3 getRowVector(int i) const;

    /**
    * Gets a vector representing one axis (i.e. one column) in the matrix.
    *
    * @param i The row to return.
    *
    * @return The vector.
    */
    Vector3 getAxisVector(int i) const;

    /**
    * Sets the matrix to be the inverse of the given matrix.
    *
    * @param m The matrix to invert and use to set this.
    */
    void setInverse(const Matrix3 &m);

    /** Returns a new matrix containing the inverse of this matrix. */
    Matrix3 inverse() const;

    /**
    * Inverts the matrix.
    */
    void invert();

    /**
    * Sets the matrix to be the transpose of the given matrix.
    *
    * @param m The matrix to transpose and use to set this.
    */
    void setTranspose(const Matrix3 &m);

    /** Returns a new matrix containing the transpose of this matrix. */
    Matrix3 transpose() const;

    /**
    * Returns a matrix which is this matrix multiplied by the given
    * other matrix.
    */
    Matrix3 operator*(const Matrix3 &o) const;

    /**
    * Multiplies this matrix in place by the given other matrix.
    */
    void operator*=(const Matrix3 &o);

    /**
    * Multiplies this matrix in place by the given scalar.
    */
    void operator*=(const real scalar);

    /**
    * Does a component-wise addition of this matrix and the given
    * matrix.
    */
    void operator+=(const Matrix3 &o);

    /**
    * Sets this matrix to be the rotation matrix corresponding to
    * the given quaternion.
    */
    void setOrientation(const Quaternion &q);

    /**
    * Interpolates a couple of matrices.
    */
    static Matrix3 linearInterpolate(const Matrix3& a, const Matrix3& b, real prop);
};
