// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>

#include "core.hpp"
#include "app.hpp"
#include "input.hpp"

#include "geometry/body.hpp"
#include "geometry/grid.hpp"
#include "geometry/cube.hpp"

#include "tutorial2.hpp"

Application* Tutorial2::Create() {
    auto app = new Tutorial2();
    app->init();
    return app;
}

void Tutorial2::initWorld() {
    Application::initWorld();

    input = InputOrbit::create(*this, 3);
    grid = Grid::Create();

    // sets up dice
    dice = Cube::Create();
    dice->setMass(1);
    // slows down moving
    // 1.0 doesn't slow down
    dice->setDamping(1.0f, 1.0f);
    dice->setAwakeTime(glfwGetTime());
}

void Tutorial2::handleKey(int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ENTER && action == GLFW_RELEASE) {
        this->startTime = glfwGetTime();
        // the world is square with 2 metres in each direction

        // resets postion, rotation and acceleration
        dice->clearAccumulators();
        dice->setPosition(0.0f, 0.0f, 0.0f);
        dice->setOrientation(1.0f, 0.0f, 0.0f, 0.0f);
        // 2 - moves out of the world in second
        // 0.2 - 10 sec to move out of the world in second
        dice->setVelocity(0.2f, 0.0f, 0.0f);
        // 1 m per second
        dice->setAcceleration(1.0f, 0.0f, 0.0f);
        // 2 * R_PI - full rotation per second
        dice->setRotation(0.0f, 0.0f, 2 * R_PI / 10);
    }
}

void Tutorial2::handleButton(int button, int action, int mods) {
}

void Tutorial2::draw() {
    dice->integrate((float)this->getLastFrameDelta());

    grid->draw(*this);
    dice->draw(*this);
}

void Tutorial2::dispose() {
    Application::dispose();

    delete dice;
    delete grid;
    delete input;
}
