// c/c++
#include "math.h"

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>

#include "app.h"
#include "point.h"

// PointBase -----------------
PointBase::PointBase() {
}

PointBase::~PointBase() {
}

// PointSphere ---------------
PointSphere::PointSphere() {
}

PointSphere::~PointSphere() {
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &elementbuffer);
}

PointBase* PointSphere::Create(int columns, int rows) {
    PointSphere* p = new PointSphere();

    // top vertex
    p->vertices.push_back(Vector3(0.0, 1.0, 0.0));

    real step_row_angle = PI / rows;
    real step_col_angle = 2 * PI / columns;

    // vertices
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
    p->vertices.push_back(Vector3(0.0, -1.0, 0.0));

    // sets up tringtles
    for (int i = 0; i < columns; i++) {
        p->indices.push_back(0);
        p->indices.push_back(i + 1);
        p->indices.push_back(i + 2);
    }
    int row_cur = 1;
    int row_next = row_cur + (columns + 1);
    for (int i = 0; i < rows - 2; i++) {
        for (int j = 0; j < columns; j++) {
            p->indices.push_back(row_cur + j);
            p->indices.push_back(row_next + j);
            p->indices.push_back(row_next + j + 1);
        }
        for (int j = 0; j < columns; j++) {
            p->indices.push_back(row_cur + j);
            p->indices.push_back(row_cur + j + 1);
            p->indices.push_back(row_next + j + 1);
        }
        row_cur = row_next;
        row_next += (columns + 1);
    }
    for (int i = 0; i < columns; i++) {
        p->indices.push_back(row_cur + i);
        p->indices.push_back(row_cur + i + 1);
        p->indices.push_back(row_next);
    }

    p->init();
    return p;
}

void PointSphere::init() {
    //glGenVertexArrays(1, &vertexArrayID);
    //glBindVertexArray(vertexArrayID);

    // Create and compile our GLSL program from the shaders
    programID = loadShaders("SimpleTransform.vertexshader", "SingleColor.fragmentshader");

    // Get a handle for our "MVP" uniform
    matrixID = glGetUniformLocation(programID, "MVP");

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vector3), vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &elementbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, elementbuffer);
    glBufferData(GL_ARRAY_BUFFER, indices.size() * sizeof(short), indices.data(), GL_STATIC_DRAW);
}

void PointSphere::draw(const Application& app) {

    glUseProgram(programID);

    glm::mat4 mvp = app.getProjection() * app.getView();
    // ser transformation matrix to the "MVP" uniform
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0, // attribute 0. No particular reason for 0, but must match the layout in the shader.
        4, // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0, // stride
        nullptr // array buffer offset
    );

    // Index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

    // Draw the triangles !
    glDrawElements(GL_TRIANGLES, // mode
        indices.size(), // count
        GL_UNSIGNED_SHORT, // type
        nullptr // element array buffer offset
    );

    glDisableVertexAttribArray(0);
}
