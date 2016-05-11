// c/c++
#include "math.h"

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>

#include "point.h"

// PointBase -----------------
PointBase::PointBase() {
}

PointBase::~PointBase() {
}

// PointSphere ---------------
PointSphere::PointSphere() {
}

PointBase& PointSphere::Create(int columns = 5, int rows = 5) {
    PointSphere* p = new PointSphere();

    // top vertex
    p->vertices.push_back(Vector3(0.0, 1.0, 0.0));

    real step_row_angle = PI / rows;
    real step_col_angle = 2 * PI / columns;

    // vertex
    real cur_row_angle = step_row_angle;
    for (int i = 0; i < rows - 1; i++) {
        real cur_row_sin = sin(cur_row_angle);
        real cur_row_cos = cos(cur_row_angle);

        real cur_col_angle = 0.0;
        for (int j = 0; j <= columns; j++) {
            real cur_col_sin = sin(cur_col_angle);
            real cur_col_cos = cos(cur_col_angle);

            p->vertices.push_back(Vector3(
                cur_col_sin * cur_row_sin,
                cur_row_cos,
                cur_col_cos * cur_row_sin
            ));

            cur_col_angle += step_col_angle;
        }
        cur_row_angle += step_row_angle;
    }

    // bottom vertex
    p->triangles.push_back(0);
    p->triangles.push_back(-1);
    p->triangles.push_back(0);
    // sets up tringtles
    for (int i = 0; i < columns; i++) {
        p->triangles.push_back(0);
        p->triangles.push_back(i + 1);
        p->triangles.push_back(i + 2);
    }
    int row_cur = 1;
    int row_next = row_cur + (columns + 1);
    for (int i = 0; i < rows - 2; i++) {
        for (int j = 0; j < columns; j++) {
            p->triangles.push_back(row_cur + j);
            p->triangles.push_back(row_next + j);
            p->triangles.push_back(row_next + j + 1);
        }
        for (int j = 0; j < columns; j++) {
            p->triangles.push_back(row_cur + j);
            p->triangles.push_back(row_cur + j + 1);
            p->triangles.push_back(row_next + j + 1);
        }
        row_cur = row_next;
        row_next += (columns + 1);
    }
    for (int i = 0; i < columns; i++) {
        p->triangles.push_back(row_cur + i);
        p->triangles.push_back(row_cur + i + 1);
        p->triangles.push_back(row_next);
    }
    return *p;
}

void PointSphere::init() {
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    // Create and compile our GLSL program from the shaders
    programID = loadShaders("SimpleTransform.vertexshader", "SingleColor.fragmentshader");
    // Get a handle for our "MVP" uniform
    matrixID = glGetUniformLocation(programID, "MVP");

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(real), vertices.data(), GL_STATIC_DRAW);
}

void PointSphere::draw() {
}
