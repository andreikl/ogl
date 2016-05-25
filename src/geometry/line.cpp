// c/c++
#include "math.h"

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>

#include "core.hpp"
#include "app.hpp"
#include "geometry/body.hpp"
#include "geometry/Line.hpp"

Line::Line() {
}

Line::~Line() {
    glDeleteBuffers(1, &vertexbuffer);
}

RigidBody* Line::Create() {
    Line* p = new Line();

    //left point
    p->vertices.push_back(Vector3(-1.0f, 0.0f, 0.0f));
    p->vertices.push_back(Vector3(1.0f, 0.0f, 0.0f));

    p->init();
    return p;
}

void Line::init() {
    // Create and compile our GLSL program from the shaders
    programID = loadShaders("SimpleTransform.vertexshader", "SingleColor.fragmentshader");

    // Get a handle for our "MVP" uniform
    matrixID = glGetUniformLocation(programID, "MVP");
    colorID = glGetUniformLocation(programID, "uColor");

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vector3), vertices.data(), GL_STATIC_DRAW);
}

void Line::draw(const Application& app) {
    glUseProgram(programID);

    real arr[16];
    Matrix4 m = this->getTransform();
    m.fillGLArray(arr);

    glm::mat4 tmp1 = glm::mat4(
        arr[0], arr[1], arr[2], arr[3],
        arr[4], arr[5], arr[6], arr[7],
        arr[8], arr[9], arr[10], arr[11],
        arr[12], arr[13], arr[14], arr[15]);

    glm::mat4 mvp = app.getProjection() * app.getView() * tmp1;
    // ser transformation matrix to the "MVP" uniform
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);
    // set solid color
    glUniform4f(colorID, 1.0f, 0.0f, 0.0f, 1.0f);

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
        (GLsizei)vertices.size() // count
    );

    glDisableVertexAttribArray(0);
}
