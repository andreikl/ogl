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

#include "tutorial3.hpp"

Application* Tutorial3::Create() {
    auto app = new Tutorial3();
    app->init();
    return app;
}

void Tutorial3::initWorld() {
    Application::initWorld();

    input = InputOrbit::create(*this, 3);
    grid = Grid::Create();

    // sets up dice
    dice = Cube::Create();
    // slows down moving
    // 1.0 doesn't slow down
    dice->setDamping(1.0f, 1.0f);

    for (int i = 0; i < 5; i++) {
        RigidBody* ray = Line::Create();
        ray->setDamping(1.0f, 1.0f);
        rays.push_back(ray);
    }
}

void Tutorial3::handleKey(int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ENTER && action == GLFW_RELEASE) {
    }
}

void Tutorial3::handleButton(int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_RELEASE) {
        this->startTime = glfwGetTime();
        for (auto& ray : rays) {
            if (!ray->getAwakeTime()) {
                ray->setAwakeTime(glfwGetTime());
                break;
            }
        }
    }
}

void Tutorial3::draw() {
    dice->integrate((float)this->getLastFrameDelta());

    grid->draw(*this);
    dice->draw(*this);

    for (auto& ray : rays) {
        if (ray->getAwakeTime()) {
            ray->draw(*this);
        }
        // clears ray if it lives more than 1sec
        if (glfwGetTime() - ray->getAwakeTime() >= 1.0) {
            ray->setAwakeTime(0.0);
        }
    }
}

void Tutorial3::dispose() {
    Application::dispose();

    for (auto& ray : rays) {
        delete ray;
    }
    delete dice;
    delete grid;
    delete input;
}
