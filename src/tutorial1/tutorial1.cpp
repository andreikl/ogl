// Include GLEW
#include <GL/glew.h>

#include "inputOrbit.h"
#include "tutorial1.h"

GLuint programID;
GLuint matrixID;

GLuint vertexbuffer;
GLuint vertexArrayID;

Application* Tutorial1::Create() {
    auto tutorial1 = new Tutorial1();
    tutorial1->init();
    return tutorial1;
}

void Tutorial1::draw() {

    glUseProgram(programID);

	glm::mat4 mvp = projection * view;
	// ser transformation matrix to the "MVP" uniform
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

    glDisableVertexAttribArray(0);
}

void Tutorial1::initWorld() {
    Application::initWorld();

	input = InputOrbit::create(*this, 3);

    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    // Create and compile our GLSL program from the shaders
	programID = this->loadShaders("SimpleTransform.vertexshader", "SingleColor.fragmentshader");
	// Get a handle for our "MVP" uniform
	matrixID = glGetUniformLocation(programID, "MVP");

    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
    };
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

void Tutorial1::dispose() {
    Application::dispose();

    // Cleanup VBO
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteVertexArrays(1, &vertexArrayID);
    glDeleteProgram(programID);
}
