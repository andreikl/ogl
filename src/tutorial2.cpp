// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>

#include "core.h"
#include "app.h"
#include "input.h"

#include "geometry/body.h"
#include "geometry/grid.h"
#include "geometry/cube.h"

#include "tutorial2.h"

Application* Tutorial2::Create() {
    auto tutorial2 = new Tutorial2();
    tutorial2->init();
    return tutorial2;
}

void Tutorial2::initWorld() {
    Application::initWorld();

    input = InputOrbit::create(*this, 3);
    grid = Grid::Create();

    dice = Cube::Create();
    dice->setMass(200.0);
    dice->setOrientation(1, 0, 0, 0);
    dice->setDamping(0.90f, 0.90f);

    dice->setAwake();
    dice->setCanSleep(false);
}

void Tutorial2::handleKey(int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ENTER && action == GLFW_RELEASE) {
        //dice->clearAccumulators();
        dice->setPosition(0.0f, 1.0f, 0.0f);
        dice->setVelocity(150.0, 300.0, 0.0);
        dice->setAcceleration(1000.0, 0.0, 0.0);
        dice->setRotation(3000, 0.0, 0.0);
        //dice->addForceAtPoint(Vector3(5.0f, 5.0f, 0.0f), Vector3(0.5f, 0.5f, 0.5f));
    }
}

void Tutorial2::draw() {
    dice->integrate(this->lastFrameDuration);

    grid->draw(*this);
    dice->draw(*this);
}

void Tutorial2::dispose() {
    Application::dispose();

    delete dice;
    delete grid;
    delete input;
}
