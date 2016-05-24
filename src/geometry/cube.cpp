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
#include "geometry/cube.hpp"

Cube::Cube() {
}

Cube::~Cube() {
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &elementbuffer);
}

RigidBody* Cube::Create() {
    Cube* p = new Cube();

    //top front left corner
    p->vertices.push_back(Vector3(-1.0, 1.0, 1.0));
    //top front right corner
    p->vertices.push_back(Vector3(1.0, 1.0, 1.0));
    //top rear right corner
    p->vertices.push_back(Vector3(1.0, 1.0, -1.0));
    //top rear left corner
    p->vertices.push_back(Vector3(-1.0, 1.0, -1.0));
    //bottom front left corner
    p->vertices.push_back(Vector3(-1.0, -1.0, 1.0));
    //bottom front right corner
    p->vertices.push_back(Vector3(1.0, -1.0, 1.0));
    //bottom rear right corner
    p->vertices.push_back(Vector3(1.0, -1.0, -1.0));
    //bottom rear left corner
    p->vertices.push_back(Vector3(-1.0, -1.0, -1.0));

    //top front edge
    p->indices.push_back(0);
    p->indices.push_back(1);
    //top left edge
    p->indices.push_back(1);
    p->indices.push_back(2);
    //top rear edge
    p->indices.push_back(2);
    p->indices.push_back(3);
    //top right edge
    p->indices.push_back(3);
    p->indices.push_back(0);
    //bottom front edge
    p->indices.push_back(4);
    p->indices.push_back(5);
    //bottom left edge
    p->indices.push_back(5);
    p->indices.push_back(6);
    //bottom rear edge
    p->indices.push_back(6);
    p->indices.push_back(7);
    //bottom right edge
    p->indices.push_back(7);
    p->indices.push_back(4);
    //bottom front edge
    p->indices.push_back(4);
    p->indices.push_back(5);
    //left front edge
    p->indices.push_back(0);
    p->indices.push_back(4);
    //right front edge
    p->indices.push_back(1);
    p->indices.push_back(5);
    //right rear edge
    p->indices.push_back(2);
    p->indices.push_back(6);
    //left rear edge
    p->indices.push_back(3);
    p->indices.push_back(7);

    p->init();
    return p;
}

void Cube::init() {
    // Create and compile our GLSL program from the shaders
    programID = loadShaders("SimpleTransform.vertexshader", "SingleColor.fragmentshader");

    // Get a handle for our "MVP" uniform
    matrixID = glGetUniformLocation(programID, "MVP");
    colorID = glGetUniformLocation(programID, "uColor");

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vector3), vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &elementbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, elementbuffer);
    glBufferData(GL_ARRAY_BUFFER, indices.size() * sizeof(short), indices.data(), GL_STATIC_DRAW);
}

void Cube::draw(const Application& app) {
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
    glUniform4f(colorID, 0.0, 1.0, 0.0, 1.0f);

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
    glDrawElements(GL_LINES, // mode
        (GLsizei)indices.size(), // count
        GL_UNSIGNED_SHORT, // type
        nullptr
    );

    glDisableVertexAttribArray(0);
}
