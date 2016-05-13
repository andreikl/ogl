// c/c++
#include "math.h"

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>

#include "core.h"
#include "app.h"
#include "geometry/body.h"
#include "geometry/grid.h"

Grid::Grid() {
}

Grid::~Grid() {
    glDeleteBuffers(1, &vertexbuffer);
}

RigidBodyBase* Grid::Create(int columns, int rows) {
    Grid* p = new Grid();

    real step_column = 2.0f / columns;
    real step_row = 2.0f / rows;

    // vertices
    real cur_column = -1.0;
    for (int i = 0; i <= columns; i++) {
        p->vertices.push_back(Vector3(cur_column, -1.0, -1.0));
        p->vertices.push_back(Vector3(cur_column, -1.0, 1.0));
        cur_column += step_column;
    }
    real cur_row = -1.0;
    for (int i = 0; i <= columns; i++) {
        p->vertices.push_back(Vector3(-1.0, -1.0, cur_row));
        p->vertices.push_back(Vector3(1.0, -1.0, cur_row));
        cur_row += step_row;
    }

    p->init();
    return p;
}

void Grid::init() {
    // Create and compile our GLSL program from the shaders
    programID = loadShaders("SimpleTransform.vertexshader", "SingleColor.fragmentshader");

    // Get a handle for our "MVP" uniform
    matrixID = glGetUniformLocation(programID, "MVP");
    colorID = glGetUniformLocation(programID, "uColor");

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vector3), vertices.data(), GL_STATIC_DRAW);
}

void Grid::draw(const Application& app) {
    glUseProgram(programID);

    glm::mat4 mvp = app.getProjection() * app.getView();
    // ser transformation matrix to the "MVP" uniform
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);
    // set solid color
    glUniform4f(colorID, 0.5f, 0.5f, 0.5f, 1.0f);

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

    // Draw the triangles !
    glDrawArrays(GL_LINES, // mode
        0, // first
        vertices.size() // count
    );

    glDisableVertexAttribArray(0);
}
