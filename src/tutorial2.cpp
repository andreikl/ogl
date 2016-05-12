// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "app.h"
#include "body.h"
#include "input.h"

#include "tutorial2.h"

Application* Tutorial2::Create() {
    auto tutorial2 = new Tutorial2();
    tutorial2->init();
    return tutorial2;
}

void Tutorial2::initWorld() {
    Application::initWorld();

    input = InputOrbit::create(*this, 3);
    body = RigidBodySphere::Create();
}

void Tutorial2::draw() {
    body->draw(*this);
}

void Tutorial2::dispose() {
    Application::dispose();

    delete body;
    delete input;
}
