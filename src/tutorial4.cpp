#include <time.h>
#include <random>

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
#include "geometry/line.hpp"

#include "tutorial4.hpp"

Application* Tutorial4::Create() {
    srand(time(NULL));

    auto app = new Tutorial4();
    app->init();
    return app;
}


std::default_random_engine generator;
std::uniform_real_distribution<float> distribution(0, 1);
std::uniform_real_distribution<float> velocity_distribution(0, 0.2f);

void initCube(RigidBody& cube) {
    cube.setMass(1);

    // slows down moving
    // 1.0 doesn't slow down
    cube.setDamping(1.0f, 1.0f);

    cube.setPosition(distribution(generator), distribution(generator), distribution(generator));
    cube.setOrientation(1.0f, 0.0f, 0.0f, 0.0f);
    // 2 - moves out of the world in second
    // 0.2 - 10 sec to move out of the world in second
    cube.setVelocity(velocity_distribution(generator), velocity_distribution(generator), velocity_distribution(generator));
    // 1 m per second
    cube.setAcceleration(distribution(generator), distribution(generator), distribution(generator));
    // 2 * R_PI - full rotation per second
    cube.setRotation(0.0f, 0.0f, 2 * R_PI / 10);

    cube.setAwakeTime(glfwGetTime());
}

void Tutorial4::initWorld() {

    Application::initWorld();

    input = InputOrbit::create(*this, 3);
    grid = Grid::Create();

    // sets up dice
    world = Cube::Create();
    // slows down moving
    // 1.0 doesn't slow down
    world->setDamping(1.0f, 1.0f);

    for (int i = 0; i < 10; i++) {
        RigidBody* cube = Cube::Create();
        initCube(*cube);
        cubes.push_back(cube);
    }
}

void Tutorial4::handleKey(int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ENTER && action == GLFW_RELEASE) {
    }
}

void Tutorial4::handleButton(int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_RELEASE) {
        this->startTime = glfwGetTime();
        for (auto& cube : cubes) {
            // resets postion, rotation and acceleration
            cube->clearAccumulators();

            initCube(*cube);
        }
    }
}

void Tutorial4::draw() {
    world->integrate((float)this->getLastFrameDelta());

    grid->draw(*this);
    world->draw(*this);

    for (auto& cube: cubes) {
        if (cube->getAwakeTime()) {
            cube->draw(*this);

            // clears cube if it lives more than 10sec
            if (glfwGetTime() - cube->getAwakeTime() >= 10.0) {
                cube->setAwakeTime(0.0);
            }
        }
    }
}

void Tutorial4::dispose() {
    Application::dispose();

    for (auto& cube: cubes) {
        delete cube;
    }
    delete world;
    delete grid;
    delete input;
}
