// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "core.h"
#include "app.h"
#include "input.h"

#include "geometry/body.h"
#include "geometry/grid.h"
#include "geometry/sphere.h"

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
    sphere = Sphere::Create();
}

void Tutorial2::draw() {
    grid->draw(*this);
    sphere->draw(*this);
}

void Tutorial2::dispose() {
    Application::dispose();

    delete sphere;
    delete grid;
    delete input;
}
