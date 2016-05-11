typedef float real;
const real PI = 3.1415926535897f;

class Vector3 {
// constructors and destructors
public:
    Vector3() : x(0.0), y(0.0), z(0.0) {}
    Vector3(const real x, const real y, const real z): x(x), y(y), z(z) {}

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
};

GLuint loadShaders(const char* vertex_file_path, const char* fragment_file_path);
